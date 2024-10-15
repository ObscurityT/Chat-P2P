#include "Server.h"
#include "con_handler.h"
 

void Server::start_accept()
{
	//obter o io_context a partir do acceptor
	auto& io_context = acceptor_.get_executor().context();

	//passar o io_context para o con_handler
	con_handler::pointer connection = con_handler::create(io_context);

	acceptor_.async_accept(connection->socket(),
		boost::bind(&Server::handle_accept, this, connection, 
		boost::asio::placeholders::error));

}

void Server::handle_accept(con_handler::pointer connection, const boost::system::error_code& err)
{
	if (!err)
	{
		connection->Start();
	}
	start_accept();
}
