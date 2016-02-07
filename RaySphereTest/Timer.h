#pragma once
#include<iostream>
#include<chrono>

using systemClock = std::chrono::system_clock;
using timePoint = systemClock::time_point;
using milliseconds = std::chrono::milliseconds;

class Timer
{
public:
	void Start();

	milliseconds Stop() const;
	
	timePoint m_start;
};