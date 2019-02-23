#pragma once
#include "zmq.hpp"
#include <iostream>
#include <thread>
#include <chrono>

class Rep_Server
{
	zmq::context_t m_context;
	zmq::socket_t m_socket;
public:
	Rep_Server(const std::string& port = "5555")
		:m_context{ 1 },
		m_socket{ m_context, ZMQ_REP }
	{
		m_socket.bind("tcp://*:" + port);
		std::cout << "Listening for packets on port " << port << std::endl;
	}

	void operator()()
	{
		while (true)
		{
			zmq::message_t request;

			//  Wait for next request from client
			m_socket.recv(&request);
			std::cout << "Received Hello" << std::endl;

			//  Do some 'work'
			std::this_thread::sleep_for(std::chrono::milliseconds{2000});

			//  Send reply back to client
			zmq::message_t reply(5);
			memcpy(reply.data(), "World", 5);
			m_socket.send(reply);
		}
	}
};
