#include <WIndows.h>
#include "GameTimer.h"
#include <d3dx9.h>
#include "Sprite.h"

// ������ ���ν����Լ�: ������� ���� ���� �̺�Ʈ�� ó���ϴ� �Լ�(����ó���Ѵ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);	// hWnd�� 0�� ���� ������. ������os�� ���� ������ �ñ�ڴ�.
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
	bool isWindow = true;	//false�� Ǯ��ũ�� ����

	if (isWindow)
	{
		width = 1024;
		height = 768;
	}
	else
	{
		width = 1920;
		height = 1080;
	}

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
	wc.lpszClassName = L"2DTileFrameWnd";				// �� ������ ��Ÿ���� �̸� 

	// ���� �����콺Ÿ�� ���
	if (FALSE == RegisterClass(&wc))
	{
		return 0;
	}

	//Ǯ��ũ�� ����϶���, �����쿡 �ΰ����� ��Ҹ� �����Ѵ�.
	DWORD style;
	if (isWindow)
	{
		style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}


	//â�ڵ�(���̵�)�� ���� �߱��� ����.
	HWND hWnd = CreateWindow(
		L"2DTileFrameWnd",		// ����� ������ ��Ÿ�� �̸�. os�� ��ϵǾ�����.
		L"02Game",
		style,	// �����콺Ÿ�� �⺻�̾��ٰ� ���� �����쿴�ٰ� Ǯ��ũ���̱⶧���� ��Ÿ�Ϸ�.
		CW_USEDEFAULT, CW_USEDEFAULT,		// ������ġ : x, y 
		width, height, //�ػ�. �ʺ�/����
		0,			// �θ�â�� �ڵ�. ������.
		0,			// �޴��ڵ�. ������.
		hInstance,	// os�� ������ �����̵Ǽ�. os���� �����츦 �����Ҽ��ֵ�.
		0);

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
	
	D3DFORMAT format;
	if (isWindow)
	{
		format = D3DFMT_UNKNOWN;	// �����켳���� �ñ��.
	}
	else
	{
		format = D3DFMT_X8R8G8B8;	// ���� ���������� ����Ѵ�.
	}

	//Device�� �����ϱ�����
	//Device�� ���ؼ� ȭ�鿡 ��� ���������� ����
	//�������ϴ°�.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	// D3DFMT_UNKNOWN�� ������ ������ �������� ���ÿ� �ñ�ڴٴ°�.
	//�׷��� format���� �ٲ�.
	d3dpp.BackBufferCount = 1;	// ���� ���۸� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//����̽��� ����
	//���𰡸� ���ؼ�.
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

	//Sprite COM �������̽�����
	ID3DXSprite* spriteDX;	// 2d���ϱ�����.
	hr = D3DXCreateSprite(dxDevice, &spriteDX);
	if (FAILED(hr))
	{
		return 0;
	}

	//�̹����ε�
	//IDirect3DTexture9* textureDX;
	//RECT textureRect;
	//D3DCOLOR textureColor;

	// �ε��� ���ϸ�
	LPCWSTR fileName = L"../resource/image/george.png";
	
	//��������Ʈ�� ����
	//��������Ʈ�� ����
	Sprite* testSprite = new Sprite();
	testSprite->Init(fileName, dxDevice, spriteDX);

	/*
	
	D3DXIMAGE_INFO texInfo;
	{
	// ���Ϸκ��� �̹����� �ʺ�� ���̸� ��´�
		hr = D3DXGetImageInfoFromFile(fileName, &texInfo);
		if (FAILED(hr))
		{
			return 0;
		}
		//�̹��������� �ε�.
		hr = D3DXCreateTextureFromFileEx(dxDevice,
			fileName,
			texInfo.Width, texInfo.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			&texInfo,
			NULL,
			&textureDX);

		if (FAILED(hr))
		{
			return 0;
		}

		//����� ��������
		textureRect.left = 0;
		textureRect.right = textureRect.left + texInfo.Width;
		textureRect.top = 0;
		textureRect.bottom = textureRect.top + texInfo.Height;

		textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	*/

	float fps = 60.0f;
	float frameInverval = 1.0f / fps;
	float frameTime = 0.0f;

	GameTimer gameTimer;
	gameTimer.Init();
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (TRUE == PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);	// Ű���� ��ȯ ���� 
			DispatchMessage(&msg);	// �޼���â�� ����� ��û�Ѵ�.
		}

		{
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();

			//deltaTime
			//���������� ������Ʈ ���� 
			//���ݱ��� �帥 �ð�

			testSprite->Update(deltaTime);

			frameTime += deltaTime; 
			if (frameInverval <= frameTime)
			{
				frameTime = 0.0f;

				// �������Ӹ��� ȭ���� ���� ä���.
				dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0),0.0f, 0);
				{
					dxDevice->BeginScene();
					{
						//Scene�۾�: ����ȭ��� ���õ� ��� �۾�����
						spriteDX->Begin(D3DXSPRITE_ALPHABLEND);
						{

							//��������Ʈ ����
							testSprite->Render();


							////2D�̹�����°���. Texture(�ؽ���,2d�̹��� ����)
							//spriteDX->Draw(
							//	textureDX,		//�׸��ؽ��� ������ ����ִ� �������̽�
							//	&textureRect,	// �����̹������� �׸� �κ�	
							//	NULL,			
							//	NULL,
							//	textureColor	//��������Ʈ�� ����� ����ä��
							//);	
							//
						}
						spriteDX->End();

					}
					//deviceLostó��

					//Device����Ȯ��(�ž�����Ʈ����)
					hr = dxDevice->TestCooperativeLevel();
					if (FAILED(hr)) //Device���¿� ������ ������,
					{
						//	�������� ������ ���� �ٸ��� ó��(�������������,��������������ĥ���ִ»���,�ٿϷ�Ȼ���/�����λ���)
						if (D3DERR_DEVICELOST == hr)
						{
							//����츮�� �ƹ��͵��Ҽ� ���»���
							Sleep(100); // 100�̶� �ð���ŭ �޽��� ���� ����.cpu������.//���̵���·� ���ư�.
						}
						else if (D3DERR_DEVICENOTRESET == hr)
						{
							
							//��������������, ������ �����ѻ���
							//���ݺ��� ������ �����Ͻÿ�.

							//Device�� �׿� Device������ ������ 
							//��縮�ҽ��� �����ؾ������
							//1. ������ ��������͵��� ��� ����
							testSprite->Release();

							/*
							if (textureDX)
							{
								textureDX->Release();
								textureDX = NULL;
							}*/

							//2. ���λ���(����)
							direct3d = Direct3DCreate9(D3D_SDK_VERSION);	//���̷�Ʈx�� �ٽ� ����
							if (NULL != direct3d)
							{
								//����̽��� �ٽ� �������ְ�,
								HRESULT hr = direct3d->CreateDevice(
									D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp,
									&dxDevice);
								if (SUCCEEDED(hr))
								{
									//��������Ʈ �������̽� ��������
									hr = D3DXCreateSprite(dxDevice, &spriteDX);
									if (SUCCEEDED(hr))
									{
										testSprite->Reset();

									}
								}
								
							}
						}
				
					}

					dxDevice->EndScene();
				}

				// ä�� ���� ����͸� ���� �����ش�.
				dxDevice->Present(NULL, NULL, NULL, NULL);
			
				OutputDebugString(L"Update\n");
			}
		}

	}

	//�ؽ��� ������ ��������Ʈ�� �ı��ɶ�
	if (NULL != testSprite)
	{
		delete testSprite;
	}



	//�׻�����ް��ؾ��ϱ⶧�������ﶧ��.
	if (dxDevice)
	{
		dxDevice->Release();
		dxDevice = NULL;
	}
	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}

	return 0;
}
