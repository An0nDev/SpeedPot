#pragma once

#include "../../../Base.hpp"
#include "../../../ClientboundBase.hpp"
#include "../../../../DataTypes/VarInt.hpp"
#include "../../../../DataTypes/Natives.hpp"

namespace SpeedPot::Packet::Packets::Clientbound::Status {
    class PongPacket : public Packet, ClientboundPacket {
        DataTypes::LongNR payload;
    public:
        static const DataTypes::VarIntNR ID;
        explicit PongPacket (DataTypes::LongNR const & payload) : payload (payload) {};

        void sendTo (Network::RawClientConnector & clientConnector, Network::Client & client);
    };
}