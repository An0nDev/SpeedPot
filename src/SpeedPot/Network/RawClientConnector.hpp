#pragma once

#include <stdexcept>
#include "../DataTypes/Common.hpp"

namespace SpeedPot::Network {
    class RawClientConnector {
    public:
        class EOFError : public std::exception {};
        virtual DataTypes::Common::Buffer read (DataTypes::Common::Length size) = 0;
        virtual void write (DataTypes::Common::Buffer const & buffer) = 0;
    };
}
