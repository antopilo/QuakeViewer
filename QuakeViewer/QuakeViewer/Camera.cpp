#include "Camera.h"

#include <iostream>
#include "Input.h"
#include <Dependencies/glfw/include/GLFW/glfw3.h>

Camera::Camera(const Matrix4& projection, const Matrix4& view)
{
	_projection = projection;
	_view = view;
	_yaw = 0.0f;
	_pitch = 0.0f;
	_translation = Vector3(0, 0, 0);
}

float mouseLastX;
float mouseLastY;
bool firstMouse;

void Camera::Update(float ts)
{
	float x = Input::GetMouseX();
	float y = Input::GetMouseY();

	if (!_controlled && Input::IsMouseButtonDown(1))
	{
		mouseLastX = x;
		mouseLastY = y;
	}

	_controlled = Input::IsMouseButtonDown(1);

	//if (!controlled)
	//	Input::ShowMouse();
	//else
	//	Input::HideMouse();

	// Should probably not have speed binding in here.
	if (Input::IsKeyDown(GLFW_KEY_UP))
		_speed += 0.1f;
	else if (Input::IsKeyDown(GLFW_KEY_DOWN))
		_speed -= 0.1f;

	if (_speed < 0)
		_speed = 0;

	// Keyboard
	if (!_controlled)
		return;


	glm::vec3 movement = glm::vec3(0, 0, 0);

	if (Input::IsKeyDown(GLFW_KEY_D))
		movement -= _right * (_speed * ts);
	if (Input::IsKeyDown(GLFW_KEY_A))
		movement += _right * (_speed * ts);

	if (Input::IsKeyDown(GLFW_KEY_W))
		movement += _forward * (_speed * ts);
	if (Input::IsKeyDown(GLFW_KEY_S))
		movement -= _forward * (_speed * ts);
	if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
		movement -= _up * (_speed * ts);
	if (Input::IsKeyDown(GLFW_KEY_SPACE))
		movement += _up * (_speed * ts);

	_translation += Vector3(movement);
	

	if (firstMouse)
	{
		mouseLastX = x;
		mouseLastY = y;
		firstMouse = false;
	}

	// mouse
	float diffx = x - mouseLastX;
	float diffy = mouseLastY - y;
	mouseLastX = x;
	mouseLastY = y;

	const float sensitivity = 0.1f;
	diffx *= sensitivity;
	diffy *= sensitivity;

	_yaw += diffx;
	_pitch += diffy;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	_forward.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_forward.y = sin(glm::radians(_pitch));
	_forward.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_forward = glm::normalize(_forward);
	_right = glm::normalize(glm::cross(_up, _forward));
}