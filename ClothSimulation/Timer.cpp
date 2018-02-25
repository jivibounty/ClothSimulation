
#include "Timer.h"
#include <stdlib.h>

namespace Cloth
{

	Timer::Timer()
		: m_bTimerStopped(false)
		, m_StartTimeInMicroSec(0.0)
		, m_StopTimeInMicroSec(0.0)
	{
#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceFrequency(&m_Frequency);
		m_StartCount.QuadPart = 0;
		m_StopCount.QuadPart = 0;
		m_PauseStartDiffCount.QuadPart = 0;
#else
		m_StartCount.tv_sec = m_StartCount.tv_usec = 0;
		m_StopCount.tv_sec = m_StopCount.tv_usec = 0;
		m_PauseStartDiffCount.tv_sec = m_StopCount.tv_usec = 0;
#endif
	}

	Timer::~Timer()
	{
	}

	double Timer::getTimeInMicroSeconds() const
	{
#if defined(WIN32) || defined(_WIN32)
		LARGE_INTEGER count;
		QueryPerformanceCounter(&count);
		return count.QuadPart * (1000000.0 / m_Frequency.QuadPart);
#else
		timeval count;
		gettimeofday(&count, NULL);
		return (count.tv_sec * 1000000.0) + count.tv_usec;
#endif
	}

	double Timer::getTimeInMilliSeconds() const
	{
		return this->getTimeInMicroSeconds() * 0.001;
	}

	double Timer::getTimeInSeconds() const
	{
		return this->getTimeInMicroSeconds() * 0.000001;
	}

	void Timer::startTimer()
	{
		m_bTimerStopped = false;
#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&m_StartCount);
#else
		gettimeofday(&m_StartCount, NULL);
#endif
	}

	void Timer::pauseTimer()
	{
#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&m_PauseStartDiffCount);
		m_PauseStartDiffCount.QuadPart = m_PauseStartDiffCount.QuadPart - m_StartCount.QuadPart;
#else
		gettimeofday(&m_PauseStartDiffCount, NULL);
		m_PauseStartDiffCount.tv_sec = m_PauseStartDiffCount.tv_sec - m_StartCount.tv_sec;
#endif
	}

	void Timer::continueTimer()
	{
#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&m_StartCount);
		m_StartCount.QuadPart -= m_PauseStartDiffCount.QuadPart;
#else
		gettimeofday(&m_StartCount, NULL);
		m_StartCount.tv_sec -= m_PauseStartDiffCount.tv_sec;
#endif
	}

	void Timer::stopTimer()
	{

#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&m_StopCount);
		if(m_bTimerStopped)
		{
			m_StartCount = m_StopCount;
		}
#else
		gettimeofday(&m_StopCount, NULL);
		if(m_bTimerStopped)
		{
			m_StartCount = m_StopCount;
		}
#endif
		m_bTimerStopped = true;
	}

	double Timer::getElapsedTimeInMicroSeconds()
	{
#if defined(WIN32) || defined(_WIN32)
		if(!m_bTimerStopped)
		{
			QueryPerformanceCounter(&m_StopCount);
		}

		m_StartTimeInMicroSec = m_StartCount.QuadPart * (1000000.0 / m_Frequency.QuadPart);
		m_StopTimeInMicroSec = m_StopCount.QuadPart * (1000000.0 / m_Frequency.QuadPart);
#else
		if(!m_bTimerStopped)
		{
			gettimeofday(&m_StopCount, NULL);
		}
		m_StartTimeInMicroSec = (m_StartCount.tv_sec * 1000000.0) + m_StartCount.tv_usec;
		m_StopTimeInMicroSec = (m_StopCount.tv_sec * 1000000.0) + m_StopCount.tv_usec;
#endif

		return m_StopTimeInMicroSec - m_StartTimeInMicroSec;
	}

	double Timer::getElapsedTimeInMilliSeconds()
	{
		return this->getElapsedTimeInMicroSeconds() * 0.001;
	}

	double Timer::getElapsedTimeInSeconds()
	{
		return this->getElapsedTimeInMicroSeconds() * 0.000001;
	}

}

