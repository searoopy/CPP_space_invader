#include "Timer.h"

Timer::Timer(float targetTime)
    :targetTime(targetTime)
{
}


void Timer::Reset()
{
    elapsedTime = 0.0f;
}

void Timer::Tick(float deltaTime)
{
    //경과 시간 업데이트.
    elapsedTime += deltaTime;
}

bool Timer::IsTimeOut() const
{
    return elapsedTime >= targetTime;
}

void Timer::SetTargetTime(float newtargetTime)
{
    targetTime = newtargetTime;
}
