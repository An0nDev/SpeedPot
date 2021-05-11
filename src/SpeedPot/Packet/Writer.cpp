#include "Writer.hpp"

namespace SpeedPot::Packet {
    void Writer::writeTo (Network::RawClientConnector & clientConnector, DataTypes::VarIntNR const & id, std::vector <DataTypes::Common::Buffer> const & fieldsData) {
        DataTypes::Common::Buffer idAsVarInt = DataTypes::VarInt::toBinaryRepresentation (id);
        DataTypes::VarIntNR totalLength = idAsVarInt.size;
        for (DataTypes::Common::Buffer const & fieldData : fieldsData) {
            totalLength += fieldData.size;
        }
        clientConnector.write (DataTypes::VarInt::toBinaryRepresentation (totalLength));
        clientConnector.write (idAsVarInt);
        for (DataTypes::Common::Buffer const & fieldData : fieldsData) {
            clientConnector.write (fieldData);
        }
    }
}