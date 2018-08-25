#include <WIndows.h>
#include "GameTimer.h"
#include <d3dx9.h>

// 윈도우 프로시저함수: 윈도우로 부터 받은 이벤트를 처리하는 함수(내가처리한다)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);	// hWnd에 0을 넣은 이유는. 윈도우os에 직접 관리를 맡기겠다.
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
	HINSTANCE hInstance,	// 메인 응용프로그램의 메인핸들
	HINSTANCE hPrevInstance,				// 안쓰임 
	PSTR pCmdLine,			// 실행하는데 쓰이는 명령줄 또는 인수 // 끝에 인자를 쓸때 이명령어를 통해 결과가 들어옴.
	int nCmdShow			// 응용프로그래밍 표시방식. 최소화/최대화 해서 보여줄거냐?
)

{
	int width = 1024;
	int height = 768;
	bool isWindow = true;	//false는 풀스크린 모드로

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

	//윈도우스타일을 만들고 등록
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc; // 윈도우 프로시저 함수등록
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"2DTileFrameWnd";				// 이 윈도우 스타일의 이름 

	// 만든 윈도우스타일 등록
	if (FALSE == RegisterClass(&wc))
	{
		return 0;
	}

	//풀스크린 모드일때는, 윈도우에 부가적인 요소를 제거한다.
	DWORD style;
	if (isWindow)
	{
		style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}


	//창핸들(아이디)를 먼저 발급을 받자.
	HWND hWnd = CreateWindow(
		L"2DTileFrameWnd",		// 사용할 윈도우 스타일 이름. os에 등록되어있음.
		L"02Game",
		style,	// 윈도우스타일 기본이었다가 이제 윈도우였다가 풀스크린이기때문에 스타일로.
		CW_USEDEFAULT, CW_USEDEFAULT,		// 시작위치 : x, y 
		width, height, //해상도. 너비/높이
		0,			// 부모창의 핸들. 사용안함.
		0,			// 메뉴핸들. 사용안함.
		hInstance,	// os와 윈도우 연결이되서. os에서 윈도우를 관리할수있따.
		0);

	if (NULL == hWnd)
	{
		return 0;
	}
		
	// hWmd : 하나의 윈도우를 가리키는 핸들(아이디)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//실제 게임 영역 확보
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

	// 누군가가 (DirectX)한테 하드웨어에 직접 접근할수 있는
	//먼가(Device)를 생성해서 달라고 요청 

	LPDIRECT3D9 direct3d; // 그래픽을 담당하는 directX
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d)
	{
		return 0;
	}
	
	D3DFORMAT format;
	if (isWindow)
	{
		format = D3DFMT_UNKNOWN;	// 윈도우설정에 맡긴다.
	}
	else
	{
		format = D3DFMT_X8R8G8B8;	// 전용 색상포맷을 사용한다.
	}

	//Device를 생성하기전에
	//Device를 통해서 화면에 어떻게 보여질지를 결정
	//값세팅하는거.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	// D3DFMT_UNKNOWN는 게임의 세팅이 윈도우의 세팅에 맡기겠다는것.
	//그래서 format으로 바꿈.
	d3dpp.BackBufferCount = 1;	// 더블 버퍼링 개수
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//디바이스를 생성
	//무언가를 통해서.
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

	//Sprite COM 인터페이스생성
	ID3DXSprite* spriteDX;
	hr = D3DXCreateSprite(dxDevice, &spriteDX);
	if (FAILED(hr))
	{
		return 0;
	}

	//이미지로드
	IDirect3DTexture9* textureDX;
	RECT textureRect;
	D3DCOLOR textureColor;
	{
		// 로드할 파일명
		LPCWSTR fileName = L"../resource/image/george.png";

		// 파일로부터 이미지의 너비와 높이를 얻는다
		D3DXIMAGE_INFO texInfo;
		hr = D3DXGetImageInfoFromFile(fileName, &texInfo);
		if (FAILED(hr))
		{
			return 0;
		}

		//이미지데이터 로드.
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

		//출력할 영역지정
		textureRect.left = 0;
		textureRect.right = textureRect.left + texInfo.Width;
		textureRect.top = 0;
		textureRect.bottom = textureRect.top + texInfo.Height;

		textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	}

	float fps = 60.0f;
	float frameInverval = 1.0f / fps;
	float frameTime = 0.0f;

	GameTimer gameTimer;
	gameTimer.Init();

	// 이 윈도우가 꺼지지 않고 유지되도록 처리.
	/*
	MSG msg;
	while (-1 != GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);	// 키보드 변환 수행 
		DispatchMessage(&msg);	// 메세지창에 배분을 요청한다.
	}
	*/

	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (TRUE == PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);	// 키보드 변환 수행 
			DispatchMessage(&msg);	// 메세지창에 배분을 요청한다.
		}

		{
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();

			//deltaTime
			//이전윈도우 업데이트 부터 
			//지금까지 흐른 시간

			frameTime += deltaTime; 
			if (frameInverval <= frameTime)
			{
				frameTime = 0.0f;

				// 매프레임마다 화면의 색을 채운다.
				dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0),0.0f, 0);
				{
					dxDevice->BeginScene();
					{
						//Scene작업: 게임화면과 관련된 모든 작업공간
						spriteDX->Begin(D3DXSPRITE_ALPHABLEND);
						{
							//2D이미지출력공간. Texture(텍스쳐,2d이미지 한장)
							spriteDX->Draw(
								textureDX,		//그릴텍스쳐 정보가 들어있는 인터페이스
								&textureRect,	// 원본이미지에서 그릴 부분	
								NULL,			
								NULL,
								textureColor	//스프라이트의 색상과 알파채널
							);	
							
						}
						spriteDX->End();

					}
					dxDevice->EndScene();
				}

				// 채운 색을 모니터를 통해 보여준다.
				dxDevice->Present(NULL, NULL, NULL, NULL);
			
				OutputDebugString(L"Update\n");
			}
		}

	}

	//항상허락받고해야하기때문에지울때도.
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
