#pragma once
#include <glm.hpp>
#include <vector>
#include <map>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Icosphere
{
public:
	bool cel;
	float radius;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> positions;
	std::vector<float> texCoords;
	std::vector<float> normals;

	std::map<std::pair<float, float>, unsigned int> sharedIndices;

	/* Abstracted OpenGL Elements */
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	Icosphere(float r, unsigned int subdivs);
	~Icosphere() {}

	void LogVerts();
	void LogIndices();
private:
	std::vector<float> IcosahedronVertices();
	void BuildVertices(unsigned int subdivs);
	void Subdivide(unsigned int subdivs);
	void BuildVertexBuffer();
	void BuildVertexBufferCel();


	void PositionMidpoint(const float v1[3], const float v2[3], float magnitude, float v3[3]);
	void TextureMidpoint(const float t1[2], const float t2[2], float nt[2]);
	void ComputeNormal(const float pos[3], float n[3]);
	/*
	* Add elements to member variable vectors.
	* Each takes three as triangles are formed and added
	* three vertices at a time in the code
	*/
	void AddIndices(unsigned int i1, unsigned int i2, unsigned int i3);
	void AddPosition(const float px, const float py, const float pz);
	void AddNormal(const float nx, const float ny, const float nz);
	void AddTexCoord(const float t0, const float t1);
	unsigned int CheckAddVertexElements(const float pos[3], const float tex[2], const float norm[3]);
	bool IsSharedTexCoord(const float tex[2]);
	bool isOnLineSeg(const float a[2], const float b[2], const float t[2]);
};