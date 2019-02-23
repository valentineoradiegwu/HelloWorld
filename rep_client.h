#pragma once
#include "zmq.hpp"
#include <iostream>

class Rep_Client
{
	zmq::context_t m_context;
	zmq::socket_t m_socket;
public:
	Rep_Client(const std::string& port="5555")
		:m_context{ 1 },
		m_socket{ m_context, ZMQ_REQ }
	{
		std::cout << "Connecting to hello world server..." << std::endl;
		m_socket.connect("tcp://localhost:" + port);
	}

	void operator()()
	{
		for (auto i : { 1, 2, 3, 4 })
		{
			zmq::message_t request(5);
			memcpy(request.data(), "Hello", 5);
			std::cout << "Sending Hello " << i << "..." << std::endl;
			m_socket.send(request);

			//  Get the reply.
			zmq::message_t reply;
			m_socket.recv(&reply);
			std::cout << "Received World " << i << std::endl;
		}
	}
};
