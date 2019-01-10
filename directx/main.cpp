#include <windows.h>
#include <math.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

struct vec3f {
	float x, y, z;
};

struct matrix {
	float mat[4][4];
};

matrix operator*(matrix& m1, matrix& m2);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Window Creation
	WNDCLASSEX wndClassEx = { sizeof(wndClassEx) };
	wndClassEx.lpfnWndProc = DefWindowProcA;
	wndClassEx.lpszClassName = "DirectX 11 Inverse";

	RegisterClassExA(&wndClassEx);

	HWND window = CreateWindowExA(0, 
				     "DirectX 11 Inverse",
				     "DirectX 11 Inverse",
				     WS_POPUP | WS_MAXIMIZE | WS_VISIBLE,
				     CW_USEDEFAULT,
				     CW_USEDEFAULT,
				     CW_USEDEFAULT,
				     CW_USEDEFAULT,
				     nullptr,
				     nullptr,
				     nullptr,
				     nullptr);
	
	// Direct3D Device Initialization
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	ID3D11Device1 *device;

	baseDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&device));

	ID3D11DeviceContext1 *deviceContext;

	baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&deviceContext));
				
