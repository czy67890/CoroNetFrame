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
	 * \brief һ����TCP�������ʹ�õĻ��������Զ�����
	 * \author czy
	 * \date 2023.04.02
	 */
	class Buffer {
	public:
		
		Buffer();


		~Buffer();
		void writeToBuffer(const char *msg,int len);

		/*!
		 *  @brief ��ȡN���ֽ�,���Ҳ���ӻ�������ȥ��Щ�ֽ�
		 *  @param readBytes��ȡ���ַ�����
		 *  @return string��ȡ�����ַ���
		 */
		std::string_view readNBytesFormBufferNotTake(int readBytes);
		/*!
		 *  @brief  ���溯����ȡ����
		 */
		std::string readNBytesFormBufferTake(int readBytes);

		std::string readAllAndTake();

		std::string_view readAllNotTake();

		/*!
		 *  @brief  ���ļ�������������ݲ���д��buffer_
		 *  @param fd,����ȡ���ļ�������
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
		std::vector<char> buffer_;///���ݵ�buffer
		int readIndex_; ///<��ȡ��λ��
		int writeIndex_; ///<��һ��д���λ��
	};
}