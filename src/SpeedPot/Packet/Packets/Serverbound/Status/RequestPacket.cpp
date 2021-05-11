#include <nlohmann/json.hpp>
#include "RequestPacket.hpp"
#include "../../Clientbound/Status/ResponsePacket.hpp"
#include "../../../../Network/Server.hpp"

namespace SpeedPot::Packet::Packets::Serverbound::Status {
    const DataTypes::VarIntNR RequestPacket::ID = 0x00;
    RequestPacket::RequestPacket () {}
    Packet* RequestPacket::readFrom (Network::RawClientConnector & clientConnector) {
        return new RequestPacket ();
    }
    void RequestPacket::handle (Packet* packet, Network::Client & client) {
        std::cout << "[!] handling request packet" << std::endl;
        nlohmann::json jsonResponse = {
            {"version", {
                {"name", Network::Server::VERSION_NAME},
                {"protocol", Network::Server::IMPLEMENTS_PROTOCOL_VERSION}
            }},
            {"players", {
                {"max", 420},
                {"online", 69},
                {"sample", nlohmann::json::array ()}
            }},
            {"description", {
                {"text", client.server.description}
            }}
        };
        DataTypes::StringNR jsonResponseString = jsonResponse.dump ();
        Clientbound::Status::ResponsePacket responsePacket (jsonResponseString);
        responsePacket.sendTo (client.connector, client);
    }
}