#pragma once

#include <cstdlib>
#include <cstring>

#include "Common.hpp"
#include "../Network/RawClientConnector.hpp"

namespace SpeedPot::DataTypes {
    template <class NR /* native representation */>
    class ReadResult /* Result of calling DataType::readFrom */ {
    public:
        const NR nativeRepresentation;
        const Common::Length fieldLength;
        ReadResult (NR const & nativeRepresentation, Common::Length const & fieldLength)
        : nativeRepresentation (nativeRepresentation), fieldLength (fieldLength) {};
    };
    class ProtocolViolationException : public std::runtime_error {
    public: explicit ProtocolViolationException (const char* what) : std::runtime_error (what) {};
    };
    template <class NR /* native representation */>
    class DataType {
    public:
        static ReadResult <NR> readFrom (Network::RawClientConnector & clientConnector);
        static Common::Buffer toBinaryRepresentation (NR const & nativeRepresentation);
    };
}
