#include "SpeedPot/Network/Server.hpp"
#include "SpeedPot/Utils/ExceptionPrinter.hpp"

int main () {
    try {
        SpeedPot::Network::Server server (25566, "\u00A7l\u00A7fSpeedPot test server");
        server.listen (1);
    } catch (std::exception & exception) {
        SpeedPot::Utils::ExceptionPrinter::print (exception, "SpeedPot main");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
