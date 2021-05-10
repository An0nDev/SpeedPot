#pragma once

#include "DataType.hpp"
#include "Common.hpp"

namespace SpeedPot::DataTypes {
    typedef bool BooleanNR;
    template <>
    class DataType <BooleanNR> {
    public:
        static ReadResult <BooleanNR> readFrom (Network::RawClientConnector & clientConnector) {
            Common::Buffer booleanBuffer = clientConnector.read (1);
            return ReadResult <BooleanNR> ((*booleanBuffer.pointer) == 0x01, 1);
        };
        static Common::Buffer toBinaryRepresentation (BooleanNR nativeRepresentation) {
            Common::Buffer buffer (1);
            *buffer.pointer = nativeRepresentation ? 0x01 : 0x00;
            return buffer;
        };
    };
    typedef DataType <BooleanNR> Boolean;
}
