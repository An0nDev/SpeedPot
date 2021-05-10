#pragma once

#include <cstdint>

#include "DataType.hpp"
#include "Common.hpp"

namespace SpeedPot::DataTypes {
    typedef int32_t VarIntNR;
    typedef uint32_t UVarIntNR; // only to be used internally to copy the sign bit
    template <>
    class DataType <VarIntNR> {
        static const uint8_t MAX_LENGTH_BYTES = 5;
    public:
        static ReadResult <VarIntNR> readFrom (Network::RawClientConnector & clientConnector) {
            // from https://wiki.vg/index.php?title=Protocol&oldid=7368#VarInt_and_VarLong
            Common::Length byteCount = 0;
            VarIntNR result = 0;
            Common::Byte inputByte;
            do {
                {
                    Common::Buffer inputBuffer = clientConnector.read (1);
                    inputByte = (*inputBuffer.pointer);
                }
                Common::Byte inputValue = inputByte & 0b01111111;
                result |= inputValue << (7 * byteCount);
                byteCount++;
                if (byteCount > MAX_LENGTH_BYTES) {
                    throw ProtocolViolationException ("readFrom: VarInt is too big");
                }
            } while ((inputByte & 0b10000000) != 0);
            return ReadResult <VarIntNR> (result, byteCount);
        };
        static Common::Buffer toBinaryRepresentation (VarIntNR const & nativeRepresentation) {
            Common::Length bitSize = 0;
            {
                if (nativeRepresentation < 0) {
                    bitSize = 32; /* sign bit is set, forcing max size, since MC VarInts don't use zigzag */
                } else {
                    VarIntNR nativeRepForBitSizeCalc = nativeRepresentation;
                    do {
                        bitSize += 1;
                        nativeRepForBitSizeCalc >>= 1;
                    } while (nativeRepForBitSizeCalc != 0);
                }
            }
            Common::Length byteSize = bitSize / 7;
            if (bitSize % 7 > 0) byteSize++;
            // No need to check length since the input can't hold more than 32 bits

            Common::Buffer buffer (byteSize);

            UVarIntNR nativeRepWithSignBit = *((UVarIntNR*) &nativeRepresentation);
            for (Common::Length byteIndex = 0; byteIndex < byteSize; byteIndex++) {
                Common::Byte outByte = (Common::Byte) nativeRepWithSignBit & 0b01111111;
                if (byteIndex != (byteSize - 1)) outByte |= 0b10000000;
                *(buffer.pointer + byteIndex) = outByte;
                nativeRepWithSignBit >>= 7;
            }

            return buffer;
        };
    };
    typedef DataType <VarIntNR> VarInt;
}
