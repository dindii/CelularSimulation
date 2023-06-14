#include "Window.h"

#include <iostream>
#include <glad/glad.h>

#include <Core/Application.h>

namespace CS
{
	LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	Window::Window(std::string&& name, vec2<int32_t> dims) noexcept : m_Dims(dims), m_WindowName(name), m_NativeWindow(nullptr), m_WindowContext(nullptr), m_ClientDims(0.0f, 0.0f)
	{
		WNDCLASSEX wc = {};

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = NULL;
		wc.cbWndExtra = NULL;
		wc.hInstance  = NULL;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = name.c_str();
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Error registering class",
				"Error", MB_OK | MB_ICONERROR);
			return;
		}

		
		RECT windowRect = { 0, 0, static_cast<LONG>(dims.x), static_cast<LONG>(dims.y) };
		::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		m_ClientDims = { windowWidth, windowHeight };

		m_Dims = m_ClientDims;

		m_NativeWindow = CreateWindowEx(NULL,
			name.c_str(),
			name.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			m_ClientDims.x, m_ClientDims.y,
			NULL,
			NULL,
			NULL,
			this);


		if (!m_NativeWindow)
		{
			MessageBox(NULL, "Could not create the window.",
				"Error", MB_OK | MB_ICONERROR);
			return;
		}

		::ShowWindow(m_NativeWindow, SW_SHOW);
		::SetActiveWindow(m_NativeWindow);

		bool graphicsLoaded = LoadGraphicsContext();

		if (!graphicsLoaded)
		{
			MessageBox(NULL, "Could not successfully initialize the graphics context.",
				"Error", MB_OK | MB_ICONERROR);
			return;
		}

	}

	bool Window::LoadGraphicsContext()
	{
		HDC context  = m_WindowContext = ::GetDC(m_NativeWindow);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		int pixelFormatNumber = ChoosePixelFormat(context, &pfd);

		if (!pixelFormatNumber)
		{
			MessageBox(NULL, "Could not find a proper pixel format.",
				"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		SetPixelFormat(context, pixelFormatNumber, &pfd);

		HGLRC GLRC = wglCreateContext(context);


		if (!wglMakeCurrent(context, GLRC))
		{
			MessageBox(NULL, "Failed to make OpenGL as current context.",
				"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!gladLoadGL())
		{
			MessageBox(NULL, "Failed to load OpenGL (Glad).",
				"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	void Window::PollEvents()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));


		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::SwapBuffers()
	{
		::SwapBuffers(m_WindowContext);
	}

	LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		Application& app = Application::GetInstance();
		
		Window* wndptr = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		switch (msg)
		{
			case WM_CREATE:
			{
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lparam)->lpCreateParams);
				return 0;
			} break;

			case WM_KEYDOWN:
			{
				if (wparam == VK_ESCAPE)
				{
					DestroyWindow(wndptr->GetNativeWindow());
					return 0;
				}
			} break;
			
			case WM_LBUTTONDOWN:
			{
				//#TODO: Create a bitfield for this
				vec2<uint32_t> pos((lparam & 0xFFFF), ((lparam >> 16) & 0xFFFF));

				POINT pt = {};
				::ClientToScreen(wndptr->GetNativeWindow(), &pt);
				
				//app.OnMouseClicked(KeyCodes::CS_MOUSE_LBUTTON, pos);
				
				app.OnMouseClicked(KeyCodes::CS_MOUSE_LBUTTON, vec2<uint32_t>(pos.x, pos.y));

			} break;

			case WM_RBUTTONDOWN:
			{
				//#TODO: Call some sort of OnEvent of window, so it will be more clear on where we are beginning with events
				vec2<uint32_t> pos((lparam & 0xFFFF), ((lparam >> 16) & 0xFFFF));
				app.OnMouseClicked(KeyCodes::CS_MOUSE_RBUTTON, pos);

			} break;


			case WM_DESTROY: case WM_QUIT:
			{
				Application::GetInstance().Terminate();
				return 0;
			} break;
			
			default:
				return DefWindowProc(hwnd, msg, wparam, lparam); 
		}
	}

	Window::~Window()
	{
	}

	void Window::OnUpdate()
	{
		SwapBuffers();
		PollEvents();
	}

};