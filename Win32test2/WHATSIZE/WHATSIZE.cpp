/*--------------------------------------------------------------------
	WHATSIZE.cpp -- What Size is the Window? ��5�ж���ӳ��ģʽ��ʾ��
	�ڿͻ����ߴ�
			(C)	Ф������2015
--------------------------------------------------------------------*/
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("WhatSize");
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
		TEXT("What Size is the Window?"),	// ���ڱ���
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

void Show(HWND hwnd, HDC hdc, int xText, int yText, int iMapMode, TCHAR *szMapMode)
{
	TCHAR szBUFFER[60];
	RECT 
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;

	switch (message)
	{
	case WM_CREATE:
		//��ȡϵͳ����Ŀ�Ⱥ͸߶�
		hdc = GetDC(hwnd);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ
		EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����

}
