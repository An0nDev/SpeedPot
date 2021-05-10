#pragma once

#include <tuple>
#include <map>

#include "Base.hpp"
#include "../DataTypes/VarInt.hpp"
#include "../Network/RawClientConnector.hpp"
#include "../Network/Client.hpp"

#include "Packets/Serverbound/Handshaking/Handshake.hpp"

namespace SpeedPot::Packet {
    class List {
    public:
        typedef Network::Client::State RequiredState;
        typedef DataTypes::VarIntNR RequiredID;
        typedef Packet* (*PointerToPacketReadFrom) (Network::RawClientConnector &);
        typedef void (*PointerToPacketHandle) (Packet*, Network::Client &);

        typedef std::tuple <PointerToPacketReadFrom, PointerToPacketHandle> PacketListEntry;
        typedef std::map <RequiredID, PacketListEntry> IDsToEntries;
        typedef std::map <RequiredState, IDsToEntries> StatesToIDs;
        typedef std::map <Direction, StatesToIDs> DirectionsToStates;
        DirectionsToStates PACKET_LIST; // READ-ONLY! do not modify
        List () {
            IDsToEntries clientboundHandshaking;
            StatesToIDs clientbound;
            clientbound [Network::Client::State::HANDSHAKING] = clientboundHandshaking;

            IDsToEntries serverboundHandshaking;
            serverboundHandshaking [0x00] = {&Packets::HandshakePacket::readFrom, &Packets::HandshakePacket::handle};
            StatesToIDs serverbound;
            serverbound [Network::Client::State::HANDSHAKING] = serverboundHandshaking;

            PACKET_LIST [Direction::CLIENTBOUND] = clientbound;
            PACKET_LIST [Direction::SERVERBOUND] = serverbound;
        }
    };
}