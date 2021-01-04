#include <windows.h>
#include <iostream>

void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD)
{
    static POINT prevCursorPos{};

    POINT currentCursorPos;
    ::GetCursorPos(&currentCursorPos);

    if ((prevCursorPos.x != currentCursorPos.x) ||
        (prevCursorPos.y != currentCursorPos.y))
    {
        prevCursorPos = currentCursorPos;

        if (const auto window = ::WindowFromPoint(currentCursorPos))
        {
            DWORD_PTR result{};
            if (::SendMessageTimeoutW(window, WM_NCHITTEST, 0, MAKELPARAM(currentCursorPos.x, currentCursorPos.y), SMTO_NORMAL, 100, &result))
            {
                std::cout << "window: " << window << " - ";// << result << std::endl;
                switch (result)
                {
                    case HTERROR: std::cout << "HTERROR"; break;
                    case HTTRANSPARENT: std::cout << "HTTRANSPARENT"; break;
                    case HTNOWHERE: std::cout << "HTNOWHERE"; break;
                    case HTCLIENT: std::cout << "HTCLIENT"; break;
                    case HTCAPTION: std::cout << "HTCAPTION"; break;
                    case HTSYSMENU: std::cout << "HTSYSMENU"; break;
                    case HTGROWBOX: std::cout << "HTGROWBOX"; break;
                    case HTMENU: std::cout << "HTMENU"; break;
                    case HTHSCROLL: std::cout << "HTHSCROLL"; break;
                    case HTVSCROLL: std::cout << "HTVSCROLL"; break;
                    case HTMINBUTTON: std::cout << "HTMINBUTTON"; break;
                    case HTMAXBUTTON: std::cout << "HTMAXBUTTON"; break;
                    case HTLEFT: std::cout << "HTLEFT"; break;
                    case HTRIGHT: std::cout << "HTRIGHT"; break;
                    case HTTOP: std::cout << "HTTOP"; break;
                    case HTTOPLEFT: std::cout << "HTTOPLEFT"; break;
                    case HTTOPRIGHT: std::cout << "HTTOPRIGHT"; break;
                    case HTBOTTOM: std::cout << "HTBOTTOM"; break;
                    case HTBOTTOMLEFT: std::cout << "HTBOTTOMLEFT"; break;
                    case HTBOTTOMRIGHT: std::cout << "HTBOTTOMRIGHT"; break;
                    case HTBORDER: std::cout << "HTBORDER"; break;
                    case HTOBJECT: std::cout << "HTOBJECT"; break;
                    case HTCLOSE: std::cout << "HTCLOSE"; break;
                    case HTHELP: std::cout << "HTHELP"; break;
                    default: std::cout << "UNEXPECTED RESULT"; break;
                }
                std::cout << std::endl;
            }
        }
    }
}

int main()
{
    WNDCLASSW wc{ sizeof(wc) };
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = ::GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"HitTester";
    RegisterClassW(&wc);

    auto window = ::CreateWindowEx(0, wc.lpszClassName, nullptr, WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, ::GetModuleHandle(nullptr), nullptr);
    if (window)
    {
        ::SetTimer(window, 42, 1000, TimerProc);

        MSG msg {};
        while (::GetMessageW(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    return 0;
}
