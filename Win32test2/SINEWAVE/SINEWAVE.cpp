/*--------------------------------------------------------------------
	HELLOWIN.cpp -- Sine Wave Using Polyline
					(C)	肖镇龙，2015
--------------------------------------------------------------------*/
#include <windows.h>
#include <iostream>
#include <math.h>

#define NUM		1000
#define TWOPI	(2 * 3.14159)

using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SineWave");
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
		TEXT("Sine Wave Using Polyline"),	// 窗口标题
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
	static int cxClient, cyClient;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	POINT apt[NUM];
	RECT rect;

	switch (message)
	{
	case WM_SIZE:
		// 获得客户区的高度和宽度
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint 标明窗口绘制开始

		MoveToEx(hdc, 0, cyClient / 2, NULL);		// 设置起始位点，MoveToEx的最后一个值返回的是一个指向POINT结构的指针，x、y字段表示运行该函数之前的当前位置。
		LineTo(hdc, cxClient, cyClient / 2);		// 画直线，设置直线的终点
		// 调用GetCurrentPositionEx(hdc, &pt)可以获取当前位置

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
		}
		Polyline(hdc, apt, NUM);  // 将POINT结构体数组中所有点依次连接起来

		/*
		// 画一个间隔像素为100的网格
		GetClientRect(hwnd, &rect);
		for (int x = 0; x < rect.right; x += 100)
		{
			MoveToEx(hdc, x, 0, NULL);
			LineTo(hdc, x, rect.bottom);
		}

		for (int y = 0; y < cyClient; y += 100)
		{
			MoveToEx(hdc, 0, y, NULL);
			LineTo(hdc, cxClient, y);
		}
		*/

		/*
		// 方框1
		{
			// case后面初始化变量需要用{}括起来
			struct point_test
			{
				long x;
				long y;
			}
			pts[] = { 100, 100, 200, 100, 200, 200, 100, 200, 100, 100 };
			MoveToEx(hdc, pts[0].x, pts[0].y, NULL);

			for (i = 1; i < 5; i++)
				LineTo(hdc, pts[i].x, pts[i].y);
		}
		*/

		/*
		// 方框2, Polyline不会改变当前位置
		{
			// case后面初始化变量需要用{}括起来
			POINT pts2[] = { 100, 100, 200, 100, 200, 200, 100, 200, 100, 100 };
			MoveToEx(hdc, pts2[0].x, pts2[0].y, NULL);

			Polyline(hdc, pts2, 5);
		}
		*/

		EndPaint(hwnd, &ps);				// EndPaint 结束窗口绘制
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage 将“退出”信息插入消息队列
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc 执行默认的消息处理
}