#include "src/Util/FileUnit.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
CUtil::FileWriter::FileWriter(std::string_view fileName)
	:fp_(::fopen(fileName.data(), "a"))
{	
	assert(fp_);
	::setbuf(fp_, buffer_);
}

CUtil::FileWriter::~FileWriter()
{
	::fclose(fp_);
}

void CUtil::FileWriter::append(const char * buf,int len)
{	
	size_t written = 0;
	while(written != len){
		int thisTimeWrite = write(buf,len);
		writtenBytes_ += thisTimeWrite;
		if(thisTimeWrite == -1){
			//TODO:log error
			return;
		}
		written += thisTimeWrite;
	}
}

void CUtil::FileWriter::append(std::string_view sv)
{
	append(sv.data(),sv.size());
}


void CUtil::FileWriter::flushToFile()
{
	::fflush_unlocked(fp_);
}

size_t CUtil::FileWriter::getWrittenBytes()
{
	return writtenBytes_;
}

int CUtil::FileWriter::write(const char* buf, int len)
{
	return ::fwrite_unlocked(buf,1,len,fp_);
}

CUtil::LogFile::LogFile(std::string_view logName)
	:baseNameLen_(logName.size() + 1),logNameLen_(baseNameLen_ + 20)
{	
	///memcpy?
	std::copy(logName.begin(),logName.end(),&buffer_[0]);
	buffer_[logName.size()] = '.';
	ceateNewFile();
}

CUtil::LogFile::~LogFile()
{

}

std::string_view CUtil::LogFile::getFileName()
{	
	std::string timeStr = fileStartTime_.toStringOnlySecond();
	std::copy(timeStr.begin(),timeStr.end(),&buffer_[baseNameLen_]);
	std::string log(".log");
	std::copy(log.begin(), log.end(), &buffer_[logNameLen_ - 1]);
	return std::string_view (buffer_,logNameLen_ + log.size());
}

void CUtil::LogFile::append(const char *data,int len)
{
	fileWiter_->append(data,len);
}

void CUtil::LogFile::ceateNewFile()
{
	fileStartTime_ = TimeStamp::Now();
	std::string_view fileName = getFileName();
	lastFlushTime_ = fileStartTime_;
	fileWiter_ .reset(new FileWriter(fileName));
}
