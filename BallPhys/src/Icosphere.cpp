#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Icosphere.h"

Icosphere::Icosphere(float r, unsigned int subdivs)
	: radius(r)
{
	BuildVertices(subdivs);
	BuildVertexBuffer();

	// OpenGL Elements Code
	vb.FillBuffer(&vertices[0], vertices.size() * sizeof(float));
	va.AddVertexBufferElement<float>(3);
	va.AddVertexBufferElement<float>(3);
	va.AddVertexBufferElement<float>(2);
	va.AddBuffer(vb);

	ib.FillBuffer(&indices[0], indices.size());
}

std::vector<float> Icosphere::IcosahedronVertices()
{
	std::vector<float> pos(12 * 3);

	const float theta = (float)M_PI / 180.0f * 72.0f; // 72 degrees. 360/5
	const float phi = atan(1.0f / 2); // Angle between xz plane and y-axis

	float theta_1 = 0.0f; // theta for top set of five vertices
	float theta_2 = theta / 2;

	// Top vertex
	unsigned int i = 0;
	pos[i] = 0.0f;
	pos[i + 1] = radius;
	pos[i + 2] = 0.0f;

	// Middle 10 vertices
	float y = radius * sin(phi);
	float xz = radius * cos(phi);
	for (i = 1; i <= 5; i++)
	{
		unsigned int i1 = i * 3;
		pos[i1] = xz * cos(theta_1);		// x-pos
		pos[i1 + 1] = y;					// y-pos
		pos[i1 + 2] = xz * sin(theta_1);	// z-pos

		unsigned int i2 = (i + 5) * 3;
		pos[i2] = xz * cos(theta_2);		// x-pos
		pos[i2 + 1] = -y;					// y-pos
		pos[i2 + 2] = xz * sin(theta_2);	// z-pos

		theta_1 += theta;
		theta_2 += theta;
	}

	// Bottom vertex
	i = 11 * 3;
	pos[i] = 0.0f;
	pos[i + 1] = -radius;
	pos[i + 2] = 0.0f;
	return pos;
}

