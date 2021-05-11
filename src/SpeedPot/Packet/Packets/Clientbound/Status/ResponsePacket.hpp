#pragma once

#include "../../../Base.hpp"
#include "../../../ClientboundBase.hpp"
#include "../../../../DataTypes/String.hpp"

namespace SpeedPot::Packet::Packets::Clientbound::Status {
    class ResponsePacket : public Packet, ClientboundPacket {
        DataTypes::StringNR jsonResponse;
    public:
        static const DataTypes::VarIntNR ID;
        explicit ResponsePacket (DataTypes::StringNR const & jsonResponse) : jsonResponse (jsonResponse) {};

        void sendTo (Network::RawClientConnector & clientConnector, Network::Client & client);
    };
}
