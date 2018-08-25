#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	// check 9-1 : 시간을 얻기 위한 베이스 작업
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);		// 초당 프리퀀시 갯수. PC 가 내부에서 시간을 계산하는 방식
	_secondsPerCount = 1.0f / (double)countsPerSec;		// 한 프리퀀시당 걸리는 시간
}

GameTimer::~GameTimer()
{

}

// check 7-2
void GameTimer::Init()
{
	// check 9-2 : 시간을 얻기 위한 베이스 작업
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);	// 64비트 정수를 이용해서 시간 값을 돌려준다. 시간을 개수 단위로 측정. 현재 시간을 얻는다.

	// check 11-2
	_prevTime = currentTime;
	_deltaTime = 0.0;
}

void GameTimer::Update()
{
	// check 9-3 : 시간을 얻기 위한 베이스 작업
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);	// 64비트 정수를 이용해서 시간 값을 돌려준다. 시간을 개수 단위로 측정. 현재 시간을 얻는다.

	// check 10 - 델타타임을 구한다.
	_deltaTime = (currentTime - _prevTime) * _secondsPerCount;
	_prevTime = currentTime;

}

float GameTimer::GetDeltaTime()
{
	// check 8-1
	return _deltaTime;
}