void Icosphere::BuildVertices(unsigned int subdivs)
{
	const float H_TEX_INTERVAL = 1.0f / 11.0f;
	const float V_TEX_INTERVAL = 1.0f / 3.0f;

	std::vector<float> pos = IcosahedronVertices();
	float n[3];

	/* Top Vertices */
	AddPosition(pos[0], pos[1], pos[2]);		// 0
	AddNormal(0, 1, 0);
	AddTexCoord(H_TEX_INTERVAL, 0);

	AddPosition(pos[0], pos[1], pos[2]);		// 1
	AddNormal(0, 1, 0);
	AddTexCoord(3 * H_TEX_INTERVAL, 0);

	AddPosition(pos[0], pos[1], pos[2]);		// 2
	AddNormal(0, 1, 0);
	AddTexCoord(5 * H_TEX_INTERVAL, 0);

	AddPosition(pos[0], pos[1], pos[2]);		// 3
	AddNormal(0, 1, 0);
	AddTexCoord(7 * H_TEX_INTERVAL, 0);

	AddPosition(pos[0], pos[1], pos[2]);		// 4
	AddNormal(0, 1, 0);
	AddTexCoord(9 * H_TEX_INTERVAL, 0);

	/* Middle Top Outside Vertices */
	ComputeNormal(&pos[3], n);
	AddPosition(pos[3], pos[4], pos[5]);		// 5
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(0, V_TEX_INTERVAL);

	AddPosition(pos[3], pos[4], pos[5]);		// 6
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(10 * H_TEX_INTERVAL, V_TEX_INTERVAL);

	/* Middle Bottom Outside Vertices */
	ComputeNormal(&pos[18], n);
	AddPosition(pos[18], pos[19], pos[20]);		// 7
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(H_TEX_INTERVAL, 2 * V_TEX_INTERVAL);
	
	AddPosition(pos[18], pos[19], pos[20]);		// 8
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(11 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL);

	/* Middle Shared Vertices */
	ComputeNormal(&pos[6], n);
	AddPosition(pos[6], pos[7], pos[8]);		// 9
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(2 * H_TEX_INTERVAL, V_TEX_INTERVAL);
	sharedIndices[std::make_pair(2 * H_TEX_INTERVAL, V_TEX_INTERVAL)] = (unsigned int)9;

	ComputeNormal(&pos[9], n);
	AddPosition(pos[9], pos[10], pos[11]);		// 10
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(4 * H_TEX_INTERVAL, V_TEX_INTERVAL);
	sharedIndices[std::make_pair(4 * H_TEX_INTERVAL, V_TEX_INTERVAL)] = (unsigned int)10;

	ComputeNormal(&pos[12], n);
	AddPosition(pos[12], pos[13], pos[14]);		// 11
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(6 * H_TEX_INTERVAL, V_TEX_INTERVAL);
	sharedIndices[std::make_pair(6 * H_TEX_INTERVAL, V_TEX_INTERVAL)] = (unsigned int)11;

	ComputeNormal(&pos[15], n);
	AddPosition(pos[15], pos[16], pos[17]);		// 12
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(8 * H_TEX_INTERVAL, V_TEX_INTERVAL);
	sharedIndices[std::make_pair(8 * H_TEX_INTERVAL, V_TEX_INTERVAL)] = (unsigned int)12;

	ComputeNormal(&pos[21], n);
	AddPosition(pos[21], pos[22], pos[23]);		// 13
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(3 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL);
	sharedIndices[std::make_pair(3 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL)] = (unsigned int)13;

	ComputeNormal(&pos[24], n);
	AddPosition(pos[24], pos[25], pos[26]);		// 14
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(5 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL);
	sharedIndices[std::make_pair(5 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL)] = (unsigned int)14;

	ComputeNormal(&pos[27], n);
	AddPosition(pos[27], pos[28], pos[29]);		// 15
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(7 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL);
	sharedIndices[std::make_pair(7 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL)] = (unsigned int)15;

	ComputeNormal(&pos[30], n);
	AddPosition(pos[30], pos[31], pos[32]);		// 16
	AddNormal(n[0], n[1], n[2]);
	AddTexCoord(9 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL);
	sharedIndices[std::make_pair(9 * H_TEX_INTERVAL, 2 * V_TEX_INTERVAL)] = (unsigned int)16;

	/* Bottom Vertices */
	AddPosition(pos[33], pos[34], pos[35]);		// 17
	AddNormal(0, -1, 0);
	AddTexCoord(2 * H_TEX_INTERVAL, 3 * V_TEX_INTERVAL);

	AddPosition(pos[33], pos[34], pos[35]);		// 18
	AddNormal(0, -1, 0);
	AddTexCoord(2 * H_TEX_INTERVAL, 3 * V_TEX_INTERVAL);

	AddPosition(pos[33], pos[34], pos[35]);		// 19
	AddNormal(0, -1, 0);
	AddTexCoord(2 * H_TEX_INTERVAL, 3 * V_TEX_INTERVAL);

	AddPosition(pos[33], pos[34], pos[35]);		// 20
	AddNormal(0, -1, 0);
	AddTexCoord(2 * H_TEX_INTERVAL, 3 * V_TEX_INTERVAL);

	AddPosition(pos[33], pos[34], pos[35]);		// 21
	AddNormal(0, -1, 0);
	AddTexCoord(2 * H_TEX_INTERVAL, 3 * V_TEX_INTERVAL);

	// Top Row
	AddIndices(0, 5, 9);
	AddIndices(1, 9, 10);
	AddIndices(2, 10, 11);
	AddIndices(3, 11, 12);
	AddIndices(4, 12, 6);
	// Middle Top Row
	AddIndices(5, 7, 9);
	AddIndices(9, 13, 10);
	AddIndices(10, 14, 11);
	AddIndices(11, 15, 12);
	AddIndices(12, 16, 6);
	// Middle Bottom Row
	AddIndices(7, 9, 13);
	AddIndices(13, 10, 14);
	AddIndices(14, 11, 15);
	AddIndices(15, 12, 16);
	AddIndices(16, 6, 8);
	// Bottom Row
	AddIndices(17, 7, 13);
	AddIndices(18, 13, 14);
	AddIndices(19, 14, 15);
	AddIndices(20, 15, 16);
	AddIndices(21, 16, 8);

	Subdivide(subdivs);

	BuildVertexBuffer();
}

