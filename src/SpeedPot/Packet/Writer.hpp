#pragma once

#include "../Network/RawClientConnector.hpp"
#include "../DataTypes/VarInt.hpp"
#include <vector>
#include "../DataTypes/Common.hpp"

namespace SpeedPot::Packet {
    class Writer {
    public:
        static void writeTo (Network::RawClientConnector & clientConnector, DataTypes::VarIntNR const & id, std::vector <DataTypes::Common::Buffer> const & fieldsData);
    };
}