/* nuklear - 1.32.0 - public domain */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_GDIP_IMPLEMENTATION

#include "gui/nuklear/nuklear.h"

extern "C" {
#include "nuklear_gdip.h"
}

//GUI Includes
#include "gui/lib/screen_manager.hpp"
#include "gui/screens/screen_drivers.hpp"
#include "gui/model/driver.hpp"
#include <memory>
#include <vector>


/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
static LRESULT CALLBACK
WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    if (nk_gdip_handle_event(wnd, msg, wparam, lparam))
        return 0;
    return DefWindowProcW(wnd, msg, wparam, lparam);
}

int main(void)
{
    GdipFont* font;
    struct nk_context *ctx;

    WNDCLASSW wc;
    RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD exstyle = WS_EX_APPWINDOW;
    HWND wnd;
    int running = 1;
    int needs_refresh = 1;

    /* Win32 */
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandleW(0);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"NuklearWindowClass";
    RegisterClassW(&wc);

    AdjustWindowRectEx(&rect, style, FALSE, exstyle);

    wnd = CreateWindowExW(exstyle, wc.lpszClassName, L"Nuklear Demo",
        style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, wc.hInstance, NULL);

    /* GUI */
    ctx = nk_gdip_init(wnd, WINDOW_WIDTH, WINDOW_HEIGHT);
    font = nk_gdipfont_create("Arial", 12);
    nk_gdip_set_font(font);

    //Manager initialization
    ScreenManager screenManager = {};
    std::vector<Driver> driverList = {}; //Load from memory
    screenManager.set(std::make_shared<ScreenDrivers>(screenManager, driverList));

    while (running)
    {
        /* Input */
        MSG msg;
        nk_input_begin(ctx);
        if (needs_refresh == 0) {
            if (GetMessageW(&msg, NULL, 0, 0) <= 0)
                running = 0;
            else {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            needs_refresh = 1;
        } else needs_refresh = 0;
        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                running = 0;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
            needs_refresh = 1;
        }
        nk_input_end(ctx);

        /* GUI */
        if (nk_begin(ctx, "eForce STW GUI", nk_rect(0, 0, 400, 800), 0))
        {
            screenManager.drawCurrent(ctx);
        }
        nk_end(ctx);

        /* Draw */
        nk_gdip_render(NK_ANTI_ALIASING_ON, nk_rgb(30,30,30));
    }

    nk_gdipfont_del(font);
    nk_gdip_shutdown();
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}
