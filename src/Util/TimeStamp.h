#pragma once
#include <chrono>
#include <string>

namespace CUtil{
	class TimeStamp{
	public:
		TimeStamp();

		~TimeStamp();

		TimeStamp(const TimeStamp& rhs);

		static TimeStamp Now();

		TimeStamp operator=(const TimeStamp& rhs);
		
		std::string toStringOnlySecond();

		std::string toStringMicrioSecond();

		const std::chrono::time_point<std::chrono::system_clock>& getTime() const{
			return tPoint_;
		}

		void addSecond(int32_t seconds);

		void addMinutes(int32_t minus);
		
		void addHours(int32_t hours);


	private:
		std::chrono::time_point<std::chrono::system_clock> tPoint_;
	};

	inline bool operator <(const  TimeStamp & l,const TimeStamp & r){
		return l.getTime() < r.getTime();
	}

}