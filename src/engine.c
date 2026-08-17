// engine.c

#include "engine.h"

void E_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
};

void E_run(HINSTANCE hInstance) {
	E_log("[ENGINE] running\n");

	WNDCLASS wc = {0};
	wc.style = ;
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance; // can also use GetModuleHandle(NULL);
    wc.lpszClassName = "ezc";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("ezc", "ezc engine",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 800, 600,
        NULL, NULL, wc.hInstance, NULL);

    HDC hdc = GetDC(hwnd);

   	PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);
    wglMakeCurrent(hdc, wglCreateContext(hdc));

    MSG msg;
    {
    //while (GetMessage(&msg, NULL, 0, 0) > 0) {
        
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.5f, 0.5f);
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.0f,  0.5f);
        glEnd();
        SwapBuffers(hdc);

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    while(true) {
    	printf("tick\n");
    	Sleep(1000);
    }

    E_log("[ENGINE] shutting down");
    DestroyWindow(hwnd);
}

