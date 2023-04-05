#include "Buffer.h"
#include <assert.h>
#include <sys/uio.h>
/*****************************************************************//**
 * \file   Buffer.cc
 * \brief  
 * 
 * \author czy
 * \date   April 2023
 *********************************************************************/

constexpr int DEFAULT_REMAINED_HEADER = 8;
constexpr int DEFAULT_INIT_BUFFER_SIZE = 1024;
//默认512KB的大小，防止栈溢出
constexpr int DEFAULT_STACK_BUFFER = 1024*512;

cBase::Buffer::Buffer()
	:readIndex_(DEFAULT_REMAINED_HEADER),writeIndex_(DEFAULT_REMAINED_HEADER),size_(DEFAULT_INIT_BUFFER_SIZE)
{
	buffer_.resize(DEFAULT_INIT_BUFFER_SIZE);
}

cBase::Buffer::~Buffer()
{

}

void cBase::Buffer::writeToBuffer(const char* msg, int len)
{
	if(writeAbleBytes() < len){
		resizeBuffer(len);
	}
	assert(writeAbleBytes() >= len);
	for (int count = 0;count < len;++count ) {
		buffer_[writeIndex_++] = msg[count];
	}
}

std::string_view cBase::Buffer::readNBytesFormBufferNotTake(int readBytes)
{	
	int reallyReadBytes = std::min(readAbleBytes(),readBytes);
	return std::string_view(&(buffer_[readIndex_]),reallyReadBytes);
}

std::string cBase::Buffer::readNBytesFormBufferTake(int readBytes)
{
	int reallyReadBytes = std::min(readBytes,readAbleBytes());
	std::string ans;
	ans.reserve(reallyReadBytes);
	for(;readIndex_ < readIndex_ + reallyReadBytes;++readIndex_){
		ans.push_back(buffer_[readIndex_]);
	}
	return ans;
}

std::string cBase::Buffer::readAllAndTake()
{
	std::string ansStr;
	ansStr.reserve(readAbleBytes());
	for (; readIndex_ <= writeIndex_;++ readIndex_) {
		ansStr.push_back(buffer_[readIndex_]);
	}
	///复位
	readIndex_ = DEFAULT_REMAINED_HEADER;
	writeIndex_ = DEFAULT_REMAINED_HEADER;
	return ansStr;
}

std::string_view cBase::Buffer::readAllNotTake()
{
	return std::string_view(&(buffer_[readIndex_]),readAbleBytes());
}

void cBase::Buffer::readFd(int fd,int len)
{	
	///pay attention writeAbleBytes this need call twice
	if(len > writeAbleBytes()){
		resizeBuffer(0);
	}
	int writeAble = writeAbleBytes();
	struct iovec ivoecs[2];
	char buffer[DEFAULT_STACK_BUFFER];
	if(len > writeAble){
		
	}
	else{
		
	}

}

int cBase::Buffer::headEmptyLen()
{
	return readIndex_ - DEFAULT_REMAINED_HEADER;
}

void cBase::Buffer::resizeBuffer(int neededLen)
{	
	int nowCanProvide = headEmptyLen();
	///需要扩容的情况
	if(nowCanProvide < neededLen){
		buffer_.resize(neededLen + size_);
	}
	else{
		int movedLen = readAbleBytes();
		int oldIndex = readIndex_;
		for(int newHeader = DEFAULT_REMAINED_HEADER;newHeader < DEFAULT_REMAINED_HEADER + movedLen;++newHeader,oldIndex++){
			buffer_[newHeader] = buffer_[oldIndex];
		}
	}
}



