#include "CommunicationManager.h"
#include <string>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>

using boost::asio::ip::udp;

int OCSPORT = 50001; // 운용통제기 Port
std::string OCSIP = "172.16.12.114"; // 운용통제기 IP

int GMSPORT = 50005; // 유도탄 Port
std::string GMSIP = "172.16.12.51"; // 유도탄 IP

int MYPORT = 50004;
boost::asio::io_context io_context;

int CommunicationManager::getCurrentMissileNum() 
{
    
}

/*
                           ☆☆☆☆☆☆☆  운용통제기 송신 ☆☆☆☆☆☆☆
*/

void CommunicationManager::sendOCS(const Message& message) {
    udp::socket ocs_socket(io_context, udp::endpoint(udp::v4(), 0));
    udp::endpoint server_endpoint(boost::asio::ip::address::from_string(OCSIP), OCSPORT);

    std::ostringstream archive_stream;
    boost::archive::binary_oarchive archive(archive_stream);
    archive << message;

    std::string serialized_message = archive_stream.str();

    ocs_socket.send_to(boost::asio::buffer(serialized_message), server_endpoint);
}

/*
                           ☆☆☆☆☆☆☆    미사일모의기 송신  ☆☆☆☆☆☆☆
*/

void CommunicationManager::sendGMS(const Message& message) {
    udp::socket gms_socket(io_context, udp::endpoint(udp::v4(), 0));
    udp::endpoint server_endpoint(boost::asio::ip::address::from_string(GMSIP), GMSPORT);

    std::ostringstream archive_stream;
    boost::archive::binary_oarchive archive(archive_stream);
    archive << message;

    std::string serialized_message = archive_stream.str();

    gms_socket.send_to(boost::asio::buffer(serialized_message), server_endpoint);
}

/*
                           ☆☆☆☆☆☆☆    메시지 수신  ☆☆☆☆☆☆☆☆☆
 */

Message CommunicationManager::receiver()
{
    udp::socket ocs_socket(io_context, udp::endpoint(udp::v4(), MYPORT));
    udp::endpoint ocs_client_endpoint;

    char data[1024];
    size_t ocs_length = ocs_socket.receive_from(boost::asio::buffer(data), ocs_client_endpoint);

    std::string ocs_message(data, ocs_length);

    std::istringstream archive_stream(ocs_message);
    boost::archive::binary_iarchive archive(archive_stream);

    Message received_data;
    archive >> received_data;

    return received_data;
}

