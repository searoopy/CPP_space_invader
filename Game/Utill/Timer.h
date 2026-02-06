#pragma once


class Timer
{

public:
	Timer(float targetTime = 1.0f);
	void Tick(float deltaTime);


	//경과 시간 리셋.
	void Reset();

	//설정한 시간 만큼 흘렀는지 확인.
	bool IsTimeOut() const;

	void SetTargetTime(float newtargetTime);

private:
	//경과 시간 확인용 변수.
	float elapsedTime = 0.0f;

	//타이머 목표 시간.
	float targetTime = 0.0f;
};