void Icosphere::Subdivide(unsigned int subdivs)
{
	// Temporary storage of old values
	std::vector<unsigned int> tmpIndices;
	unsigned int indexCount;

	const float *p1, *p2, *p3;		// Pointer to original vertices positions
	const float *t1, *t2, *t3;		// Pointer to origina vertices texture coords

	float p12[3], p23[3], p13[3];	// New midpoint vertex positions
	float n12[3], n23[3], n13[3];	// New midpoint vertex normals
	float t12[2], t23[2], t13[2];	// New midpoint texture coords

	unsigned int i12, i23, i13;

	for (unsigned int i = 0; i < subdivs; ++i)
	{
		// tmpPositions = positions;
		tmpIndices = indices;
		indices.clear();

		indexCount = tmpIndices.size();
		for (unsigned int j = 0; j < indexCount; j += 3)
		{
			unsigned int i1 = tmpIndices[j];
			unsigned int i2 = tmpIndices[j + 1];
			unsigned int i3 = tmpIndices[j + 2];

			p1 = &positions[i1 * 3];
			p2 = &positions[i2 * 3];
			p3 = &positions[i3 * 3];

			t1 = &texCoords[i1 * 2];
			t2 = &texCoords[i2 * 2];
			t3 = &texCoords[i3 * 2];

			PositionMidpoint(p1, p2, radius, p12);
			PositionMidpoint(p2, p3, radius, p23);
			PositionMidpoint(p1, p3, radius, p13);
			TextureMidpoint(t1, t2, t12);
			TextureMidpoint(t2, t3, t23);
			TextureMidpoint(t1, t3, t13);
			ComputeNormal(p12, n12);
			ComputeNormal(p23, n23);
			ComputeNormal(p13, n13);

			i12 = CheckAddVertexElements(p12, t12, n12);
			i23 = CheckAddVertexElements(p23, t23, n23);
			i13 = CheckAddVertexElements(p13, t13, n13);

			AddIndices(i1, i12, i13);
			AddIndices(i12, i2, i23);
			AddIndices(i12, i23, i13);
			AddIndices(i13, i23, i3);
		}
	}
}

void Icosphere::PositionMidpoint(const float v1[3], const float v2[3], float magnitude, float v3[3])
{
	v3[0] = v1[0] + v2[0];
	v3[1] = v1[1] + v2[1];
	v3[2] = v1[2] + v2[2];
	float mag = magnitude / (sqrt(v3[0] * v3[0] + v3[1] * v3[1] + v3[2] * v3[2]));
	v3[0] *= mag;
	v3[1] *= mag;
	v3[2] *= mag;
}

void Icosphere::TextureMidpoint(const float t1[2], const float t2[2], float nt[2])
{
	nt[0] = (t1[0] + t2[0]) * 0.5f;
	nt[1] = (t1[1] + t2[1]) * 0.5f;
}

void Icosphere::AddPosition(const float px, const float py, const float pz)
{
	positions.push_back(px);
	positions.push_back(py);
	positions.push_back(pz);
}

void Icosphere::AddTexCoord(const float t0, const float t1)
{
	texCoords.push_back(t0);
	texCoords.push_back(t1);
}

void Icosphere::AddIndices(const unsigned int i1, const unsigned int i2, const unsigned int i3)
{
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}

void Icosphere::ComputeNormal(const float v[3], float n[3])
{
	float mag = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	n[0] = mag * v[0];
	n[1] = mag * v[1];
	n[2] = mag * v[2];
}

void Icosphere::AddNormal(const float nx, const float ny, const float nz)
{
	normals.push_back(nx);
	normals.push_back(ny);
	normals.push_back(nz);
}

unsigned int Icosphere::CheckAddVertexElements(const float pos[3], const float tex[2], const float norm[3])
{
	unsigned int index;

	// Test if vertex is shared. ie. not on the outer edge of texture map
	if (IsSharedTexCoord(tex))
	{
		std::pair<float, float> key = std::make_pair(tex[0], tex[1]);
		std::map<std::pair<float, float>, unsigned int>::iterator iter = sharedIndices.find(key);
		if (iter == sharedIndices.end())
		{
			AddPosition(pos[0], pos[1], pos[2]);
			AddTexCoord(tex[0], tex[1]);
			AddNormal(norm[0], norm[1], norm[2]);
			index = texCoords.size() / 2 - 1;
			sharedIndices[key] = index;
		}
		else
		{
			index = iter->second;
		}
	}
	else
	{
		AddPosition(pos[0], pos[1], pos[2]);
		AddTexCoord(tex[0], tex[1]);
		AddNormal(norm[0], norm[1], norm[2]);
		index = texCoords.size() / 2 - 1;
	}
	return index;
}

