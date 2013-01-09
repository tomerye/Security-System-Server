#include "RemoteStation.h"

namespace securityServer {

RemoteStation::RemoteStation(boost::asio::io_service& io_service) :
		socket_(io_service) {

}

void RemoteStation::send(const securityClient::Packet & packet) {
	boost::asio::streambuf buf;
	std::ostream os(&buf);
	boost::archive::text_oarchive ar(os);
	ar & packet;
	size_t header = buf.size();
	std::vector < boost::asio::const_buffer > buffers;
	buffers.push_back(boost::asio::buffer(&header, sizeof(header)));
	buffers.push_back(buf.data());
	boost::asio::write(socket, buffers);
}

void RemoteStation::startListening() {

	size_t header;
	boost::asio::async_read(socket_,
			boost::asio::buffer(&header, sizeof(header)),
			boost::bind(&RemoteStation::handle_read_data, shared_from_this(),
					boost::asio::placeholders::error));
	boost::asio::streambuf buf;
	boost::asio::read(socket_, buf.prepare(header));
	buf.commit(header);
	std::istream is(&buf);
	boost::archive::text_iarchive ar(is);
	securityClient::Packet packet;
	ar & packet;
	std::cout << "Client id recev: " << packet.client_id_ << "\n";
}

void RemoteStation::handle_read_data(const size_t header,
		const boost::system::error_code& error) {
	boost::asio::streambuf buf;
	boost::asio::async_read(socket_, buf.prepare(header),
			boost::bind(&RemoteStation::handle_read_packet,shared_from_this(),buf,
					boost::asio::placeholders::error));
}

void RemoteStation::handle_read_packet(const boost::asio::streambuf &buf, boost::system::error_code &error){

}
RemoteStation::~RemoteStation() {
	// TODO Auto-generated destructor stub
}

} /* namespace securityServer */
