#include <NuakeRenderer/NuakeRenderer.h>
#include <NuakeRenderer/Window.h>

#include <QuakeBSPParser/BSPParser.h>
#include "QuakeViewer/Input.h"

#include "QuakeViewer/Renderer.h"
#include <GLFW/glfw3.h>
#include "QuakeViewer/Mesh.h"

#include <iostream>

float _deltaTime = 0.0f;
float _timeStep = 0.0f;
float _lastFrameTime = 0.0f;

int main()
{
	using namespace NuakeRenderer;

	auto window = Window("Quake Viewer");
	Input::SetWindow(window.GetHandle());

	NuakeRenderer::Init();
	NuakeRenderer::ApplyNuakeImGuiTheme();

	Renderer renderer;

	Matrix4 projection = glm::perspective(80.0f, 16.0f / 9.0f, 0.01f, 100000.f);
	Matrix4 view = Matrix4(1);
	Camera* camera = new Camera(projection, view);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	const std::string BSP_PATH = "e1m1.bsp";

	BSPParser::LoadFile(BSP_PATH);
	BSPParser::Parse();

	uint32_t verticesNum = BSPParser::Vertices.size();
	std::vector<Vertex> vertices;
	for (const auto& v : BSPParser::Vertices)
	{
		vertices.push_back({
			Vector3(v.X, v.Z, -v.Y),
			Vector2(0, 0),
			Vector3(v.X, v.Z, v.Y)
		});
	}

	//for (auto& e : BSPParser::Edges)
	//{
	//	Vertex vertex1 = vertices[e.vertex0];
	//	Vertex vertex2 = vertices[e.vertex1];
	//	meshVertices.push_back(vertex1);
	//	meshVertices.push_back(vertex2);
	//}

	auto indices = std::vector<unsigned int>();
	for (auto& f : BSPParser::Faces)
	{
		// first edge
		long firstEdge = f.ledge_id;
		long lastEdge = firstEdge + f.ledge_num;

		int edgeCount = 0;

		for (long i = firstEdge; i < lastEdge; i++)
		{
			auto edgeId = BSPParser::LEdges[i];

			if(edgeId < 0)
			{
				auto edge = BSPParser::Edges[-edgeId];
				indices.push_back((int)edge.vertex0);
				indices.push_back((int)edge.vertex1);
			}
			else if(edgeId != 0)
			{
				auto edge = BSPParser::Edges[edgeId];
				indices.push_back((int)edge.vertex1);
				indices.push_back((int)edge.vertex0);
			}
			edgeCount++;
		}
	}

	Mesh mesh2 = Mesh(vertices);
	Mesh mesh = Mesh(vertices, indices);

	while (!window.ShouldClose())
	{
		_deltaTime = (float)glfwGetTime();
		_timeStep = _deltaTime - _lastFrameTime;
		_lastFrameTime = _deltaTime;

		NuakeRenderer::SetClearColor(0.1, 0.1, 0.1, 1.0);
		NuakeRenderer::Clear();

		glViewport(0, 0, window.GetWindowSize().x, window.GetWindowSize().y);

		camera->OnWindowResize(window.GetWindowSize());

		camera->Update(_timeStep);
		renderer.BeginRender(camera);
		renderer.DrawCube();

		mesh.Bind();
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

		//mesh2.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, std::size(vertices));

		NuakeRenderer::BeginImGuiFrame();
		{
			// imgui code here...
			ImGui::Begin("camera");
			ImGui::Text("Position:");
			std::string pos = "x: " + std::to_string(camera->_translation.x) + 
				", y:" + std::to_string(camera->_translation.y) + 
				", z:" + std::to_string(camera->_translation.z);
			ImGui::Text(pos.c_str());
			ImGui::End();
		}
		NuakeRenderer::EndImGuiFrame();

		window.SwapBuffers();
		NuakeRenderer::PollEvents();
	}

	return 1;
}