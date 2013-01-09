
#ifndef REMOTESTATION_H_
#define REMOTESTATION_H_



#include "Packet.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


namespace securityServer {

using boost::asio::ip::tcp;


class RemoteStation {
public:
	RemoteStation();
	RemoteStation(boost::asio::io_service& io_service);
	void send(const securityClient::Packet& packet);
	void startListening();
	virtual ~RemoteStation();
	int getID() const {return id_;}
	tcp::socket& getSocket(){return socket_;}
private:
	void handle_read_data(const size_t header,const boost::system::error_code& error);
	void handle_read_packet(const boost::asio::streambuf &buf, boost::system::error_code &error);
	int id_;
	tcp::socket socket_;


};

} /* namespace securityServer */
#endif /* REMOTESTATION_H_ */
