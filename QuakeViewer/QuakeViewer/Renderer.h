#pragma once
#include "Camera.h"

#include <NuakeRenderer/VertexArray.h>
#include <NuakeRenderer/VertexBuffer.h>
#include <NuakeRenderer/VertexBufferLayout.h>

#include <string>

using namespace NuakeRenderer;

class Renderer
{
private:
	const std::string VERT_PATH = "Resources/Shaders/basic.vert.glsl";
	const std::string FRAG_PATH = "Resources/Shaders/basic.frag.glsl";

	Camera* _camera;
	VertexArray* _vertexArray;

	void LoadShaders();
public:
	Renderer();
	~Renderer() = default;

	void BeginRender(Camera* camera);

	void DrawCube();
};