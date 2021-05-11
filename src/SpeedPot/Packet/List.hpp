#pragma once

#include <tuple>
#include <map>

#include "Base.hpp"
#include "../DataTypes/VarInt.hpp"
#include "../Network/RawClientConnector.hpp"
#include "../Network/State.hpp"

#include "Packets/Serverbound/Handshaking/HandshakePacket.hpp"
#include "Packets/Serverbound/Status/PingPacket.hpp"
#include "Packets/Serverbound/Status/RequestPacket.hpp"

namespace SpeedPot::Packet {
    class List {
    public:
        typedef Network::State RequiredState;
        typedef DataTypes::VarIntNR RequiredID;
        typedef Packet* (*PointerToPacketReadFrom) (Network::RawClientConnector &);
        typedef void (*PointerToPacketHandle) (Packet*, Network::Client &);

        typedef std::tuple <PointerToPacketReadFrom, PointerToPacketHandle> PacketListEntry;
        typedef std::map <RequiredID, PacketListEntry> IDsToEntries;
        typedef std::map <RequiredState, IDsToEntries> StatesToIDs;
        StatesToIDs SERVERBOUND_PACKET_LIST; // READ-ONLY! do not modify
        List () {
            using namespace Packets::Serverbound;

            {
                using namespace Handshaking;
                IDsToEntries handshaking;

                handshaking [HandshakePacket::ID] = {&HandshakePacket::readFrom, &HandshakePacket::handle};

                SERVERBOUND_PACKET_LIST [Network::State::HANDSHAKING] = handshaking;
            }

            {
                using namespace Status;
                IDsToEntries status;

                status [RequestPacket::ID] = {&RequestPacket::readFrom, &RequestPacket::handle};
                status [PingPacket::ID] = {&PingPacket::readFrom, &PingPacket::handle};

                SERVERBOUND_PACKET_LIST [Network::State::STATUS] = status;
            }
        }
    };
}