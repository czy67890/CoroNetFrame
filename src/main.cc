#include <iostream>
#include <chrono>
#include "src/Util/TimeStamp.h"
#include <string>
#include "src/Util/Mutex.h"
#include "src/Util/FileUnit.h"
#include <sys/time.h>
#include "src/Util/TimeCounter.h"
int times = 200000000;

using namespace CUtil;
int main(){
	LogFile file("testproc");
	for(int i = 0;i < 30;++i){
		file.append("i be out",9);
	}
	return 0;
}