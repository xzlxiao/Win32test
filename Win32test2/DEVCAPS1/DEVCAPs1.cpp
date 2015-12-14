/*--------------------------------------------------------------
	DEVCAPS1.cpp -- Device Capabilities Display Program No.1
				(c) Ф������ 2015
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

// �ṹ�������iIndex�������GetDeviceCaps�ĵڶ�������
devcaps[] =
{
	HORZSIZE, TEXT("HORZSIZE"),TEXT("Width in millimeters:"),

	VERTSIZE, TEXT("VERTSIZE"),TEXT("Height in millimeters:"),

	HORZRES, TEXT("HORZRES"), TEXT("Width in pixels:"),

	VERTRES, TEXT("VERTRES"), TEXT("Height in raster lines:"),

	// ÿ�����ص���ɫλ��
	BITSPIXEL, TEXT("BITSPIXEL"),TEXT("Color bits per pixel:"),

	// ɫ��ƽ��
	PLANES, TEXT("PLANES"), TEXT("Number of color planes:"),

	NUMBRUSHES, TEXT("NUMBRUSHES"), TEXT("Number of device brushes:"),

	NUMPENS, TEXT("NUMPENS"), TEXT("Number of device pens:"),

	NUMMARKERS, TEXT("NUMMARKERS"), TEXT("Number of device markers:"),

	NUMFONTS, TEXT("NUMFONTS"), TEXT("Number of device fonts:"),

	NUMCOLORS, TEXT("NUMCOLORS"), TEXT("Number of device colors:"),

	PDEVICESIZE, TEXT("PDEVICESIZE"), TEXT("Size of device structure:"),

	// ÿһ���ص�Ŀ��
	ASPECTX, TEXT("ASPECTX"), TEXT("Relative width of pixel:"),

	// ÿһ���ص�ĸ߶�
	ASPECTY, TEXT("ASPECTY"), TEXT("Relative height of pixel:"),

	// ÿһ���ص�ĶԽ��߳���
	ASPECTXY, TEXT("ASPECTXY"), TEXT("Relative diagonal of pixel:"),

	// �߼����أ���ÿӢ�������������ķ�ʵ�ʷֱ���
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
		TEXT("Device Capabilities"),	// ���ڱ���
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
	HDC			hdc;
	PAINTSTRUCT	ps;
	TEXTMETRIC tm;
	static int cxChar, cyChar, cxCaps;
	int i;
	TCHAR szBuffer[10];

	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME|SND_ASYNC);		// PlaySound ���������ļ�

		//��ȡϵͳ����Ŀ�Ⱥ͸߶�
		hdc = GetDC(hwnd);												// ���ڿͻ����豸���������ͨ�����ڴ��������Ϣ�������Ϣ��ʹ�øú�����ReleaseDC()���ʹ�ã�����������յ��û��ļ��̻��������ʱ��ʱ�ػ��ƿͻ�����������Ϊ������WM_PAINT��Ϣȥ����ʹ�ͻ�����һ������Ч��
		GetTextMetrics(hdc, &tm);										// ���ڻ�ȡ����ߴ�
		cxChar = tm.tmAveCharWidth;										// ϵͳ�ַ���ƽ�����
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;		// ��д�ַ�ƽ�����
		cyChar = tm.tmHeight + tm.tmExternalLeading;					// ϵͳ�ַ����ܸ߶�
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ

		for (i = 0; i < NUMLINES; i++)
		{
			TextOut(hdc, 0, cyChar *i,				// cyChar * iָ����ÿ���ַ��Ķ�������ڿͻ����Ķ�����λ��
				devcaps[i].szLabel,
				lstrlen(devcaps[i].szLabel));

			TextOut(hdc, 14 * cxCaps, cyChar * i,
				devcaps[i].szDesc,
				lstrlen(devcaps[i].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);	// ���TextOut�������õ�����ӿͻ��������Ͻǿ�ʼ��

			TextOut(hdc, 14 * cxCaps + 35 * cxChar, cyChar*i, szBuffer,
				wsprintf(szBuffer, TEXT("%5d"),
					GetDeviceCaps(hdc, devcaps[i].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);	//	ʹ���ĵ�����ָ�����
		}

		// ͨ��GetSystemMetrics��ȡ��Ļ�ֱ��ʣ������ǵõ���ֵֻ����ʵֵ��һ��
		TextOut(hdc, 0, (NUMLINES + 1) * cyChar, L"ˮƽ�ֱ���",  wcslen(L"ˮƽ�ֱ���"));
		TextOut(hdc, 14 * cxCaps, cyChar * (NUMLINES + 1), szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(SM_CXSCREEN)));
		TextOut(hdc, 0, (NUMLINES + 2) * cyChar, L"��ֱ�ֱ���", wcslen(L"��ֱ�ֱ���"));
		TextOut(hdc, 14 * cxCaps, cyChar * (NUMLINES + 2), szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(SM_CYSCREEN)));
		EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����
}