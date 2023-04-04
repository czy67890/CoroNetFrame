#include <iostream>
#include <chrono>
#include "src/Util/TimeStamp.h"
#include <string>
using namespace std;
using namespace CUtil;
int main(){
	TimeStamp stp = TimeStamp::Now();
	stp.addHours(1);
	std::string res = stp.toString();
	cout << res.size();
	return 0;
}