#include "PingPacket.hpp"
#include "../../Clientbound/Status/PongPacket.hpp"
#include "../../../../Network/Client.hpp"

namespace SpeedPot::Packet::Packets::Serverbound::Status {
    const DataTypes::VarIntNR PingPacket::ID = 0x01;
    PingPacket::PingPacket (DataTypes::LongNR const & payload) : payload (payload) {}
    Packet* PingPacket::readFrom (Network::RawClientConnector & clientConnector) {
        return new PingPacket (DataTypes::Long::readFrom (clientConnector).value);
    }
    void PingPacket::handle (Packet* packet, Network::Client & client) {
        std::cout << "[!] handling ping packet" << std::endl;
        auto pingPacket = (PingPacket*) packet;
        Clientbound::Status::PongPacket (pingPacket->payload).sendTo (client.connector, client);
    }
}