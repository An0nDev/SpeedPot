#pragma once

namespace SpeedPot::Packet {
    class ClientboundPacket {
    public:
        virtual void sendTo (Network::RawClientConnector & clientConnector, Network::Client & client) = 0;
    };
}