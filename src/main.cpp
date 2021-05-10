#include <iostream>

#include "SpeedPot/DataTypes/Natives.hpp"
#include "SpeedPot/Network/DummyRawClientConnector.hpp"
#include "SpeedPot/Packet/List.hpp"

template <typename Pointer>
class PointerCleaner {
public:
    Pointer wrapped;
    explicit PointerCleaner (Pointer const & wrapped) : wrapped (wrapped) {};
    ~PointerCleaner () { delete wrapped; }
};

int main () {
    {
        using namespace SpeedPot::DataTypes;
        typedef uint32_t NativeTestType;
        NativeTestType source = 435435423;
        Common::Buffer buffer = NativeDataType <NativeTestType>::toBinaryRepresentation (source);
        SpeedPot::Network::DummyRawClientConnector dummyClientConnector (buffer);
        NativeTestType dest = NativeDataType <NativeTestType>::readFrom (dummyClientConnector).nativeRepresentation;
        std::cout << "source: " << source << ", dest: " << dest << std::endl;
    }

    {
        using namespace SpeedPot;

        DataTypes::Common::Buffer buffer (1);
        Network::DummyRawClientConnector dummyRawClientConnector (buffer);
        Network::Client client;

        Network::Client::State state = Network::Client::State::HANDSHAKING;
        DataTypes::VarIntNR id = 0x00;

        Packet::List list;
        Packet::List::PacketListEntry entry = list.PACKET_LIST [Packet::Direction::CLIENTBOUND] [state] [id];
        Packet::List::PointerToPacketReadFrom pointerToPacketReadFrom;
        Packet::List::PointerToPacketHandle pointerToPacketHandle;
        std::tie (pointerToPacketReadFrom, pointerToPacketHandle) = entry;
        PointerCleaner <Packet::Packet*> readPacketWrapper = PointerCleaner <Packet::Packet*> (pointerToPacketReadFrom (dummyRawClientConnector));
        try {
            pointerToPacketHandle (readPacketWrapper.wrapped, client);
        } catch (std::exception & exception) {
            std::cout << "caught exception" << std::endl;
        }
    }
    return 0;
}
