/*--------------------------------------------------------------------
	HELLOWIN.cpp -- Line-Drawing Demonstration Program
						(C)	Ф������2015
--------------------------------------------------------------------*/
#include <windows.h>
#include <iostream>
#include <tchar.h>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT(":ineDemo");
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
		TEXT("Line Demonstration"),	// ���ڱ���
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
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ

		// �����β���䣬Ĭ���ǰ�ɫ
		Rectangle(hdc, cxClient / 8, cyClient / 8,
			7 * cxClient / 8, 7 * cyClient / 8);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, cxClient, cyClient);

		MoveToEx(hdc, 0, cyClient, NULL);
		LineTo(hdc, cxClient, 0);
		
		// ��Բ
		Ellipse(hdc, cxClient / 8, cyClient / 8,
			7 * cxClient / 8, 7 * cyClient / 8);

		// Բ�Ǿ��Σ�����������Ϊ����ʴ��
		RoundRect(hdc, cxClient / 4, cyClient / 4,
			3 * cxClient / 4, 3 * cyClient / 4,
			cxClient / 4, cyClient / 4);

		Arc(hdc, cxClient / 16, cyClient / 16,
			15 * cxClient / 16, 15 * cyClient / 16,
			cxClient / 2, 0, 0, cyClient / 2);

		Chord(hdc, cxClient / 16, cyClient / 16,
			15 * cxClient / 16, 15 * cyClient / 16,
			cxClient, cyClient / 2, cxClient / 2, 0);

		Pie(hdc, cxClient / 16, cyClient / 16,
			15 * cxClient / 16, 15 * cyClient / 16,
			cxClient / 2, cyClient, cxClient, cyClient / 2);

		EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����
}