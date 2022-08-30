#pragma once
#include <NuakeRenderer/Math.h>
#include <NuakeRenderer/Vendors/glm/glm/ext/matrix_clip_space.hpp>
#include <NuakeRenderer/Vendors/glm/glm/ext/matrix_float4x4.hpp>
#include <NuakeRenderer/Vendors/glm/glm/ext/matrix_transform.hpp>
class Camera
{
public:
	Matrix4 _projection;
	Matrix4 _view;
	Vector3 _translation = Vector3();
	Vector3 _up = Vector3(0, 1, 0);
	Vector3 _right = Vector3(1, 0, 0);
	Vector3 _forward = Vector3(0, 0, 1);

	float _yaw = 0.0f;
	float _pitch = 0.0f;;
	bool _controlled = true;
	float _speed = 0.1f;
	float _ratio = 1.0f;

	Camera(const Matrix4& _projection, const Matrix4& _view);
	~Camera() = default;

	void OnWindowResize(Vector2 size)
	{
		_ratio = (float)size.x / (float)size.y;
	}

	void Update(float ts);
	Matrix4& GetProjection()  
	{ 
		
		_projection = glm::perspectiveFov(glm::radians(90.0f), 9.0f * _ratio, 9.0f, 0.001f, 1000.0f);
		return _projection; 
	}

	Matrix4 GetView()
	{
		glm::mat4 tr = lookAt(_translation, _translation + _forward, Vector3(0, 1, 0));
		return tr;
	}
};