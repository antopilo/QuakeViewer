#include "Input.h"
#include <GLFW/glfw3.h>

GLFWwindow* Input::_window;

std::map<int, bool> Input::m_Keys = std::map<int, bool>();
bool Input::m_MouseButtons[5] = { false, false, false, false, false };

float Input::XScroll = 0.0f;
float Input::YScroll = 0.0f;

void Input::SetWindow(GLFWwindow* window)
{
	_window = window;
	glfwSetScrollCallback(_window, Input::ScrollCallback);
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	XScroll = (float)xoffset;
	YScroll = (float)yoffset;
}

// Only true if the key is currently being pressed
bool Input::IsKeyDown(int keycode)
{
	int state = glfwGetKey(_window, keycode);
	bool result = state == GLFW_PRESS;

	m_Keys[keycode] = state;

	return result;
}

// Only true if the key is pressed for the first frame. no repeat.
bool Input::IsKeyPressed(int keycode)
{
	int state = glfwGetKey(_window, keycode);
	bool result = state == GLFW_PRESS;

	// First time pressed?
	if (m_Keys.find(keycode) == m_Keys.end() || m_Keys[keycode] == true)
	{
		if (result)
			m_Keys[keycode] = true;

		return result;
	}

	return false;
}


bool Input::IsKeyReleased(int keycode)
{
	int state = glfwGetKey(_window, keycode);
	bool result = state == GLFW_RELEASE;

	// First time pressed?
	if (m_Keys.find(keycode) == m_Keys.end())
		return result;

	if (result && m_Keys[keycode] == true)
	{
		return true;
	}


	return false;
}
#pragma endregion

#pragma region Mouse

// Visibility
void Input::HideMouse()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Input::IsMouseHidden()
{
	return glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Input::ShowMouse()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


// Action
bool Input::IsMouseButtonDown(int button)
{
	auto state = glfwGetMouseButton(_window, button);

	return state == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(int button)
{
	auto state = glfwGetMouseButton(_window, button);

	return false;
}

bool Input::IsMouseButtonReleased(int button)
{
	auto state = glfwGetMouseButton(_window, button);

	return state == GLFW_RELEASE && m_MouseButtons[button] == true;
}

// Position
float Input::GetMouseX()
{

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	return (float)xpos;
}

float Input::GetMouseY()
{

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	return (float)ypos;
}

Vector2 Input::GetMousePosition()
{

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	return Vector2(xpos, ypos);
}
#pragma endregion


void Input::Update()
{
	// Reset all input to false.
	for (auto& k : m_Keys)
	{
		if (!IsKeyDown(k.first))
			k.second = false;
	}

	for (int i = 0; i < 5; i++)
	{
		if (!IsMouseButtonDown(i))
			m_MouseButtons[i] = false;
	}
}