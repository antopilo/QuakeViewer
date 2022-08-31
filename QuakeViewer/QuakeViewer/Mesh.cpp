#include "Mesh.h"

#include <NuakeRenderer/VertexBufferLayout.h>

Mesh::Mesh(const std::vector<Vertex>& vertices)
{
	_vertexArray = std::make_shared<VertexArray>();
	_vertexArray->Bind();

	_vertexBuffer = std::make_shared<VertexBuffer>(vertices.data(), sizeof(Vertex) * vertices.size());
	
	auto vertexBufferLayout = VertexBufferLayout();
	vertexBufferLayout.Push<float>(3);
	vertexBufferLayout.Push<float>(2);
	vertexBufferLayout.Push<float>(3);

	_vertexArray->AddBuffer(*_vertexBuffer, vertexBufferLayout);
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	_vertexBuffer = std::make_shared<VertexBuffer>(vertices.data(), sizeof(Vertex) * vertices.size());
	_vertexBuffer->Bind();

	auto vertexBufferLayout = VertexBufferLayout();
	vertexBufferLayout.Push<float>(3);
	vertexBufferLayout.Push<float>(2);
	vertexBufferLayout.Push<float>(3);

	_vertexElementArray = std::make_shared<VertexBuffer>(indices.data(), sizeof(unsigned int) * indices.size(), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

	_vertexArray = std::make_shared<VertexArray>();
	_vertexArray->AddBuffer(*_vertexBuffer, vertexBufferLayout);
	_vertexElementArray->Bind();
}

void Mesh::Bind() const
{
	_vertexArray->Bind();
}

void Mesh::Unbind() const
{
	_vertexArray->Unbind();
}