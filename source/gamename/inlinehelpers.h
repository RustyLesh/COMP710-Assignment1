#ifndef __INLINEHELPERS_H__
#define __INLINEHELPERS_H__
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>

inline int GetRandom(int lowerBoundary, int upperBoundary)
{
	int range = (upperBoundary - lowerBoundary + 1);
	return (rand() % range) + lowerBoundary;
}

inline float GetRandomPercentage()
{
	int percent = GetRandom(0, 100);
	return percent / 100.0f;
}

inline float GetPositiveOrNegative()
{
	int coinToss = rand() % 2;
	float result = (coinToss == 0) ? -1.0f : 1.0f;
	return result;
}

inline float Lerp(float s, float e, float t)
{
	return (((1.0f - t) * s) + (t * e));
}

inline float EaseInOutQuad(float time, float start, float change, float duration)
{
	time /= (duration / 2);
	if (time < 1.0f)
	{
		return ((change / 2.0f) * (time * time)) + start;
	}
	return -change / 2.0f * (((time - 2.0f) * (--time)) - 1.0f) + start;
}

inline float RadToDeg(float rad)
{
	return (rad * (180/M_PI));
}

inline float DegToRad(float degrees)
{
	return(degrees *(M_PI / 180));
}

inline float Clamp(float minimum, float value, float maximum)
{
	if (value > maximum)
	{
		value = maximum;
	}
	else if (value < minimum)
	{
		value = minimum;
	}

	return value;
}
#endif // __INLINEHELPERS_H__