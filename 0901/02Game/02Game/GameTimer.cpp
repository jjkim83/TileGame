
#include <Windows.h>
#include <d3d9.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	__int64 countsPerSec;
	// �ʴ� cpu ������
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec); //���ɿ� �ٰ��� �ð� 

	_secondsPerCount = 1.0f / (double)countsPerSec;
}

GameTimer::~GameTimer()
{

}

void GameTimer::Init() 
{
	__int64 currentTime;
	// ��������� cpu ������
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

