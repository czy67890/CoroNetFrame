#include "src/Util/TimeStamp.h"
#include <iostream>
CUtil::TimeStamp::TimeStamp()
{	
}

CUtil::TimeStamp::TimeStamp(const TimeStamp& rhs)
{
	tPoint_ = rhs.tPoint_;
}

CUtil::TimeStamp CUtil::TimeStamp::Now()
{
	TimeStamp tmp;
	tmp.tPoint_ = std::chrono::system_clock::now();
	return tmp;
}

CUtil::TimeStamp CUtil::TimeStamp::operator=(const TimeStamp& rhs)
{
	return TimeStamp();
}

std::string CUtil::TimeStamp::toStringOnlySecond()
{
	std::string res;
	auto time = std::chrono::system_clock::to_time_t(tPoint_);
	std::tm* local_time = std::localtime(&time);
	res.resize(20);
	std::strftime( &res[0],20,"%Y-%m-%d %H:%M:%S",local_time);
	return res;
}

std::string CUtil::TimeStamp::toStringMicrioSecond()
{
	return std::string();
}

void CUtil::TimeStamp::addSecond(int32_t seconds)
{
	tPoint_ += std::chrono::seconds(seconds);
}

void CUtil::TimeStamp::addMinutes(int32_t minus)
{
	tPoint_ += std::chrono::minutes(minus);
}

void CUtil::TimeStamp::addHours(int32_t hours)
{
	tPoint_ += std::chrono::hours(hours);
}

CUtil::TimeStamp::~TimeStamp()
{

}

