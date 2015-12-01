/*--------------------------------------------------------------------
	HELLOWIN.cpp -- Displays "Hello, Windows 10!" in client area
						(C)	Ф������2015
--------------------------------------------------------------------*/
#include <windows.h>
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND		 hwnd;
	MSG			 msg;
	WNDCLASS	 wndclass;
		
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// LoadIcon ����ͼ�꣬�Թ�����ʹ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);				// LoadCursor ��������꣬�Թ�����ʹ��
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);		// GetStockObject ��ȡһ��ͼ�ζ����ڱ�������һ�������Դ��ڱ��������ػ��ͼˢ
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if(!RegisterClass(&wndclass))		// RegisterClass ΪӦ�ó���Ĵ���ע��һ��������
	{
		MessageBox(NULL, TEXT("This program requires Windows NT"),
					szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,		// ���������� CreateWindow ���ڴ����ഴ��һ������
						TEXT("The Hello Program"),	// ���ڱ���
						WS_OVERLAPPEDWINDOW, 		// ��������
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
	
	while(GetMessage(&msg, NULL, 0, 0))		// GetMessage ����Ϣ���л�ȡ��Ϣ
	{
		TranslateMessage(&msg);			// TranslateMessage ����һЩ������Ϣ
		DispatchMessage(&msg);			// DispatchMessage ����Ϣ���͸�
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT		rect;
	
	switch(message)
	{
		case WM_CREATE:
			 //PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME|SND_ASYNC);		// PlaySound ���������ļ�
			 return 0;
			 
		case WM_PAINT:
			 hdc = BeginPaint(hwnd, &ps);		// BeginPaint �������ڻ��ƿ�ʼ
			 
			 GetClientRect(hwnd, &rect);		// GetClienRect ��ȡ���ڿͻ����ߴ�
			 
			 DrawText(hdc, TEXT("Hello, Window 10!"), -1, &rect,		// DrawText ��ʾһ���ı��ַ���
					  DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			 EndPaint(hwnd, &ps);				// EndPaint �������ڻ���
			 return 0;
		case WM_DESTROY:
			 PostQuitMessage(0);				// PostQuitMessage �����˳�����Ϣ������Ϣ����
			 return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);	// DefWindowProc ִ��Ĭ�ϵ���Ϣ����
}