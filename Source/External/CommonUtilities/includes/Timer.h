#pragma once
#include <chrono>
namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;

		void Update();

		float GetDeltaTime() const;
		double GetTotalTime() const;
	private:
		double myCurrentTime;
		double myDeltaTime;
		std::chrono::high_resolution_clock::time_point timePrevius;
	};


}