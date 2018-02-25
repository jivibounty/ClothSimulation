
#ifndef Timer_h
#define Timer_h

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace Cloth
{

	class Timer
	{
	public:
		//default constructor
		Timer();

		//destructor
		~Timer();

		double getTimeInMicroSeconds() const;
		double getTimeInMilliSeconds() const;
		double getTimeInSeconds() const;
		void startTimer();
		void pauseTimer();
		void continueTimer();
		void stopTimer();
		double getElapsedTimeInMicroSeconds();
		double getElapsedTimeInMilliSeconds();
		double getElapsedTimeInSeconds();

	private:
		double m_StartTimeInMicroSec;
		double m_StopTimeInMicroSec;
		bool m_bTimerStopped;
#if defined(WIN32) || defined(_WIN32)
		LARGE_INTEGER m_Frequency;
		LARGE_INTEGER m_StartCount;
		LARGE_INTEGER m_StopCount;
		LARGE_INTEGER m_PauseStartDiffCount;
#else
		timeval m_StartCount;
		timeval m_StopCount;
#endif
	};

}

#endif //Timer_h

