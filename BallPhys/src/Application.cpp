#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Physics.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Icosphere.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void LogMat4(glm::mat4 m);

const unsigned int scr_width = 1200;
const unsigned int scr_height = 900;

// Camera Setup
Camera cam(glm::vec3(0.0f, 0.0f, 650.0f));

bool firstMouse = true;
float lastX = scr_width / 2;
float lastY = scr_height / 2;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    /* Capture the mouse in the OpenGL window */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize Glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    /* Physics setup code */
    DeclareBalls();
    Initialize();
    tc = Predict();

    /* Shape to draw setup */
    Icosphere ico(1.0f, 3);

    /* Shaders */
    Shader cel_shader("res/shaders/celVert.shader", "res/shaders/celFrag.shader");
    cel_shader.Bind();
    cel_shader.SetUniformVec3("light_pos", glm::vec3(0.0f, 0.0f, 0.0f));
    cel_shader.SetUniformVec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));

    /* Setup Renderer */
    Renderer renderer;
    renderer.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    renderer.EnableDepthTest();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Implement deltatime
        float currFrame = (float)glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        processInput(window);

        /* Physics calculations here */
        AdvanceToNextFrame();
        tf = dtf;
        /* Physics calculations end */

        /* Render here */
        renderer.Clear();

        glm::mat4 mProjection = glm::mat4(1.0f);
        glm::mat4 mView = glm::mat4(1.0f);
        glm::mat4 mModel = glm::mat4(1.0f);

        mProjection = glm::perspective(glm::radians(cam.Zoom), (float)scr_width / (float)scr_height, 1.0f, 1000.0f);
        mView = cam.GetViewMatrix();

        cel_shader.Bind();
        // cel_shader.SetUniformVec3("view_pos", cam.pos);
        cel_shader.SetUniformMat4("projection", mProjection);
        cel_shader.SetUniformMat4("view", mView);

        /* Draw moving balls */
        for (unsigned int i = 0; i < n; ++i)
        {
            glm::mat4 ico_model = glm::translate(mModel, positions[i]);
            ico_model = glm::scale(ico_model, glm::vec3(radius[i], radius[i], radius[i]));
            glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(ico_model)));

            cel_shader.Bind();
            cel_shader.SetUniformMat4("model", ico_model);
            cel_shader.SetUniformMat3("m_normal", normal);

            float num = ((int)i / (float)n) * (float)M_PI;
            cel_shader.SetUniformVec4("obj_color", glm::vec4(sin(num), cos(num), sin(2 * num), 1.0f));

            renderer.Draw(ico.va, ico.ib, cel_shader);
        }

        /* Draw the container */
        glm::mat4 container_model = glm::translate(mModel, container);
        container_model = glm::scale(container_model, glm::vec3(rc, rc, rc));
        cel_shader.SetUniformMat4("model", container_model);
        renderer.DrawWireframe(ico.va, ico.ib, cel_shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        std::cout << "yaw: " << cam.yaw << std::endl;
        std::cout << "pitch: " << cam.pitch << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Make viewport match new dimensions of resized window
    // Width and height will be larger then specified on retina displays
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;
    lastX = (float)xpos;
    lastY = (float)ypos;

    cam.ProcessMouseMovement((float)xoffset, (float)yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.ProcessScroll((float)yoffset);
}

void LogMat4(glm::mat4 m)
{
    std::cout << "Matrix:" << std::endl;
    std::cout << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << std::endl;
    std::cout << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << std::endl;
    std::cout << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << std::endl;
    std::cout << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << std::endl;
}