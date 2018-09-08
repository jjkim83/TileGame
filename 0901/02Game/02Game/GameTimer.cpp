
#include <Windows.h>
#include <d3d9.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	__int64 countsPerSec;
	// 초당 cpu 진동수
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec); //성능에 근거한 시간 

	_secondsPerCount = 1.0f / (double)countsPerSec;
}

GameTimer::~GameTimer()
{

}

void GameTimer::Init() 
{
	__int64 currentTime;
	// 현재까지의 cpu 진동수
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	_deltaTime = 0.0f;
	_prevTime = currentTime;
}

void GameTimer::Update()
{
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);


	_deltaTime = (currentTime - _prevTime)*_secondsPerCount;
	_prevTime = currentTime;
}

float GameTimer::GetDeltaTime()
{
	return _deltaTime;
}

