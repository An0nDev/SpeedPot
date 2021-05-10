#pragma once

#include <string>

#include "DataType.hpp"
#include "Common.hpp"
#include "VarInt.hpp"

namespace SpeedPot::DataTypes {
    typedef std::string StringNR;
    template <>
    class DataType <StringNR> { // from https://wiki.vg/index.php?title=Data_types
        static const uint32_t MAX_LENGTH_BYTES = 32767 /* characters */ * 4 /* max code units per character */;
    public:
        static ReadResult <StringNR> readFrom (Network::RawClientConnector & clientConnector) {
            ReadResult <VarIntNR> lengthReadResult = VarInt::readFrom (clientConnector);
            VarIntNR length = lengthReadResult.nativeRepresentation;
            if (length > MAX_LENGTH_BYTES) throw ProtocolViolationException ("readFrom: String is too big");

            Common::Buffer buffer = clientConnector.read (length);
            StringNR result ((char*) buffer.pointer, length);

            return ReadResult <StringNR> (result, lengthReadResult.fieldLength + length);
        };
        static Common::Buffer toBinaryRepresentation (StringNR const & nativeRepresentation) {
            if (nativeRepresentation.size () > MAX_LENGTH_BYTES) throw ProtocolViolationException ("toBinaryRepresentation: String is too big");
            auto checkedLength = (VarIntNR) /* cast is safe after checking max length */ nativeRepresentation.size ();

            Common::Buffer lengthVarInt = VarInt::toBinaryRepresentation (checkedLength);
            Common::Buffer output (lengthVarInt.size + checkedLength);
            memcpy (output.pointer, lengthVarInt.pointer, lengthVarInt.size); // copy length into buffer at front
            memcpy (output.pointer + lengthVarInt.size, nativeRepresentation.data (), checkedLength); // copy string data into buffer after length
            return output;
        };
    };
    typedef DataType <StringNR> String;
}
