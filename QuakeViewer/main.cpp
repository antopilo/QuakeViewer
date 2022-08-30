#include <NuakeRenderer/NuakeRenderer.h>
#include <NuakeRenderer/Window.h>

#include <QuakeBSPParser/BSPParser.h>
#include "QuakeViewer/Input.h"

#include "QuakeViewer/Renderer.h"
#include <GLFW/glfw3.h>

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