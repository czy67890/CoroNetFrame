/*!
 * \file FileUnit.h
 *
 * \author czy
 * \date 2023.04.05
 *
 * 
 */
 #pragma once
#include <fstream>
#include <string>
#include <memory>
#include "src/Util/EnableNoCopy.h"
#include <chrono>
#include "src/Util/TimeStamp.h"
using std::string;
namespace {
	//default buffer size 64KB
	constexpr int FILE_BUF_SIZE = 64*1024;
	///maxFileNameLimit
	constexpr int FILE_NAME_LIMIT = 255;
}
namespace CUtil {
	class FileWriter :public EnAbleNoCopy{
	public:
		FileWriter(std::string_view name);

		~FileWriter();

		void append(const char* buf, int len);
		
		void append(std::string_view sv);

		void flushToFile();

		size_t getWrittenBytes();
	private:
		int write(const char *buf,int len);
		
	private:
		FILE* fp_;
		size_t writtenBytes_{0};
		/// dont use default bufsize it is 4096B,we enlarge it
		char buffer_[FILE_BUF_SIZE];
	};

	class LogFile{
	public:
		LogFile(std::string_view logName);

		~LogFile();

		void append(const char *buffer,int len);

		void ceateNewFile();
	private:

		std::string_view getFileName();
		
	private:
		char buffer_[FILE_NAME_LIMIT]{0};
		TimeStamp lastFlushTime_;
		TimeStamp fileStartTime_;
		int baseNameLen_;
		int logNameLen_;
		std::unique_ptr<FileWriter> fileWiter_;
	};


}




