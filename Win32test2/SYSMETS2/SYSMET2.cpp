/*--------------------------------------------------------------
SYSMETS2.cpp -- System Metrics DIsplay Program No.2
				(c) Ф������ 2015
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
		TEXT("Get System Metrics No.2"),	// ���ڱ���
		WS_OVERLAPPEDWINDOW | WS_VSCROLL, 		// ���ڷ�� WS_VSCROLL�Ǵ�ֱ��������WS_HSCROLL��ˮƽ������
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
	static int cxChar, cyChar, cxCaps,  cyClient, iVscrollPos;
	int i, y;
	TCHAR szBuffer[10];

	switch (message)
	{
	case WM_CREATE:
		//��ȡϵͳ����Ŀ�Ⱥ͸߶�
		hdc = GetDC(hwnd);												// ���ڿͻ����豸���������ͨ�����ڴ��������Ϣ�������Ϣ��ʹ�øú�����ReleaseDC()���ʹ�ã�����������յ��û��ļ��̻��������ʱ��ʱ�ػ��ƿͻ�����������Ϊ������WM_PAINT��Ϣȥ����ʹ�ͻ�����һ������Ч��

		GetTextMetrics(hdc, &tm);										// ���ڻ�ȡ����ߴ�
		cxChar = tm.tmAveCharWidth;										// ϵͳ�ַ���ƽ�����
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;		// ��д�ַ�ƽ�����
		cyChar = tm.tmHeight + tm.tmExternalLeading;					// ϵͳ�ַ����ܸ߶�
		ReleaseDC(hwnd, hdc);

		// ���ù������ķ�Χ�� SetScrollRange(hwnd, iBar, iMin, iMax, bRedraw)
		// iBar:[SB_VERT, SB_HORZ]��bRedrawΪ�������Զ��ػ棬�粻��������������޸Ĺ���������ʾ��Ӧ��ΪTRUE
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1, FALSE);

		// ���ù�������λ�ã�SetScrollPos(hwnd, iBar, iPos, bRedraw)
		// iPos�ǹ���������λ�ã�
		SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ

		for (i = 0; i < NUMLINES; i++)
		{
			y = cyChar * (i - iVscrollPos);

			TextOut(hdc, 0, y,				// yָ����ÿ���ַ��Ķ�������ڿͻ����Ķ�����λ��
				sysmetrics[i].szLabel,
				lstrlen(sysmetrics[i].szLabel));

			TextOut(hdc, 22 * cxCaps, y,
				sysmetrics[i].szDesc,
				lstrlen(sysmetrics[i].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);	// ���TextOut�������õ�����ӿͻ��������Ͻǿ�ʼ��

			TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer,
				wsprintf(szBuffer, TEXT("%5d"),
					GetSystemMetrics(sysmetrics[i].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);	//	ʹ���ĵ�����ָ�����
		}
		EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
		return 0;

	case WM_SIZE:
		// ��ȡ�ͻ����ĸ߶ȣ�lParam�ĵ�λ���ǿͻ����Ŀ�ȣ���λ���ǿͻ����ĸ߶�
		cyClient = HIWORD(lParam);
		return 0;

	//case WM_HSCROLL:
	case WM_VSCROLL:
		// ������������֪ͨp85
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:		// ҳ�������ƣ�����������
			iVscrollPos -= 1;
			break;

		case SB_LINEDOWN:
			iVscrollPos += 1;
			break;

		case SB_PAGEUP:
			iVscrollPos -= cyClient / cyChar;		// cyClient / cyChar�Ǵ�ֱ�ƶ�������
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

		// GetScrollPos()��ȡ��������ǰλ�ã�GetScrollRange��õ�ǰ��Χ 
		if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))
		{
			// ���ù�������λ�ã�SetScrollPos(hwnd, iBar, iPos, bRedraw)
			SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);

			// InvalidateRectʹ����������Ч����������WM_PAINT��Ϣ������WM_PAINT���ȼ��ϵͣ����������
			// �����ȼ���Ϣ�������´���ˢ���ӳ١���ʹ��UpdateWindow(hwnd)����
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����
}