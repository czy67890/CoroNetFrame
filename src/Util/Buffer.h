/*!
 * \file Buffer.h
 *
 * \author czy
 * \date 2023.04.02
 */
#pragma once
#include <cstddef>

#include <cstring>
#include <vector>
#include <string>


namespace cBase{
	/*!
	 * \class Buffer
	 * \brief 一个供TCP输入输出使用的缓冲区，自动增长
	 * \author czy
	 * \date 2023.04.02
	 */
	class Buffer {
	public:
		
		Buffer();


		~Buffer();
		void writeToBuffer(const char *msg,int len);

		/*!
		 *  @brief 读取N个字节,并且不会从缓冲中消去这些字节
		 *  @param readBytes读取的字符个数
		 *  @return string读取到的字符串
		 */
		std::string_view readNBytesFormBufferNotTake(int readBytes);
		/*!
		 *  @brief  上面函数的取出版
		 */
		std::string readNBytesFormBufferTake(int readBytes);

		std::string readAllAndTake();

		std::string_view readAllNotTake();

		/*!
		 *  @brief  从文件描述符获得数据并且写入buffer_
		 *  @param fd,欲读取的文件描述符
		 *  @return 
		 *
		 */

		void readFd(int fd,int len);

		inline int readAbleBytes() {
			return writeIndex_ - readIndex_;
		}

		inline int writeAbleBytes() {
			return size_ - writeIndex_;
		}

		
		int headEmptyLen();
	

	private:

		void resizeBuffer(int neededLen);
		
	private:

		int size_;
		std::vector<char> buffer_;///数据的buffer
		int readIndex_; ///<读取的位置
		int writeIndex_; ///<下一个写入的位置
	};
}