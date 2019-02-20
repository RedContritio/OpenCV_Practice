#ifndef __REDCONTRITIO_MAIN__DEF
#define __REDCONTRITIO_MAIN__DEF
#pragma once

#include <windows.h>

#include "BufferLayer.h"
#include "StandardWindow.h"
#include "Timer.h"

namespace RedContritio
{
	namespace RedContritioMain_
	{
		static const char *MainTitleName = "Fuck OpenCV";
		static const char *MainClassName = "Fuck imshow";
		static int cxClient ,cyClient ;
		
		static inline void GetClientArguments(HWND hwnd)
		{
			RECT rect ;
			GetClientRect(hwnd, &rect);
			cxClient = rect.right ;
			cyClient = rect.bottom ;
		}

		static BUFFERLAYER BackBuffer;

		void (*WindowProcPainter)(HDC );

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
		{
			GetClientArguments(hwnd);
			switch(msg)
			{
				case WM_CREATE:
				{
					srand((unsigned)time(NULL));
					BackBuffer.ResetBufferLayer(hwnd);
					GetClientArguments(hwnd);
					break ;
				}
				case WM_PAINT:
				{
					PAINTSTRUCT ps ;
					BeginPaint(hwnd, &ps);
					BitBlt(BackBuffer.getHdc(), 0, 0, cxClient, cyClient, NULL, 0, 0, WHITENESS);
					if(WindowProcPainter) WindowProcPainter(BackBuffer.getHdc());
					BitBlt(ps.hdc, 0, 0, cxClient, cyClient, BackBuffer.getHdc(), 0, 0, SRCCOPY);
					EndPaint(hwnd, &ps);
					break ;
				}
				case WM_DESTROY:
				{
					BackBuffer.DeleteBufferLayer();
					PostQuitMessage(0);
					break;
				}
				case WM_KEYDOWN :
				{
					SendMessage(hwnd ,WM_DESTROY ,NULL ,NULL );
					break;
				}
				case WM_SIZE :
				{
					GetClientArguments(hwnd );
					BackBuffer.AdjustSize(hwnd );
					break ;
				}
				default:
					break ;
			}
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
}

void RegisterRedContritioPainter(void (*f)(HDC))
{
	RedContritio::RedContritioMain_::WindowProcPainter = f;
}

int RedContritioMain(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX winClass ;
	RedContritio::InitializeWindowClass(&winClass, RedContritio::RedContritioMain_::WindowProc, hInstance, RedContritio::RedContritioMain_::MainClassName);

	if(!RegisterClassEx(&winClass)) return 0 ;
	HWND hwnd = RedContritio::CreateVisibleWindow(RedContritio::RedContritioMain_::MainClassName, 
		RedContritio::RedContritioMain_::MainTitleName, 1024, 768, hInstance);
	if(!hwnd ) return 0 ;
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	RedContritioMain();

	bool EndFlag = false;
	RedContritio::Timer timer(2);
	MSG msg ;
	while(!EndFlag )
	{
		while(PeekMessage(&msg ,NULL ,0 ,0 ,PM_REMOVE )!= 0)
		{
			if(msg.message == WM_QUIT )
			{
				EndFlag = true ;
			}
			TranslateMessage(&msg );
			DispatchMessage(&msg );
		}

		
		if(timer.ReadyForNextFrame())
		{
			InvalidateRect(hwnd, NULL, true);
			UpdateWindow(hwnd);
		}

	}

	UnregisterClass(RedContritio::RedContritioMain_::MainClassName ,winClass.hInstance );
	return 0;
}


#endif