#include "ResponsePacket.hpp"
#include "../../../Writer.hpp"
#include "../../../../Network/Client.hpp"
#include "../../../../Network/Server.hpp"

namespace SpeedPot::Packet::Packets::Clientbound::Status {
    const DataTypes::VarIntNR ResponsePacket::ID = 0x00;
    void ResponsePacket::sendTo (Network::RawClientConnector & clientConnector, Network::Client & client) {
        Writer::writeTo (clientConnector, ResponsePacket::ID, {
            DataTypes::String::toBinaryRepresentation (jsonResponse)
        });
    }
}