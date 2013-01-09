

#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <Packet.h>
#include "RemoteStation.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace securityServer {

typedef boost::shared_ptr<RemoteStation> remote_station_ptr;


using boost::asio::ip::tcp;

class Server {
public:
	Server(boost::asio::io_service& io_service,
			const tcp::endpoint& endpoint);
	virtual ~Server();
	void sendTo(const int remote_startion_id, securityClient::Packet& packet);

private:
	void handle_accept(remote_station_ptr remoteStation, boost::system::error_code& error);
	std::map<int,remote_station_ptr> remote_station_map_;
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;


};

} /* namespace securityServer */
#endif /* SERVER_H_ */
