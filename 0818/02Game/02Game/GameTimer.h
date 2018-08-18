

#pragma once



class GameTimer
{
private:
	float _secondsPerCount;

	float _deltaTime;
	float _prevTime;

public:
	GameTimer();
	~GameTimer();

	void Init();
	void Update();
	float GetDeltaTime();

};


