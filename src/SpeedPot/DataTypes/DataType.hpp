#pragma once

#include <cstdlib>
#include <cstring>

#include "Common.hpp"
#include "../Network/RawClientConnector.hpp"

namespace SpeedPot::DataTypes {
    template <class NR /* native representation */>
    class ReadResult /* Result of calling DataType::readFrom */ {
    public:
        const NR value;
        const Common::Length length;
        ReadResult (NR const & value, Common::Length const & length)
        : value (value), length (length) {};
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
