


#include "Server.h"

namespace securityServer {

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_service& io_service,
		const tcp::endpoint& endpoint) :
		io_service_(io_service), acceptor_(io_service, endpoint) {
	remote_station_ptr newRemoteStation(new RemoteStation(io_service));
	acceptor_.async_accept(newRemoteStation->getSocket(),
			boost::bind(&Server::handle_accept, this, newRemoteStation,
					boost::asio::placeholders::error));
}

void Server::handle_accept(remote_station_ptr remoteStation,
		boost::system::error_code& error) {
	// read header
	size_t header;
	boost::asio::read(remoteStation->getSocket(),
			boost::asio::buffer(&header, sizeof(header)));
	std::cout << "body is " << header << " bytes" << std::endl;

	// read body
	boost::asio::streambuf buf;
	const size_t rc = boost::asio::read(remoteStation->getSocket(),
			buf.prepare(header));
	buf.commit(header);
	std::cout << "read " << rc << " bytes" << std::endl;

	// deserialize
	std::istream is(&buf);
	boost::archive::text_iarchive ar(is);
	securityClient::Packet packet;
	ar & packet;
	if(remote_station_map_.find(packet.client_id_)!=std::map::end)//if the id of new client
	{
		remote_station_map_[packet.client_id_]=remoteStation;
		remoteStation->startListening();
	}//if the id already exist something is wrong
	else
	{
		remoteStation->~RemoteStation();
	}

//	remote_station_ptr newRemoteStation(new RemoteStation(io_service));
//	acceptor_.async_accept(newRemoteStation->getSocket(),
//				boost::bind(&Server::handle_accept, this, newRemoteStation,
//						boost::asio::placeholders::error));
}


void Server::sendTo(int remote_station_id, securityClient::Packet& packet)
{
	remote_station_map_[remote_station_id]->send(packet);
}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

} /* namespace securityServer */
