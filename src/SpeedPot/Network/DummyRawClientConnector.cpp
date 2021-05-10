#include "DummyRawClientConnector.hpp"
#include <iostream>

namespace SpeedPot::Network {
    DummyRawClientConnector::DummyRawClientConnector (DataTypes::Common::Buffer const & sourceData)
    : data (sourceData), currentIndex (0) {}
    DataTypes::Common::Buffer DummyRawClientConnector::read (DataTypes::Common::Length size) {
        if (currentIndex == data.size) throw RawClientConnector::EOFError ();
        DataTypes::Common::Length readableSize = (currentIndex + size <= data.size) ? size : (data.size - currentIndex);
        currentIndex += readableSize;
        return DataTypes::Common::Buffer::copyFrom (((DataTypes::Common::Byte*) data.pointer) + (currentIndex - readableSize), readableSize);
    }
    DummyRawClientConnector::~DummyRawClientConnector () {
        if (currentIndex < data.size) {
            std::cerr << "DummyRawClientConnector: " << (data.size - currentIndex) << " bytes left" << std::endl;
        }
    }
}