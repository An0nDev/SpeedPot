#pragma once

#include <bit>
#include "DataType.hpp"

namespace SpeedPot::DataTypes {
    template <class NR>
    class NativeDataType : DataType <NR> {
        static const std::endian NETWORK_BYTE_ORDER = std::endian::big;
        static const bool needsSwap = std::endian::native == NETWORK_BYTE_ORDER;
        static Common::Buffer swapByteOrder (Common::Buffer const & input /* MUST contain NR! */) {
            Common::Buffer output (sizeof (NR));
            for (Common::Length byteIndex = 0; byteIndex < sizeof (NR); byteIndex++) {
                *(output.pointer + byteIndex) = *(input.pointer + ((sizeof (NR) - 1 /* zero-indexed */) - byteIndex));
            }
            return output;
        }
    public:
        static ReadResult <NR> readFrom (Network::RawClientConnector & clientConnector) {
            Common::Buffer buffer = clientConnector.read (sizeof (NR));
            return ReadResult <NR> (*((NR*) (needsSwap ? buffer : swapByteOrder (buffer)).pointer), sizeof (NR));
        }
        static Common::Buffer toBinaryRepresentation (NR nativeRepresentation) {
            Common::Buffer buffer (sizeof (NR));
            memcpy (buffer.pointer, &nativeRepresentation, sizeof (NR));
            return needsSwap ? buffer : swapByteOrder (buffer);
        }
    };
    typedef int8_t ByteNR;
    typedef NativeDataType <ByteNR> Byte;
    typedef uint8_t UnsignedByteNR;
    typedef NativeDataType <UnsignedByteNR> UnsignedByte;
    typedef int16_t ShortNR;
    typedef NativeDataType <ShortNR> Short;
    typedef uint16_t UnsignedShortNR;
    typedef NativeDataType <UnsignedShortNR> UnsignedShort;
    typedef int32_t IntNR;
    typedef NativeDataType <IntNR> Int;
    typedef int64_t LongNR;
    typedef NativeDataType <LongNR> Long;
}