#pragma once
#include <NuakeRenderer/Math.h>
#include <map>

struct GLFWwindow;

class Input
{
private:
	static bool m_MouseButtons[5];
	static std::map<int, bool> m_Keys;
	static GLFWwindow* _window;
public:
	static void SetWindow(GLFWwindow* window);
	static bool IsKeyPressed(int keycode);
	static bool IsKeyDown(int keycode);
	static bool IsKeyReleased(int keycode);
	static void Update();

	static void HideMouse();
	static void ShowMouse();
	static bool IsMouseHidden();
	static bool IsMouseButtonPressed(int button);
	static bool IsMouseButtonDown(int button);
	static bool IsMouseButtonReleased(int button);

	static float GetMouseX();
	static float GetMouseY();
	static Vector2 GetMousePosition();
};