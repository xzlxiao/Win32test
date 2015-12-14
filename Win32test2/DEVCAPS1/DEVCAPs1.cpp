/*--------------------------------------------------------------
	DEVCAPS1.cpp -- Device Capabilities Display Program No.1
				(c) 肖镇龙， 2015
---------------------------------------------------------------*/

#include <windows.h>
#include <iostream>
#include <tchar.h>
using namespace std;

#define NUMLINES ((int)(sizeof devcaps / sizeof devcaps[0]))
struct
{
	int iIndex;
	TCHAR *szLabel;
	TCHAR *szDesc;
}

// 结构体数组的iIndex储存的是GetDeviceCaps的第二个参数
devcaps[] =
{
	HORZSIZE, TEXT("HORZSIZE"),TEXT("Width in millimeters:"),

	VERTSIZE, TEXT("VERTSIZE"),TEXT("Height in millimeters:"),

	HORZRES, TEXT("HORZRES"), TEXT("Width in pixels:"),

	VERTRES, TEXT("VERTRES"), TEXT("Height in raster lines:"),

	// 每个像素的颜色位数
	BITSPIXEL, TEXT("BITSPIXEL"),TEXT("Color bits per pixel:"),

	// 色彩平面
	PLANES, TEXT("PLANES"), TEXT("Number of color planes:"),

	NUMBRUSHES, TEXT("NUMBRUSHES"), TEXT("Number of device brushes:"),

	NUMPENS, TEXT("NUMPENS"), TEXT("Number of device pens:"),

	NUMMARKERS, TEXT("NUMMARKERS"), TEXT("Number of device markers:"),

	NUMFONTS, TEXT("NUMFONTS"), TEXT("Number of device fonts:"),

	NUMCOLORS, TEXT("NUMCOLORS"), TEXT("Number of device colors:"),

	PDEVICESIZE, TEXT("PDEVICESIZE"), TEXT("Size of device structure:"),

	// 每一像素点的宽度
	ASPECTX, TEXT("ASPECTX"), TEXT("Relative width of pixel:"),

	// 每一像素点的高度
	ASPECTY, TEXT("ASPECTY"), TEXT("Relative height of pixel:"),

	// 每一像素点的对角线长度
	ASPECTXY, TEXT("ASPECTXY"), TEXT("Relative diagonal of pixel:"),

	// 逻辑像素：以每英寸的像素数计算的非实际分辨率
	LOGPIXELSX, TEXT("LOGPIXELSX"), TEXT("Horizontal dots per inch:"),

	LOGPIXELSY, TEXT("LOGPIXELSY"), TEXT("Vertical dots per inch:"),

	SIZEPALETTE, TEXT("SIZEPALETTE"), TEXT("Number of palette entries:"),

	NUMRESERVED, TEXT("NUMRESERVED"), TEXT("Reserved palette entries:"),

	COLORRES, TEXT("COLORRES"), TEXT("Actual color resolution:")
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("DevCaps1");
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
		TEXT("Device Capabilities"),	// 窗口标题
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
	static int cxChar, cyChar, cxCaps;
	int i;
	TCHAR szBuffer[10];

	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME|SND_ASYNC);		// PlaySound 播放声音文件

		//获取系统字体的宽度和高度
		hdc = GetDC(hwnd);												// 窗口客户区设备环境句柄，通常用于处理键盘消息和鼠标消息。使用该函数与ReleaseDC()结合使用，程序可以在收到用户的键盘或鼠标输入时及时地绘制客户区，而不必为了生成WM_PAINT消息去刻意使客户区的一部分无效化
		GetTextMetrics(hdc, &tm);										// 用于获取字体尺寸
		cxChar = tm.tmAveCharWidth;										// 系统字符的平均宽度
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;		// 大写字符平均宽度
		cyChar = tm.tmHeight + tm.tmExternalLeading;					// 系统字符的总高度
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint 标明窗口绘制开始

		for (i = 0; i < NUMLINES; i++)
		{
			TextOut(hdc, 0, cyChar *i,				// cyChar * i指定了每行字符的顶部相对于客户区的顶部的位置
				devcaps[i].szLabel,
				lstrlen(devcaps[i].szLabel));

			TextOut(hdc, 14 * cxCaps, cyChar * i,
				devcaps[i].szDesc,
				lstrlen(devcaps[i].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);	// 后继TextOut函数调用的坐标从客户区的右上角开始。

			TextOut(hdc, 14 * cxCaps + 35 * cxChar, cyChar*i, szBuffer,
				wsprintf(szBuffer, TEXT("%5d"),
					GetDeviceCaps(hdc, devcaps[i].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);	//	使更改的坐标恢复正常
		}

		// 通过GetSystemMetrics获取屏幕分辨率，问题是得到的值只有真实值的一半
		TextOut(hdc, 0, (NUMLINES + 1) * cyChar, L"水平分辨率",  wcslen(L"水平分辨率"));
		TextOut(hdc, 14 * cxCaps, cyChar * (NUMLINES + 1), szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(SM_CXSCREEN)));
		TextOut(hdc, 0, (NUMLINES + 2) * cyChar, L"垂直分辨率", wcslen(L"垂直分辨率"));
		TextOut(hdc, 14 * cxCaps, cyChar * (NUMLINES + 2), szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(SM_CYSCREEN)));
		EndPaint(hwnd, &ps);				// EndPaint 结束窗口绘制
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage 将“退出”信息插入消息队列
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc 执行默认的消息处理
}