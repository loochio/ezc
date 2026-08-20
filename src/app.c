// app.c

#include "app.h"

typedef struct {
	bool exit;
} AppState;

AppState g_app;

void app_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
};

LRESULT CALLBACK MainWindowCallback(
	HWND window, 
	UINT message, 
	WPARAM wParam, 
	LPARAM lParam)
{
	LRESULT result = 0;

	// Window Notifications: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-notifications
	switch(message) {
		case WM_SIZE:
			app_log("WM_SIZE");
			break;

		case WM_DESTROY:
			app_log("WM_DESTROY");
			break;

		case WM_CLOSE:
			app_log("WM_CLOSE");
			g_app.exit = true;
			break;

		case WM_ACTIVATEAPP:
			app_log("WM_ACTIVATEAPP");
			break;

		case WM_PAINT:
			app_log("WM_PAINT");
			PAINTSTRUCT paint;
			HDC device_context  = BeginPaint(window, &paint);
			LONG x = paint.rcPaint.left;
			LONG y = paint.rcPaint.top;
			LONG width = paint.rcPaint.right - paint.rcPaint.left;
			LONG height = paint.rcPaint.bottom - paint.rcPaint.top;
			PatBlt(device_context, x, y, width, height, WHITENESS);
			EndPaint(window, &paint);;
			break;

		default:
			result = DefWindowProc(window, message, wParam, lParam);
			break;
	}

	return result;
}

int CALLBACK WinMain(
	  HINSTANCE Instance,
	  HINSTANCE PrevInstance,
	  LPSTR     CommandLine,
	  int       ShowCode)
{
	app_log("[APP] running\n");

	WNDCLASS wc = {0};
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWindowCallback;
    wc.hInstance = Instance; // can also use GetModuleHandle(NULL);
    wc.lpszClassName = "ezcClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND window = CreateWindow("ezcClass", "ezc engine",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
        100, 100, 800, 600,
        NULL, NULL, wc.hInstance, NULL);

    MSG message;
    while (!g_app.exit && GetMessage(&message, NULL, 0, 0) != 0) {
    	TranslateMessage(&message);
    	DispatchMessage(&message);
    }


    //@TODO opengl implementations
    //HDC hdc = GetDC(window);

   	//PIXELFORMATDESCRIPTOR pfd = {0};
    //pfd.nSize = sizeof(pfd);
    //pfd.nVersion = 1;
    //pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    //pfd.iPixelType = PFD_TYPE_RGBA;
    //pfd.cColorBits = 32;
    //SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);
    //wglMakeCurrent(hdc, wglCreateContext(hdc));
//
    //MSG msg;
    //{
    ////while (GetMessage(&msg, NULL, 0, 0) > 0) {
    //    
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    glColor3f(1.0f, 0.5f, 0.5f);
    //    glBegin(GL_TRIANGLES);
    //        glVertex2f(-0.5f, -0.5f);
    //        glVertex2f( 0.5f, -0.5f);
    //        glVertex2f( 0.0f,  0.5f);
    //    glEnd();
    //    SwapBuffers(hdc);
//
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);
    //}

    //while(true) {
    //	printf("tick\n");
    //	Sleep(1000);
    //}

    app_log("[ENGINE] shutting down");
    DestroyWindow(window);

	return 0;
}

