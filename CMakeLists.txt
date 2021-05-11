cmake_minimum_required(VERSION 3.19)
project(SpeedPot)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpeedPot src/main.cpp src/SpeedPot/SpeedPot.cpp src/SpeedPot/SpeedPot.hpp src/SpeedPot/Packet/Common.hpp src/SpeedPot/DataTypes/Common.hpp src/SpeedPot/DataTypes/DataType.hpp src/SpeedPot/Network/RawClientConnector.hpp src/SpeedPot/DataTypes/VarInt.hpp src/SpeedPot/DataTypes/Boolean.hpp src/SpeedPot/Common.hpp src/SpeedPot/Network/NetworkedRawClientConnector.hpp src/SpeedPot/Network/DummyRawClientConnector.cpp src/SpeedPot/Network/DummyRawClientConnector.hpp src/SpeedPot/DataTypes/Common.cpp src/SpeedPot/DataTypes/String.hpp src/SpeedPot/DataTypes/Natives.hpp src/SpeedPot/Packet/Base.hpp src/SpeedPot/Network/Client.hpp src/SpeedPot/Packet/List.hpp src/SpeedPot/Packet/Packets/Serverbound/Handshaking/HandshakePacket.hpp src/SpeedPot/Network/Common.hpp src/SpeedPot/Network/Server.hpp src/SpeedPot/Network/State.hpp src/SpeedPot/Network/Client.cpp src/SpeedPot/Network/Server.cpp src/SpeedPot/Utils/PointerCleaner.hpp src/SpeedPot/Packet/Packets/Serverbound/Handshaking/HandshakePacket.cpp src/SpeedPot/Packet/Packets/Clientbound/Status/PongPacket.cpp src/SpeedPot/Packet/Packets/Clientbound/Status/PongPacket.hpp src/SpeedPot/Packet/Writer.cpp src/SpeedPot/Packet/Writer.hpp src/SpeedPot/Packet/Packets/Serverbound/Status/PingPacket.cpp src/SpeedPot/Packet/Packets/Serverbound/Status/PingPacket.hpp src/SpeedPot/Packet/ClientboundBase.hpp src/SpeedPot/Packet/Packets/Serverbound/Status/RequestPacket.cpp src/SpeedPot/Packet/Packets/Serverbound/Status/RequestPacket.hpp src/SpeedPot/Packet/Packets/Clientbound/Status/ResponsePacket.cpp src/SpeedPot/Packet/Packets/Clientbound/Status/ResponsePacket.hpp src/SpeedPot/Utils/Event.cpp src/SpeedPot/Utils/Event.hpp src/SpeedPot/Utils/SingleNotifyEvent.cpp src/SpeedPot/Utils/SingleNotifyEvent.hpp src/SpeedPot/Utils/ExceptionPrinter.cpp src/SpeedPot/Utils/ExceptionPrinter.hpp)

# from https://github.com/nlohmann/json
include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(SpeedPot PRIVATE nlohmann_json::nlohmann_json)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(SpeedPot PRIVATE Threads::Threads)