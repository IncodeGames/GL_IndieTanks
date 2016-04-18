/*
* Copyright (C) 2014 Benny Bobaganoosh
* Modified by Benjamin Lane
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>

#include "obj_loader.h"
#include "../Primitives/ShapeBase.h"

class IndexedModel
{
public:
	IndexedModel() {}
	IndexedModel(const std::vector<unsigned int> indices, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texCoords,
		const std::vector<glm::vec3>& normals = std::vector<glm::vec3>(), const std::vector<glm::vec3>& tangents = std::vector<glm::vec3>()) :
		m_indices(indices),
		m_positions(positions),
		m_texCoords(texCoords),
		m_normals(normals),
		m_tangents(tangents) {}

	bool IsValid() const;
	void CalcNormals();
	void CalcTangents();

	IndexedModel Finalize();

	void AddVertex(const glm::vec3& vert);
	inline void AddVertex(float x, float y, float z) { AddVertex(glm::vec3(x, y, z)); }

	void AddTexCoord(const glm::vec2& texCoord);
	inline void AddTexCoord(float x, float y) { AddTexCoord(glm::vec2(x, y)); }

	void AddNormal(const glm::vec3& normal);
	inline void AddNormal(float x, float y, float z) { AddNormal(glm::vec3(x, y, z)); }

	void AddTangent(const glm::vec3& tangent);
	inline void AddTangent(float x, float y, float z) { AddTangent(glm::vec3(x, y, z)); }

	void AddFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2);

	inline const std::vector<unsigned int>& GetIndices() const { return m_indices; }
	inline const std::vector<glm::vec3>& GetPositions()   const { return m_positions; }
	inline const std::vector<glm::vec2>& GetTexCoords()   const { return m_texCoords; }
	inline const std::vector<glm::vec3>& GetNormals()     const { return m_normals; }
	inline const std::vector<glm::vec3>& GetTangents()    const { return m_tangents; }
private:
	std::vector<unsigned int> m_indices;
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;
};

class MeshData
{
public:
	MeshData(const IndexedModel& model);
	virtual ~MeshData();

	void Draw() const;
protected:
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		TANGENT_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	int m_drawCount;
};

class Mesh
{
public:
	Mesh(const std::string& fileName = "cube.obj");
	Mesh(const std::string& meshName, const IndexedModel& model);
	Mesh(const Mesh& mesh);
	virtual ~Mesh();

	void Draw() const;
protected:
private:
	static std::map<std::string, MeshData*> s_resourceMap;

	std::string m_fileName;
	MeshData* m_meshData;

	void operator=(Mesh& mesh) {}
};

#endif