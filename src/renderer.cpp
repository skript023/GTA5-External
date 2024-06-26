#include "gui.hpp"
#include "Overlay.h"
#include "Functions.h"
#include "renderer.hpp"
#include "pointers.hpp"
#include "features.hpp"
#include "fonts/font_list.hpp"
#include "script.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace ellohim
{
	using namespace overlay;
	using namespace functions;

	LPCSTR TargetProcess = "GTA5.exe";
	bool ImGui_Initialised = false;
	bool CreateConsole = true;

	namespace Process
	{
		DWORD ID;
		HANDLE Handle;
		HWND Hwnd;
		WNDPROC WndProc;
		int WindowWidth;
		int WindowHeight;
		int WindowLeft;
		int WindowRight;
		int WindowTop;
		int WindowBottom;
		LPCSTR Title;
		LPCSTR ClassName;
		LPCSTR Path;
	}

	namespace OverlayWindow
	{
		WNDCLASSEX WindowClass;
		HWND Hwnd;
		LPCSTR Name;
	}

	namespace DirectX9Interface
	{
		IDirect3D9Ex* Direct3D9 = NULL;
		IDirect3DDevice9Ex* pDevice = NULL;
		D3DPRESENT_PARAMETERS pParams = { NULL };
		MARGINS Margin = { -1 };
		MSG Message = { NULL };
	}

	void renderer::input_handler()
	{
		for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;
		int button = -1;
		if (GetAsyncKeyState(VK_LBUTTON)) button = 0;
		if (button != -1) ImGui::GetIO().MouseDown[button] = true;
	}

	void renderer::draw_overlay()
	{
		char FpsInfo[64];
		sprintf(FpsInfo, "Overlay FPS: %0.f", ImGui::GetIO().Framerate);
		RGBA White = { 255,255,255,255 };
		DrawStrokeText(30, 44, &White, FpsInfo);
	}

	void renderer::on_present()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1) g_gui.m_opened = !g_gui.m_opened;
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		draw_overlay();
		ImGui::GetIO().MouseDrawCursor = g_gui.m_opened;

		if (g_gui.m_opened == true)
		{
			input_handler();

			ellohim::g_gui.dx_on_tick();

			SetWindowLong(OverlayWindow::Hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
			UpdateWindow(OverlayWindow::Hwnd);
			SetFocus(OverlayWindow::Hwnd);
		}
		else 
		{
			SetWindowLong(OverlayWindow::Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
			UpdateWindow(OverlayWindow::Hwnd);
		}
		ImGui::EndFrame();

		DirectX9Interface::pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (DirectX9Interface::pDevice->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());	
			DirectX9Interface::pDevice->EndScene();
		}

		HRESULT result = DirectX9Interface::pDevice->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && DirectX9Interface::pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	void renderer::render_on_tick()
	{
		static RECT OldRect;
		ZeroMemory(&DirectX9Interface::Message, sizeof(MSG));

		if (DirectX9Interface::Message.message != WM_QUIT)
		{
			if (PeekMessage(&DirectX9Interface::Message, OverlayWindow::Hwnd, 0, 0, PM_REMOVE)) {
				TranslateMessage(&DirectX9Interface::Message);
				DispatchMessage(&DirectX9Interface::Message);
			}
			HWND ForegroundWindow = GetForegroundWindow();
			if (ForegroundWindow == Process::Hwnd)
			{
				HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
				SetWindowPos(OverlayWindow::Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}

			RECT TempRect;
			POINT TempPoint;
			ZeroMemory(&TempRect, sizeof(RECT));
			ZeroMemory(&TempPoint, sizeof(POINT));

			GetClientRect(Process::Hwnd, &TempRect);
			ClientToScreen(Process::Hwnd, &TempPoint);

			TempRect.left = TempPoint.x;
			TempRect.top = TempPoint.y;
			ImGuiIO& io = ImGui::GetIO();
			ImGuiViewport viewport;
			viewport.PlatformHandleRaw = Process::Hwnd;

			if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom)
			{
				OldRect = TempRect;
				Process::WindowWidth = TempRect.right;
				Process::WindowHeight = TempRect.bottom;
				DirectX9Interface::pParams.BackBufferWidth = Process::WindowWidth;
				DirectX9Interface::pParams.BackBufferHeight = Process::WindowHeight;
				SetWindowPos(OverlayWindow::Hwnd, (HWND)0, TempPoint.x, TempPoint.y, Process::WindowWidth, Process::WindowHeight, SWP_NOREDRAW);
				DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
			}
			on_present();
		}
	}

	renderer::renderer()
	{
		init_overlay();
		setup_window();

		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9Interface::Direct3D9)))
		{
			throw std::runtime_error("DirectX 9 is not found");
		}

		D3DPRESENT_PARAMETERS Params = { 0 };
		Params.Windowed = TRUE;
		Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		Params.hDeviceWindow = OverlayWindow::Hwnd;
		Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		Params.BackBufferFormat = D3DFMT_A8R8G8B8;
		Params.BackBufferWidth = Process::WindowWidth;
		Params.BackBufferHeight = Process::WindowHeight;
		Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		Params.EnableAutoDepthStencil = TRUE;
		Params.AutoDepthStencilFormat = D3DFMT_D16;
		Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		if (FAILED(DirectX9Interface::Direct3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, OverlayWindow::Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9Interface::pDevice)))
		{
			DirectX9Interface::Direct3D9->Release();
			throw std::runtime_error("Unable create device directX 9");
		}

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui_ImplWin32_Init(OverlayWindow::Hwnd);
		ImGui_ImplDX9_Init(DirectX9Interface::pDevice);

		ImFontConfig font_cfg{};
		font_cfg.FontDataOwnedByAtlas = false;
		std::strcpy(font_cfg.Name, "Rubik");

		ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_rubik), sizeof(font_rubik), 14.f, &font_cfg, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

		ImGui::GetIO().Fonts->AddFontDefault();

		DirectX9Interface::Direct3D9->Release();

		g_renderer = this;
	}

	renderer::~renderer()
	{
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		if (DirectX9Interface::pDevice != NULL)
		{
			DirectX9Interface::pDevice->EndScene();
			DirectX9Interface::pDevice->Release();
		}
		if (DirectX9Interface::Direct3D9 != NULL)
		{
			DirectX9Interface::Direct3D9->Release();
		}
		DestroyWindow(OverlayWindow::Hwnd);
		UnregisterClass(OverlayWindow::WindowClass.lpszClassName, OverlayWindow::WindowClass.hInstance);

		g_renderer = nullptr;
	}
	
	LRESULT CALLBACK renderer::WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

		switch (Message)
		{
		case WM_DESTROY:
			if (DirectX9Interface::pDevice != NULL) {
				DirectX9Interface::pDevice->EndScene();
				DirectX9Interface::pDevice->Release();
			}
			if (DirectX9Interface::Direct3D9 != NULL) {
				DirectX9Interface::Direct3D9->Release();
			}
			PostQuitMessage(0);
			exit(4);
			break;
		case WM_SIZE:
			if (DirectX9Interface::pDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				DirectX9Interface::pParams.BackBufferWidth = LOWORD(lParam);
				DirectX9Interface::pParams.BackBufferHeight = HIWORD(lParam);
				HRESULT hr = DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
				if (hr == D3DERR_INVALIDCALL)
					IM_ASSERT(0);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
	}

	void renderer::setup_window()
	{
		OverlayWindow::WindowClass = {
			sizeof(WNDCLASSEX), 0, WinProc, 0, 0, nullptr, LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr, OverlayWindow::Name, LoadIcon(nullptr, IDI_APPLICATION)
		};

		RegisterClassEx(&OverlayWindow::WindowClass);
		if (Process::Hwnd)
		{
			static RECT TempRect = { NULL };
			static POINT TempPoint;
			GetClientRect(Process::Hwnd, &TempRect);
			ClientToScreen(Process::Hwnd, &TempPoint);
			TempRect.left = TempPoint.x;
			TempRect.top = TempPoint.y;
			Process::WindowWidth = TempRect.right;
			Process::WindowHeight = TempRect.bottom;
		}

		OverlayWindow::Hwnd = CreateWindowEx(NULL, OverlayWindow::Name, OverlayWindow::Name, WS_POPUP | WS_VISIBLE, Process::WindowLeft, Process::WindowTop, Process::WindowWidth, Process::WindowHeight, NULL, NULL, 0, NULL);
		DwmExtendFrameIntoClientArea(OverlayWindow::Hwnd, &DirectX9Interface::Margin);
		SetWindowLong(OverlayWindow::Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		ShowWindow(OverlayWindow::Hwnd, SW_SHOW);
		UpdateWindow(OverlayWindow::Hwnd);
	}

	DWORD WINAPI renderer::process_check(LPVOID lpParameter)
	{
		if (Process::Hwnd != NULL)
		{
			if (GetProcessId(TargetProcess) == 0)
			{
				exit(0);
			}
		}

		return EXIT_FAILURE;
	}

	void renderer::init_overlay()
	{
		if (CreateConsole == false)
			ShowWindow(GetConsoleWindow(), SW_HIDE);

		bool WindowFocus = false;
		while (WindowFocus == false)
		{
			DWORD ForegroundWindowProcessID;
			GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
			
			if (functions::GetProcessId(TargetProcess) == ForegroundWindowProcessID)
			{
				Process::ID = GetCurrentProcessId();
				Process::Handle = GetCurrentProcess();
				Process::Hwnd = GetForegroundWindow();

				RECT TempRect;
				GetWindowRect(Process::Hwnd, &TempRect);
				Process::WindowWidth = TempRect.right - TempRect.left;
				Process::WindowHeight = TempRect.bottom - TempRect.top;
				Process::WindowLeft = TempRect.left;
				Process::WindowRight = TempRect.right;
				Process::WindowTop = TempRect.top;
				Process::WindowBottom = TempRect.bottom;

				char TempTitle[MAX_PATH];
				GetWindowText(Process::Hwnd, TempTitle, sizeof(TempTitle));
				Process::Title = TempTitle;

				char TempClassName[MAX_PATH];
				GetClassName(Process::Hwnd, TempClassName, sizeof(TempClassName));
				Process::ClassName = TempClassName;

				char TempPath[MAX_PATH];
				GetModuleFileNameEx(Process::Handle, NULL, TempPath, sizeof(TempPath));
				Process::Path = TempPath;

				LOG(INFO) << "Process found";

				WindowFocus = true;
			}
		}

		OverlayWindow::Name = "External Base";
	}
}
