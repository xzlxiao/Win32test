/*--------------------------------------------------------------------
	SYSMETS3.cpp -- System Metrics DIsplay Program No.3
				(c) Ф������ 2015
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
		TEXT("Get System Metrics No.3"),	// ���ڱ���
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
	static int cxChar, cyChar, cxCaps, cyClient,cxClient, iMaxWidth;
	int i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;
	TCHAR szBuffer[10];
	SCROLLINFO si; 
	/*
	SCROLLINFO
	{
		UINT cbSize;	// ��Ϊsizeof (SCROLLINFO)
		UINT fMask;		// Ҫ���û��ȡ��ֵ
		int nMin;		// ��Χ����Сֵ
		int nMax;		// ��Χ�����ֵ
		UINT nPage;		// ҳ���С
		int nPos;		// ��ǰλ��
		int nTrackPos;	// ��ǰ׷��λ��
	*/

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

		// Save the width of the three column
		iMaxWidth = 40 * cxChar + 22 * cxCaps;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ

		// ��ȡ��ֱ������λ��

		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd, SB_VERT, &si);
		iVertPos = si.nPos;

		// ��ȡˮƽ��������Ϣ

		GetScrollInfo(hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		// �ҵ���ͼ����

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

		EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
		return 0;

	case WM_SIZE:
		// ��ȡ�ͻ����Ŀ�Ⱥ͸߶ȣ�lParam�ĵ�λ���ǿͻ����Ŀ�ȣ���λ���ǿͻ����ĸ߶�
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		// ���ô�ֱ�������ķ�Χ��ҳ���С
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;

		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		// ����ˮƽ�������ķ�Χ��ҳ���С
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 2 + iMaxWidth / cxChar;
		si.nPage = cxClient / cxChar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		return 0;

		//case WM_HSCROLL:
	case WM_VSCROLL:
		// �õ����д�ֱ����������Ϣ
		si.cbSize = sizeof(si);		// �ڵ���SetScrollInfo��GetScrollInfo��������֮ǰ����������cbSize�ֶ�Ϊ�ýṹ�Ĵ�С
		si.fMask = SIF_ALL;			// SIF_ALL��־��SIF_RANGE��SIF_POS��SIF_PAGE��SIF_TRACKPOS��ϡ�
		GetScrollInfo(hwnd, SB_VERT, &si);

		// ����λ�ã�֮��Ƚ�
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

		// ���λ�øı䣬�������ڲ�ˢ��

		if (si.nPos != iVertPos)
		{
			// ScroWindow�ĵڶ�������ָ���˿ͻ���ˮƽ���������أ�����������ָ���˿ͻ�����ֱ���������ء�
			ScrollWindow(hwnd, 0, cyChar*(iVertPos - si.nPos), NULL, NULL);
			UpdateWindow(hwnd);
		}

		return 0;

	case WM_HSCROLL:
		// ��ȡ���д�ֱ����������Ϣ
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
		PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����
}