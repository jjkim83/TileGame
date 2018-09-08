#include <Windows.h>

// check 5
#include "GameTimer.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);
		return 0;
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
		{
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);		// 기본 처리 프로시저
}


// HINSTANCE hInstance : 현재 응용프로그램의 인스턴스 핸들. 응용프로그램을 위한 식별 수단으로 쓰인다.
//	핸들 : 운영체제가부여하는 아이디. 무언가를 식별하거나 가리키기 위해 쓰인다. 특히 객체를 참조하기 위해 쓰인다.
//		윈도우는 핸들을 이용해서, 자원을 관리한다. (응용프로그램 포함)
// HINSTANCE hPrevInstance : 쓰이지 않음.
// PSTR pCmdLine : 프로그램을 실행하는 데 쓰인 명령줄 인수 문자열
// int nCmdShow : 응용프로그램 표시 방식. 크게 보일 것인가, 작게 보일 것인가?
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;	// 창의 스타일 지정. 수평/수직 크기가 변하면 창을 다시 갱신
	wc.lpfnWndProc = WndProc;	// 프로시저 함수. 윈도우 운영체제가 보내는 이벤트를 처리하기 위한 함수
	wc.cbClsExtra = 0;	// 사용 안함
	wc.cbWndExtra = 0;	// 사용 안함
	wc.hInstance = hInstance;	// 응용 프로그램 인스턴스 핸들 연결
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);	// 아이콘을 생성하고, 아이콘 핸들을 세팅해 둔다.
	wc.hCursor = LoadCursor(0, IDC_ARROW);		// 커서를 생성하고, 커서 핸들을 세팅해 둔다.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 클라이언트 영역의 배경 색을 세팅한다.
	wc.lpszMenuName = 0;	// 창의 메뉴. 현재 없다.
	wc.lpszClassName = L"2DTileFrameWnd";		// 윈도우 스타일의 이름. 이 이름을 이용해서, 다른 창에서 가져다 사용할 수 있다.
	if (!RegisterClass(&wc))
	{
		return 0;
	}

	HWND hWnd = CreateWindow(
		L"2DTileFrameWnd",		// 사용할 윈도우 스타일. 등록된 윈도우 스타일 들 중에서 이름을 통해 가지고 온다. 직접 등록할 수도 있다.
		L"2D Tile Frame",		// 창의 제목
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일. 캡션이 있을 것인지, 메뉴가 있을 것인지 등등
		CW_USEDEFAULT, CW_USEDEFAULT,	// x, y 좌표
		1024, 768,	// 너비, 높이
		0,		// 부모 창의 핸들을 세팅한다. 현재 최상위 창이므로 0을 세팅한다.
		0,		// 메뉴 핸들. 사용하지 않음
		hInstance,	// 윈도우 운영체제가 부여한 인스턴스 핸들을 세팅한다. 현재 창과 연결. 운영체제가 관리할 수 있다.
		0	// 추가적인 생성 플래그. 사용 안함.
	);
	if (NULL == hWnd)
	{
		return 0;
	}


	// hWnd : 하나의 윈도우를 관리하기 위한 핸들(OS는 이 핸들로 해당 윈도우를 기억한다.)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// check 3 : fps 결정 (60)
	float frameInterval = 1.0f / 60.0f;
	float frameTime = 0.0f;

	// check 4
	GameTimer gameTimer;
	gameTimer.Init();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// PeekMessage : 메시지가 없으면, 윈도우가 아닌 응용 프로그램에 제어권을 반환한다.
		//	PM_REMOVE : 메시지큐에서 사용한 메시지 제거
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		// 키보드 변환 수행. 키 코드를 문자 메시지로 변환
			DispatchMessage(&msg);		// 메시지를 창으로 배분
		}
		else
		{
			// check 2
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();		// 지난 프레임부터 지금까지 흐른 시간의 차이

			// check 1 : 프레임에 맞게 업데이트
			frameTime += deltaTime;	// 시간이 흐른다.
			if (frameInterval <= frameTime)
			{
				frameTime = 0.0f;

				// todo : game update
				OutputDebugString(L"Update\n");
			}
		}
	}

	return 0;
}

