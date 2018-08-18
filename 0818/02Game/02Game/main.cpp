#include <WIndows.h>
#include "GameTimer.h"
#include <d3d9.h>
// ������ ���ν����Լ�: ������� ���� ���� �̺�Ʈ�� ó���ϴ� �Լ�(����ó���Ѵ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, "Hello World", "Hello", MB_OK);	// hWnd�� 0�� ���� ������. ������os�� ���� ������ �ñ�ڴ�.
		return 0;
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
		{
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,	// ���� �������α׷��� �����ڵ�
	HINSTANCE hPrevInstance,				// �Ⱦ��� 
	PSTR pCmdLine,			// �����ϴµ� ���̴� ����� �Ǵ� �μ� // ���� ���ڸ� ���� �̸�ɾ ���� ����� ����.
	int nCmdShow			// �������α׷��� ǥ�ù��. �ּ�ȭ/�ִ�ȭ �ؼ� �����ٰų�?
)

{
	int width = 1024;
	int height = 768;
	bool isWindow = true;	//false �� �ٲ��� Ǯ��ũ�� ����

	//�����콺Ÿ���� ����� ���
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc; // ������ ���ν��� �Լ����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "2DTileFrameWnd";				// �� ������ ��Ÿ���� �̸� 

	// ���� �����콺Ÿ�� ���
	if (FALSE == RegisterClass(&wc))
	{
		return 0;
	}

	//â�ڵ�(���̵�)�� ���� �߱��� ����.
	HWND hWnd = CreateWindow(
		"2DTileFrameWnd",		// ����� ������ ��Ÿ�� �̸�. os�� ��ϵǾ�����.
		"02Game",
		WS_OVERLAPPEDWINDOW,		// �����콺Ÿ��
		CW_USEDEFAULT, CW_USEDEFAULT,		// ������ġ : x, y 
		width, height, //�ػ�. �ʺ�/����
		0,			// �θ�â�� �ڵ�. ������.
		0,			// �޴��ڵ�. ������.
		hInstance,	// os�� ������ �����̵Ǽ�. os���� �����츦 �����Ҽ��ֵ�.
		0
	);

	if (NULL == hWnd)
	{
		return 0;
	}
		
	// hWmd : �ϳ��� �����츦 ����Ű�� �ڵ�(���̵�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���� ���� ���� Ȯ��
	if (true == isWindow)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd, 0, 0,
			width + (width - clientRect.right),
			height + (height - clientRect.bottom),
			TRUE);
	}

	// directX 

	// �������� (DirectX)���� �ϵ��� ���� �����Ҽ� �ִ�
	//�հ�(Device)�� �����ؼ� �޶�� ��û 

	LPDIRECT3D9 direct3d; // �׷����� ����ϴ� directX
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d)
	{
		return 0;
	}



	//Device�� �����ϱ�����
	//Device�� ���ؼ� ȭ�鿡 ��� ���������� ����
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;	// ���� ���۸� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//����̽��� ����
	LPDIRECT3DDEVICE9 dxDevice;
	HRESULT hr = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&dxDevice);

	if (FAILED(hr))
	{
		return 0;
	}

	float fps = 60.0f;
	float frameInverval = 1.0f / fps;
	float frameTime = 0.0f;

	GameTimer gameTimer;
	gameTimer.Init();

	// �� �����찡 ������ �ʰ� �����ǵ��� ó��.
	/*
	MSG msg;
	while (-1 != GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);	// Ű���� ��ȯ ���� 
		DispatchMessage(&msg);	// �޼���â�� ����� ��û�Ѵ�.
	}
	*/


	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (TRUE == PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);	// Ű���� ��ȯ ���� 
			DispatchMessage(&msg);	// �޼���â�� ����� ��û�Ѵ�.
		}

		else
		{
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();

			//deltaTime
			//���������� ������Ʈ ���� 
			//���ݱ��� �帥 �ð�

			frameTime += deltaTime; 
			if (frameInverval <= frameTime)
			{
				frameTime = 0.0f;

				// �������Ӹ��� ȭ���� ���� ä���.
				dxDevice->Clear(0, NULL,
					D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0),
					0.0f, 0);
				
				// ä�� ���� ����͸� ���� �����ش�.
				dxDevice->Present(NULL, NULL, NULL, NULL);
				

				OutputDebugString("Update\n");
			}
		}

	}

	return 0;
}
