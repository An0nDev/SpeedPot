cmake_minimum_required(VERSION 3.19)
project(SpeedPot)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpeedPot src/main.cpp src/SpeedPot/SpeedPot.cpp src/SpeedPot/SpeedPot.hpp src/SpeedPot/Packet/Common.hpp src/SpeedPot/DataTypes/Common.hpp src/SpeedPot/DataTypes/DataType.hpp src/SpeedPot/Network/RawClientConnector.hpp src/SpeedPot/DataTypes/VarInt.hpp src/SpeedPot/DataTypes/Boolean.hpp src/SpeedPot/Common.hpp src/SpeedPot/Network/NetworkedRawClientConnector.hpp src/SpeedPot/Network/DummyRawClientConnector.cpp src/SpeedPot/Network/DummyRawClientConnector.hpp src/SpeedPot/DataTypes/Common.cpp src/SpeedPot/DataTypes/String.hpp src/SpeedPot/DataTypes/Natives.hpp src/SpeedPot/Packet/Base.hpp src/SpeedPot/Network/Client.hpp src/SpeedPot/Packet/List.hpp src/SpeedPot/Packet/Packets/Serverbound/Handshaking/Handshake.hpp)