void Icosphere::BuildVertexBuffer()
{
	unsigned int i, j;
	for (i = 0, j = 0; i < positions.size(); i += 3, j += 2)
	{
		vertices.push_back(positions[i]);
		vertices.push_back(positions[i + 1]);
		vertices.push_back(positions[i + 2]);

		vertices.push_back(normals[i]);
		vertices.push_back(normals[i + 1]);
		vertices.push_back(normals[i + 2]);

		vertices.push_back(texCoords[j]);
		vertices.push_back(texCoords[j + 1]);
	}
}

void Icosphere::BuildVertexBufferCel()
{
	unsigned int i;
	for (i = 0; i < positions.size(); i += 3)
	{
		vertices.push_back(positions[i]);
		vertices.push_back(positions[i + 1]);
		vertices.push_back(positions[i + 2]);

		vertices.push_back(normals[i]);
		vertices.push_back(normals[i + 1]);
		vertices.push_back(normals[i + 2]);
	}
}

bool Icosphere::IsSharedTexCoord(const float tex[2])
{
	const float H = 1.0f / 11.0f;
	const float V = 1.0f / 3.0f;
	float segs[] = {
		0, V,		H, 0,
		H, 0,		2*H, V,
		2*H, V,		3*H, 0,
		3*H, 0,		4*H, V,
		4*H, V,		5*H, 0,
		5*H, 0,		6*H, V,
		6*H, V,		7*H, 0,
		7*H, 0,		8*H, V,
		8*H, V,		9*H, 0,
		9*H, 0,		11*H, 2*V,
		11*H, 2*V,	10*H, 3*V,
		10*H, 3*V,	9*H, 2*V,
		9*H, 2*V,	8*H, 3*V,
		8*H, 3*V,	7*H, 2*V,
		7*H, 2*V,	6*H, 3*V,
		6*H, 3*V,	5*H, 2*V,
		5*H, 2*V,	4*H, 3*V,
		4*H, 3*V,	3*H, 2*V,
		3*H, 2*V,	2*H, 3*V,
		2*H, 3*V,	0, 1*V,
	};
	unsigned int size = (int)(sizeof(segs) / sizeof(segs[0]));
	for (unsigned int i = 0, j = 2; i < size; i += 4, j += 4)
	{
		if (isOnLineSeg(&segs[i], &segs[j], tex))
			return false;
	}
	return true;
}

bool Icosphere::isOnLineSeg(const float a[2], const float b[2], const float t[2])
{
	const float eps = 0.00001f;
	float cross = ((a[0] - b[0]) * (t[1] - a[1])) - ((b[1] - a[1]) * (t[0] - a[0]));
	if (cross > eps || cross < -eps)
		return false;
	if ((t[0] > a[0] && t[0] > b[0]) || (t[0] < a[0] && t[0] < b[0]))
		return false;
	if ((t[1] > a[1] && t[1] > b[1]) || (t[1] < a[1] && t[1] < b[1]))
		return false;
	return true;
}

void Icosphere::LogVerts()
{
	for (unsigned int i = 0; i < vertices.size(); i += 5)
	{
		std::cout << "Vertices[" << i << "].x: " << vertices[i] << std::endl;
		std::cout << "Vertices[" << i + 1 << "].y: " << vertices[i + 1] << std::endl;
		std::cout << "Vertices[" << i + 2 << "].z: " << vertices[i + 2] << std::endl;
		std::cout << "Tex[" << i + 3 << "].x: " << vertices[i + 3] << std::endl;
		std::cout << "Tex[" << i + 4 << "].y: " << vertices[i + 4] << std::endl;
	}
}

void Icosphere::LogIndices()
{
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		std::cout << "Indices[" << i << "]: " << indices[i] << std::endl;
	}
}
