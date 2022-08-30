#include "Renderer.h"
#include "FileSystem.h"

#include <NuakeRenderer/ShaderRegistry.h>
#include <glad/glad.h>

using namespace NuakeRenderer;

struct Vertex
{
    Vector3 position;
    Vector2 uv;
    Vector3 normal;
};

std::vector<Vertex> CubeVertices
{
    {Vector3(-0.5f, -0.5f, -0.5f), Vector2(0, 0), Vector3(-1, 0, 0)},
    {Vector3(0.5f, -0.5f, -0.5f), Vector2(1, 0), Vector3(-1, -1, 0)},
    {Vector3(0.5f,  0.5f, -0.5f), Vector2(0, 1), Vector3(-1, 0, 0)},
    {Vector3(-0.5f,  0.5f, -0.5f), Vector2(1, 1), Vector3(-1, 0, 0)},
    {Vector3(-0.5f, -0.5f,  0.5f), Vector2(0, 1), Vector3(-1, 0, 0)},
    {Vector3(0.5f, -0.5f,  0.5f), Vector2(1, 0), Vector3(-1, 0, 0)},
    {Vector3(0.5f,  0.5f,  0.5f), Vector2(1, 1), Vector3(-1, 0, 0)},
    {Vector3(-0.5f,  0.5f,  0.5f), Vector2(1, 1), Vector3(-1, 0, 0)}
};

std::vector<uint32_t> CubeIndices
{
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
};

float QuadVertices[] = {
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
    1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
    1.0f,  -1.0f, 0.0f,   1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
    1.0f,   1.0f, 0.0f,   1.0f, 1.0f
};

VertexBuffer* vb;
VertexBuffer* ve;

VertexArray* vat;
VertexBuffer* vbt;
VertexBuffer* vet; 
Renderer::Renderer()
{
    vb = new VertexBuffer(CubeVertices.data(), sizeof(Vertex) * CubeVertices.size());
    vb->Bind();
    auto vblayout = VertexBufferLayout();
    vblayout.Push<float>(3);
    vblayout.Push<float>(2);
    vblayout.Push<float>(3);

    ve = new VertexBuffer(CubeIndices.data(), sizeof(uint32_t) * CubeIndices.size(), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    _vertexArray = new VertexArray();
    _vertexArray->AddBuffer(*vb, vblayout);
    ve->Bind();

    // Quad buffer
    vat = new VertexArray();
    vat->Bind();
    vbt = new VertexBuffer(QuadVertices, sizeof(float) * 30);

    vblayout = VertexBufferLayout();
    vblayout.Push<float>(3);
    vblayout.Push<float>(2);
    vat->AddBuffer(*vbt, vblayout);

	LoadShaders();
}

void Renderer::LoadShaders()
{
	std::string vertexSource = FileSystem::ReadFile(VERT_PATH);
	std::string fragSource = FileSystem::ReadFile(FRAG_PATH);
	Shader* basicShader = new Shader(vertexSource, fragSource);
	ShaderRegistry::Set("basic", basicShader);
}

void Renderer::BeginRender(Camera* camera)
{
	_camera = camera;
}

void Renderer::DrawCube()
{
    auto shader = ShaderRegistry::Get("basic");
    shader->Bind();
    shader->SetUniforms(
    {
        { "projection", _camera->GetProjection() },
        { "view", _camera->GetView() },
    });

    vat->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    _vertexArray->Bind();
    glDrawElements(GL_LINES, 36, GL_UNSIGNED_INT, 0);
}

