/*--------------------------------------------------------------------
	HELLOWIN.cpp -- Sine Wave Using Polyline
					(C)	Ф������2015
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

	wndclass.style = CS_HREDRAW | CS_VREDRAW;					// ����p47��CS_HREDRAW���ڵ�ˮƽ�ߴ��CS_VREDRAW��ֱ�ߴ类�ı䣬���л��ڸô�����Ĵ��ڶ���������ˢ��
	wndclass.lpfnWndProc = WndProc;								// ע�ᴰ�ڹ���
	wndclass.cbClsExtra = 0;									// �����ֶ���������ṹ��Win�ڲ�ά���Ĵ��ڽṹ��Ԥ��һЩ����Ŀռ�
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;								// ע��Ӧ�ó����ʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// LoadIcon ����ͼ�꣬�Թ�����ʹ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);				// LoadCursor ��������꣬�Թ�����ʹ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// GetStockObject ��ȡһ��ͼ�ζ����ڱ�������һ�������Դ��ڱ��������ػ��ͼˢ
	wndclass.lpszMenuName = NULL;								// ָ��������Ĳ˵�
	wndclass.lpszClassName = szAppName;							// Ϊ�����ำ������

	if (!RegisterClass(&wndclass))		// RegisterClass ΪӦ�ó���Ĵ���ע��һ��������
	{
		MessageBox(NULL, TEXT("This program requires Windows NT"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,		// ���������� CreateWindow ���ڴ����ഴ��һ������
		TEXT("Sine Wave Using Polyline"),	// ���ڱ���
		WS_OVERLAPPEDWINDOW, 		// ���ڷ��
		CW_USEDEFAULT, 				// ��ʼ��x����
		CW_USEDEFAULT, 				// ��ʼ��y����
		CW_USEDEFAULT,				// ��ʼ�����
		CW_USEDEFAULT,				// ��ʼ���߶�
		NULL, 						// �����ھ��
		NULL,						// ���ڲ˵����
		hInstance,					// ����ʵ�����
		NULL);						// ��������
	ShowWindow(hwnd, iCmdShow);			// ShowWindow ����Ļ����ʾ����
	UpdateWindow(hwnd);					// UpdateWindow ָʾ���ڶ�����������ػ�

	while (GetMessage(&msg, NULL, 0, 0))		// GetMessage ����Ϣ���л�ȡ��Ϣ
	{
		TranslateMessage(&msg);			// TranslateMessage ����һЩ������Ϣ
		DispatchMessage(&msg);			// DispatchMessage ����Ϣ���͸����ڹ���
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
		// ��ÿͻ����ĸ߶ȺͿ��
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ

		MoveToEx(hdc, 0, cyClient / 2, NULL);		// ������ʼλ�㣬MoveToEx�����һ��ֵ���ص���һ��ָ��POINT�ṹ��ָ�룬x��y�ֶα�ʾ���иú���֮ǰ�ĵ�ǰλ�á�
		LineTo(hdc, cxClient, cyClient / 2);		// ��ֱ�ߣ�����ֱ�ߵ��յ�
		// ����GetCurrentPositionEx(hdc, &pt)���Ի�ȡ��ǰλ��

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
		}
		Polyline(hdc, apt, NUM);  // ��POINT�ṹ�����������е�������������

		/*
		// ��һ���������Ϊ100������
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
		// ����1
		{
			// case�����ʼ��������Ҫ��{}������
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
		// ����2, Polyline����ı䵱ǰλ��
		{
			// case�����ʼ��������Ҫ��{}������
			POINT pts2[] = { 100, 100, 200, 100, 200, 200, 100, 200, 100, 100 };
			MoveToEx(hdc, pts2[0].x, pts2[0].y, NULL);

			Polyline(hdc, pts2, 5);
		}
		*/

		EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����
}