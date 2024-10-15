#pragma once

#include "con_handler.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>


class Server
{

private:
	tcp::acceptor acceptor_;

	void start_accept();

public:
	//constructor for accepting connection from client

	Server(boost::asio::io_service& io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234))
	{
		start_accept();
	}
	void handle_accept(con_handler::pointer connection, const boost::system::error_code& err);

};