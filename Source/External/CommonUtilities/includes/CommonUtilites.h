#pragma once
#include <cassert>
namespace CommonUtilities
{
	template<typename T>

	T Max(const T aFirst, const T aSecond)
	{
		if (aFirst >= aSecond)
		{
			return aFirst;
		}
		else if (aFirst < aSecond)
		{
			return aSecond;
		}
	}

	template<typename T>
	T Min(const T aFirst, const T aSecond)
	{
		if (aFirst >= aSecond)
		{
			return aSecond;
		}
		else if (aFirst < aSecond)
		{
			return aFirst;
		}
	}

	template<typename T>
	T Abs(const T aValue)
	{
		if (aValue < 0)
		{
			return -aValue;
		}
		return aValue;
	}

	template<typename T>
	T Clamp(const T aValue, const T aMin, const T aMax)
	{
		assert(aMin <= aMax && "Min is greater then Max");
		if (aValue < aMin)
		{
			return aMin;
		}
		else if (aValue > aMax)
		{
			return aMax;
		}
		else if (aValue >= aMin && aValue <= aMax)
		{
			return aValue;
		}
	}

	template<typename T>
	T Lerp(const T aFirst, const T aSecond, const float aFloat)
	{
		return aFirst + (aFloat * (aSecond - aFirst));
	}

	template<typename T>
	void Swap(T& aFirst, T& aSecond)
	{
		T temp = aFirst;
		aFirst = aSecond;
		aSecond = temp;
	}
}