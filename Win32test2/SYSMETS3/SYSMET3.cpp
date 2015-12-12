/*--------------------------------------------------------------------
	SYSMETS3.cpp -- System Metrics DIsplay Program No.3
				(c) 肖镇龙， 2015
--------------------------------------------------------------------*/
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include "../SYSMETS/SYSMETS.h"
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SysMets3");
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
		TEXT("Get System Metrics No.3"),	// 窗口标题
		WS_OVERLAPPEDWINDOW, 		// 窗口风格
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
	static int cxChar, cyChar, cxCaps, cyClient,cxClient, iMaxWidth;
	int i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;
	TCHAR szBuffer[10];
	SCROLLINFO si; 
	/*
	SCROLLINFO
	{
		UINT cbSize;	// 设为sizeof (SCROLLINFO)
		UINT fMask;		// 要设置或获取的值
		int nMin;		// 范围的最小值
		int nMax;		// 范围的最大值
		UINT nPage;		// 页面大小
		int nPos;		// 当前位置
		int nTrackPos;	// 当前追踪位置
	*/

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

		// Save the width of the three column
		iMaxWidth = 40 * cxChar + 22 * cxCaps;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint 标明窗口绘制开始

		// 获取垂直滚动条位置

		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd, SB_VERT, &si);
		iVertPos = si.nPos;

		// 获取水平滚动条信息

		GetScrollInfo(hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		// 找到绘图限制

		iPaintBeg = max(0, iVertPos + ps.rcPaint.top / cyChar);
		iPaintEnd = min(NUMLINES - 1, iVertPos + ps.rcPaint.bottom / cyChar);

		for (i = iPaintBeg; i <= iPaintEnd; i++)
		{
			x = cxChar * (1 - iHorzPos);
			y = cyChar * (i - iVertPos);

			TextOut(hdc, x, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(hdc, x + 22 * cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);

			TextOut(hdc, x + 22 * cxCaps + 40 * cxChar, y, szBuffer, wsprintf(szBuffer, TEXT("&%5d"), GetSystemMetrics(sysmetrics[i].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}

		EndPaint(hwnd, &ps);				// EndPaint 结束窗口绘制
		return 0;

	case WM_SIZE:
		// 获取客户区的宽度和高度，lParam的低位字是客户区的宽度，高位字是客户区的高度
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		// 设置垂直滚动条的范围和页面大小
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;

		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		// 设置水平滚动条的范围和页面大小
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 2 + iMaxWidth / cxChar;
		si.nPage = cxClient / cxChar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		return 0;

		//case WM_HSCROLL:
	case WM_VSCROLL:
		// 得到所有垂直滚动条的信息
		si.cbSize = sizeof(si);		// 在调用SetScrollInfo和GetScrollInfo两个函数之前，必须设置cbSize字段为该结构的大小
		si.fMask = SIF_ALL;			// SIF_ALL标志是SIF_RANGE、SIF_POS、SIF_PAGE和SIF_TRACKPOS组合。
		GetScrollInfo(hwnd, SB_VERT, &si);

		// 保存位置，之后比较
		iVertPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_TOP:
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;

		case SB_LINEUP:
			si.nPos -= 1;
			break;

		case SB_LINEDOWN:
			si.nPos += 1;
			break;

		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}
		// Set the position and then retrieve it. Due to adjustments by Windows it may not be the same as the value set.

		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hwnd, SB_VERT, &si);

		// 如果位置改变，滚动窗口并刷新

		if (si.nPos != iVertPos)
		{
			// ScroWindow的第二个参数指定了客户区水平滚动的像素，第三个参数指定了客户区垂直滚动的像素。
			ScrollWindow(hwnd, 0, cyChar*(iVertPos - si.nPos), NULL, NULL);
			UpdateWindow(hwnd);
		}

		return 0;

	case WM_HSCROLL:
		// 获取所有垂直滚动条的信息
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;

		// Save the position for comparison later on

		GetScrollInfo(hwnd, SB_VERT, &si);
		iHorzPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			si.nPos -= 1;
			break;

		case SB_LINERIGHT:
			si.nPos += 1;
			break;

		case SB_PAGELEFT:
			si.nPos -= si.nPage;
			break;

		case SB_PAGERIGHT:
			si.nPos += si.nPage;
			break;

		case SB_THUMBPOSITION:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}
		// Set the position and then retrieve it. Due to adjustments by Windows it may not be the same as the value set.

		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		GetScrollInfo(hwnd, SB_HORZ, &si);

		//If the position has changed, scroll the window

		if (si.nPos != iHorzPos)
		{
			ScrollWindow(hwnd, cxChar*(iHorzPos - si.nPos), 0, NULL, NULL);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage 将“退出”信息插入消息队列
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc 执行默认的消息处理
}