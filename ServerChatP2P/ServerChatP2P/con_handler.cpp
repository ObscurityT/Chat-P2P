#include "con_handler.h"


con_handler::con_handler(boost::asio::io_service& io_service) 
	:sock (io_service) {}


tcp::socket& con_handler::socket()
{
	return sock;
}


con_handler::pointer con_handler::create(boost::asio::io_service& io_service)
{
	return pointer(new con_handler(io_service));
}


void con_handler::Start()
{
	sock.async_read_some(
		boost::asio::buffer(data, max_lenght),
		boost::bind(&con_handler::handle_read, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	sock.async_write_some(
		boost::asio::buffer(message, max_lenght),
		boost::bind(&con_handler::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

}

void con_handler::handle_read(const boost::system::error_code& err, size_t bytes_transferred)
{
	if (!err)
	{
		std::cout << data << std::endl;
	}
	else {
		std::cerr << "error: " << err.message() << std::endl;
		sock.close();
	}
}

void con_handler::handle_write(const boost::system::error_code& err, size_t bytes_transferred)
{
	if (!err)
	{
		std::cout << "Server sent Hello message!" << std::endl;
	}
	else {
		std::cerr << "error: " << err.message() << std::endl;
		sock.close();
	}
}

