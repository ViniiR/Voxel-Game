#ifndef UNICODE
#define UNICODE
#endif

#include "src/hpp/initSDL.hpp"
#include <windows.h>
#include <cstdio>
#include "wincon.h"
#include "winuser.h"
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
        case WM_LBUTTONDOWN:
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateConsole() {
    AllocConsole();
    SetConsoleTitleA("DBGC");

    FILE *STREAM;
    freopen_s(&STREAM, "CONOUT$", "w", stdout);
    freopen_s(&STREAM, "CONOUT$", "w", stderr);
    freopen_s(&STREAM, "CONOUT$", "r", stdin);

    std::cout << "DBGC started" << std::endl;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    CreateConsole();
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0,                    // Optional window styles.
                               CLASS_NAME,           // Window class
                               L"V9",                // Window text
                               WS_OVERLAPPEDWINDOW,  // Window style

                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               CW_USEDEFAULT,

                               nullptr,    // Parent window
                               nullptr,    // Menu
                               hInstance,  // Instance handle
                               nullptr     // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

/*int main(int argc, char* argv[]) {*/
/*if (!initSDL()) {*/
/*    return -1;*/
/*}*/
/*return 0;*/
/*}*/

#include <SDL2/SDL_main.h>
