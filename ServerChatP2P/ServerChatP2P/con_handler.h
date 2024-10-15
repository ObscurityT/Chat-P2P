#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

class con_handler : public boost::enable_shared_from_this<con_handler>
{
private:
	tcp::socket sock;
	std::string message = "Hello from server!";
	enum { max_lenght = 1024 };
	char data[max_lenght];

public:
	typedef boost::shared_ptr<con_handler> pointer;

	//constructor
	con_handler(boost::asio::io_service& io_service) : sock(io_service) {}

	//creating a pointer
	static pointer create(boost::asio::io_service& io_service);


	//socket creation
	tcp::socket& socket();

	void Start();
	void handle_read(const boost::system::error_code& err, size_t bytes_transferred);
	void handle_write(const boost::system::error_code& err, size_t bytes_transferred);

};
