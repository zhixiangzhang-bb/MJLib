#include "mjlib_net_tcp.h"
#include <cstring>
#include <regex>
#pragma comment(lib, "ws2_32.lib")



namespace mjlib {

	namespace net {

		/**
		 * @brief 
		 */
		TcpClient::TcpClient():serverAddr(), romotport(4000)
		{
			InitSocket();
		}

		/**
		 * @brief 析构函数
		 */
		TcpClient::~TcpClient()
		{
			closesocket(clientSocket);
			WSACleanup();
		}

		/**
		 * @brief 设置IP和端口
		 * @param ip IP地址
		 * @param port 端口号
		 * @return 执行状态	
		 */
		int32_t TcpClient::SetIpPort(const std::string& ip, int32_t port)
		{								
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(port);
			serverAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str()); // 服务器IP地址
			return 1;
		}

		/**
		 * @brief 连接服务器
		 * @return 连接状态
		 */
		int32_t TcpClient::Connect()
		{
			//创建套接字，如果错误返回-2
			clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (SOCKET_ERROR == clientSocket)
			{
				return -1;
			}
			//返回连接状态
			return connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
		}

		/**
		 * @brief 发送数据
		 * @param data 数据
		 * @return 发送状态
		 */
		int32_t TcpClient::Send(const std::string& data)
		{
			auto buff = data.c_str();
			auto size = send(clientSocket, buff, strlen(buff), 0);
			if (size <=0)
			{
					return -1;
			}
			return 1;
		}

		/**
		 * @brief 接收数据
		 * @param size 尺寸
		 * @param buff 数据缓冲区
		 * @return 
		 */
		int32_t  TcpClient::Receive(const int32_t size, char* buff)
		{
			if (buff == nullptr) {
				return -1;
			}

			if (recv(clientSocket, (char*)buff, size, 0) != size) {
				return -1;
			}
			return 1;
		}


		/**
		 * @brief 断开连接
		 * @return 断开状态
		 */
		int32_t TcpClient::Disconnect()
		{
			shutdown(clientSocket, SD_BOTH);
			return closesocket(clientSocket);

		}

		/**
		 * @brief 初始化套接字
		 * @return 初始化状态
		 */
		int32_t TcpClient::InitSocket()
		{
			//确定版本，如果错误返回-1
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
				return -1;
			}
			return 1;
		}




	}

}
