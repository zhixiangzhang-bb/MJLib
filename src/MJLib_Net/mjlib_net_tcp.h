#pragma once

#include "mjlib_net_global.h"
#include <winsock2.h>


namespace mjlib {

	namespace net {



	/*****************************************************************
	* 类名称：
	* 功能描述：
	* 作者：zzx
	* 创建日期：2024.12.12
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



		class MJLib_Net_API TcpClient
		{
		public:
			TcpClient();


			~TcpClient();

			/**
			 * @brief 设置IP和端口
			 * @param ip IP地址
			 * @param port 端口号
			 * @return 执行状态
			 */
			int32_t SetIpPort(const std::string& ip, int32_t port);

			/**
			 * @brief 连接服务器
			 * @return 执行结果 1为正常 -1为错误
			 */
			int32_t Connect();

			/**
			 * @brief 发送数据
			 * @param data 需要发送的数据字符串
			 * @return 执行结果
			 */
			int32_t Send(const std::string& data);


			/**
			 * @brief 读取数据到缓冲区
			 * @param size 读取字节大小
			 * @param buff 读取缓冲区,原始字节数组
			 * @return 执行结果 1为正常 -1为错误
			 */
			int32_t  Receive(const int32_t size, char* buff);


			/**
			 * @brief 断开连接
			 * @return 执行结果 1为成功 -1为错误
			 */
			int32_t Disconnect();

			/**
			 * @brief 排序方式
			 */
			enum Sort
			{
				LittleSort,//小端排序
				BigSort//大端排序
			};




		private:

			/**
			 * @brief 客户端套接字
			 */
			SOCKET clientSocket;

			/**
			 * @brief 远程端口
			 */
			int32_t romotport;

			/**
			 * @brief 服务器地址
			 */
			struct sockaddr_in serverAddr;

			/**
			 * @brief 初始化套接字
			 * @return 执行状态 小于0为错误
			 */
			int32_t InitSocket();
		};


	}




}

