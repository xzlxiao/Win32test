/*--------------------------------------------------------------
SYSMETS2.cpp -- System Metrics DIsplay Program No.2
				(c) 肖镇龙， 2015
---------------------------------------------------------------*/

#include <windows.h>
#include <iostream>
#include <tchar.h>
#include "../SYSMETS/SYSMETS.h"
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SysMets2");
	HWND		 hwnd;
	MSG			 msg;
	WNDCLASS	 wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;					// 类风格p47，CS_HREDRAW窗口的水平尺寸和CS_VREDRAW垂直尺寸被改变，所有基于该窗口类的窗口都将被重新刷新
	wndclass.lpfnWndProc = WndProc;								// 注册窗口过程
	wndclass.cbClsExtra = 0;									// 两个字段用于在类结构和Win内部维护的窗口结构中预留一些额外的空间
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;								// 注册应用程序的实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// LoadIcon 加载图标，以供程序使用
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);				// LoadCursor 加载鼠标光标，以供程序使用
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// GetStockObject 获取一个图形对象。在本例中是一个用来对窗口背景进行重绘的图刷
	wndclass.lpszMenuName = NULL;								// 指定窗口类的菜单
	wndclass.lpszClassName = szAppName;							// 为窗口类赋予名称

	if (!RegisterClass(&wndclass))		// RegisterClass 为应用程序的窗口注册一个窗口类
	{
		MessageBox(NULL, TEXT("This program requires Windows NT"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,		// 窗口类名， CreateWindow 基于窗口类创建一个窗口
		TEXT("Get System Metrics No.2"),	// 窗口标题
		WS_OVERLAPPEDWINDOW | WS_VSCROLL, 		// 窗口风格， WS_VSCROLL是垂直滚动条，WS_HSCROLL是水平滚动条
		CW_USEDEFAULT, 				// 初始化x坐标
		CW_USEDEFAULT, 				// 初始化y坐标
		CW_USEDEFAULT,				// 初始化宽度
		CW_USEDEFAULT,				// 初始化高度
		NULL, 						// 父窗口句柄
		NULL,						// 窗口菜单句柄
		hInstance,					// 程序实例句柄
		NULL);						// 创建参数
	ShowWindow(hwnd, iCmdShow);			// ShowWindow 在屏幕中显示窗口
	UpdateWindow(hwnd);					// UpdateWindow 指示窗口对其自身进行重绘

	while (GetMessage(&msg, NULL, 0, 0))		// GetMessage 从消息队列获取信息
	{
		TranslateMessage(&msg);			// TranslateMessage 翻译一些键盘消息
		DispatchMessage(&msg);			// DispatchMessage 将消息发送给窗口过程
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;
	TEXTMETRIC tm;
	static int cxChar, cyChar, cxCaps,  cyClient, iVscrollPos;
	int i, y;
	TCHAR szBuffer[10];

	switch (message)
	{
	case WM_CREATE:
		//获取系统字体的宽度和高度
		hdc = GetDC(hwnd);												// 窗口客户区设备环境句柄，通常用于处理键盘消息和鼠标消息。使用该函数与ReleaseDC()结合使用，程序可以在收到用户的键盘或鼠标输入时及时地绘制客户区，而不必为了生成WM_PAINT消息去刻意使客户区的一部分无效化

		GetTextMetrics(hdc, &tm);										// 用于获取字体尺寸
		cxChar = tm.tmAveCharWidth;										// 系统字符的平均宽度
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;		// 大写字符平均宽度
		cyChar = tm.tmHeight + tm.tmExternalLeading;					// 系统字符的总高度
		ReleaseDC(hwnd, hdc);

		// 设置滚动条的范围， SetScrollRange(hwnd, iBar, iMin, iMax, bRedraw)
		// iBar:[SB_VERT, SB_HORZ]，bRedraw为滚动条自动重绘，如不需调用其它函数修改滚动条的显示，应设为TRUE
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1, FALSE);

		// 设置滚动条的位置，SetScrollPos(hwnd, iBar, iPos, bRedraw)
		// iPos是滚动条的新位置，
		SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint 标明窗口绘制开始

		for (i = 0; i < NUMLINES; i++)
		{
			y = cyChar * (i - iVscrollPos);

			TextOut(hdc, 0, y,				// y指定了每行字符的顶部相对于客户区的顶部的位置
				sysmetrics[i].szLabel,
				lstrlen(sysmetrics[i].szLabel));

			TextOut(hdc, 22 * cxCaps, y,
				sysmetrics[i].szDesc,
				lstrlen(sysmetrics[i].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);	// 后继TextOut函数调用的坐标从客户区的右上角开始。

			TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer,
				wsprintf(szBuffer, TEXT("%5d"),
					GetSystemMetrics(sysmetrics[i].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);	//	使更改的坐标恢复正常
		}
		EndPaint(hwnd, &ps);				// EndPaint 结束窗口绘制
		return 0;

	case WM_SIZE:
		// 获取客户区的高度，lParam的低位字是客户区的宽度，高位字是客户区的高度
		cyClient = HIWORD(lParam);
		return 0;

	//case WM_HSCROLL:
	case WM_VSCROLL:
		// 滚动条触发的通知p85
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:		// 页面向下移，滚轮向上移
			iVscrollPos -= 1;
			break;

		case SB_LINEDOWN:
			iVscrollPos += 1;
			break;

		case SB_PAGEUP:
			iVscrollPos -= cyClient / cyChar;		// cyClient / cyChar是垂直移动的行数
			break;

		case SB_PAGEDOWN:
			iVscrollPos += cyClient / cyChar;
			break;

		case SB_THUMBTRACK:
			iVscrollPos = HIWORD(wParam);
			break;

		default:
			break;
		}

		iVscrollPos = max(0, min(iVscrollPos, NUMLINES - 1));

		// GetScrollPos()获取滑动条当前位置，GetScrollRange获得当前范围 
		if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))
		{
			// 设置滚动条的位置，SetScrollPos(hwnd, iBar, iPos, bRedraw)
			SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);

			// InvalidateRect使整个窗口无效化，并生成WM_PAINT消息，但是WM_PAINT优先级较低，如果有其它
			// 高优先级消息，将导致窗口刷新延迟。可使用UpdateWindow(hwnd)函数
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage 将“退出”信息插入消息队列
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc 执行默认的消息处理
}