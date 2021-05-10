#pragma once

#include "RawClientConnector.hpp"
#include "../DataTypes/Common.hpp"

namespace SpeedPot::Network {
    class DummyRawClientConnector : public RawClientConnector {
    private:
        DataTypes::Common::Buffer data;
        DataTypes::Common::Length currentIndex;
    public:
        explicit DummyRawClientConnector (DataTypes::Common::Buffer const & sourceData);
        DataTypes::Common::Buffer read (DataTypes::Common::Length size);
        ~DummyRawClientConnector ();
    };
}