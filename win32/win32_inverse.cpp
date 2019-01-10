#include <windows.h>

// Explicit definition of possible uses of static keyword
#define internal static 
#define local_persist static 
#define global_variable static 

// These are global for now but not for long
global_variable bool Running;
global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable HBITMAP Bitmap;
global_variable HDC BitmapDeviceContext;


internal void Win32ResizeDIBSection(int Width, int Height) {
	// TODO(Bishoy): Maybe don't free memory first but free after
	if (Bitmap) {
		DeleteObject(Bitmap);
	} 

	if (!BitmapDeviceContext) {
		BitmapDeviceContext = CreateCompatibleDC(0);
	}

	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader); // size of header before color table
	BitmapInfo.bmiHeader.biWidth = Width;          // width of drawable area
	BitmapInfo.bmiHeader.biHeight = Height;        // height of drawable area
	BitmapInfo.bmiHeader.biPlanes = 1;             // Not relevant anymore, Windows APIs suck, just set to 1
	BitmapInfo.bmiHeader.biBitCount = 32;          // 8 bits for Red, 8 bits for Green, and 8 bits for Blue
	BitmapInfo.bmiHeader.biCompression = BI_RGB;   // We use uncompressed RGB

	Bitmap = CreateDIBSection(BitmapDeviceContext,
			          &BitmapInfo,
			          DIB_RGB_COLORS,
			          &BitmapMemory,
			          0,
			          0);
}

internal void Win32UpdateWindow(HDC DeviceContext, int X, int Y, int Width, int Height) {
	StretchDIBits(DeviceContext,
		      X,
		      Y,
		      Width,
	              Height,
		      X,
		      Y,
		      Width,
		      Height,
		const VOID *lpBits,
		const BITMAPINFO *lpBitsInfo,
		      DIB_RGB_COLORS,
		      SRCCOPY);
}

LRESULT CALLBACK Win32MainWindowCallback(HWND Window,
		   		    UINT Message,
		   		    WPARAM WParam,
		   		    LPARAM LParam)
{
	LRESULT Result = 0;

	switch(Message) {
		case WM_SIZE:
			{
				RECT ClientRect;
				GetClientRect(Window, &ClientRect);
				int Width = ClientRect.right - ClientRect.left;
				int Height = ClientRect.bottom - ClientRect.top;
				Win32ResizeDIBSection(Width, Height);
				OutputDebugStringA("WM_SIZE\n");
			} break;
		case WM_CLOSE:
			{
				// TODO(Bishoy): Handle this with a message to the user
				Running = false;
			} break;
		case WM_ACTIVATEAPP:
			{
				OutputDebugStringA("WM_ACTIVATEAPP\n");
			} break;
		case WM_DESTROY:
			{
				// TODO(Bishoy): Handle this as an error - recreate window?
				Running = false;
			} break;
		case WM_PAINT:
			{
				PAINTSTRUCT Paint;
				HDC DeviceContext = BeginPaint(Window, &Paint);
				int X = Paint.rcPaint.left;
				int Y = Paint.rcPaint.top;
				int width = Paint.rcPaint.right - Paint.rcPaint.left;
				int height = Paint.rcPaint.bottom - Paint.rcPaint.top;
				Win32UpdateWindow(DeviceContext, X, Y, Width, Height);
				EndPaint(Window, &Paint);
			} break;
		default:
			{
				Result = DefWindowProc(Window, Message, WParam, LParam);
			} break;
	}

	return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance,
	             HINSTANCE hPrevInstance,
	             LPSTR lpCmdLine,
	             int nShowCmd)
{
	WNDCLASS WindowClass = {};
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = "Inverse Engine";

	if (RegisterClassA(&WindowClass)) {
		HWND Window = CreateWindowExA(0,
					      "Inverse Engine",
					      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					      CW_USEDEFAULT,
					      CW_USEDEFAULT,
					      CW_USEDEFAULT,
					      CW_USEDEFAULT,
					      nullptr,
					      nullptr,
					      Instance,
					      nullptr);
		if (Window) {
			Running = true;
			while (Running) {
				MSG Message;
				bool MessageResult = GetMessageA(&Message, 0, 0, 0);
				if (MessageResult > 0) {
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				} else {
					break;
				}
			}
		} else {
			// TODO(Bishoy) Logging
		}
	} else {
		// TODO(Bishoy) Logging
	}

	return 0;
}
