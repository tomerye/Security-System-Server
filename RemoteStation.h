/*
 * RemoteStation.h
 *
 *  Created on: Dec 22, 2012
 *      Author: root
 */

#ifndef REMOTESTATION_H_
#define REMOTESTATION_H_


#include <boost/asio.hpp>
#include <iostream>

namespace securityServer {

class RemoteStation {
public:
	RemoteStation();
	RemoteStation(tcp::socket)
	virtual ~RemoteStation();
	int getID(){return id_;}
private:
	int id_;
	tcp::socket socket_;

};

} /* namespace securityServer */
#endif /* REMOTESTATION_H_ */
