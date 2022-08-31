#pragma once
#include "Vertex.h"

#include <NuakeRenderer/VertexArray.h>
#include <NuakeRenderer/VertexBuffer.h>

#include <memory>
#include <vector>

using namespace NuakeRenderer;

class Mesh
{
private:
	std::shared_ptr<VertexArray> _vertexArray;
	std::shared_ptr<VertexBuffer> _vertexBuffer;
	std::shared_ptr<VertexBuffer> _vertexElementArray;

public:
	Mesh(const std::vector<Vertex>& vertices);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	~Mesh() = default;

	void Bind() const;
	void Unbind() const;
};