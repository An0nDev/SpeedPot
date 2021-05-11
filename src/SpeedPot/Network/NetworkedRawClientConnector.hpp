#pragma once

#include "RawClientConnector.hpp"
#include "Common.hpp"
#include <unistd.h>

namespace SpeedPot::Network {
    class NetworkedRawClientConnector : public RawClientConnector {
        SocketFD fd;
        bool closed;
    public:
        explicit NetworkedRawClientConnector (SocketFD const & fd) : fd (fd) {};
        ~NetworkedRawClientConnector () {
            if (closed) return;
            shutdown (fd, SHUT_RDWR);
            ::close (fd);
        };
        DataTypes::Common::Buffer read (DataTypes::Common::Length size) {
            DataTypes::Common::Buffer inputBuffer (size);
            DataTypes::Common::Length receivedSize = recv (fd, (void*) inputBuffer.pointer, size, 0);
            if (receivedSize == 0) throw EOFError (); // remote disconnect, according to recv man page "return value"
            if (receivedSize == -1) throw std::system_error (std::error_code (errno, std::system_category ()), "Unable to read from client socket");
            DataTypes::Common::Buffer trimmedBuffer = DataTypes::Common::Buffer::copyFrom (inputBuffer.pointer, receivedSize);
            return trimmedBuffer;
        };
        void write (DataTypes::Common::Buffer const & buffer) {
            DataTypes::Common::Length sentSize = send (fd, (void*) buffer.pointer, buffer.size, 0);
            if (sentSize != buffer.size) throw std::runtime_error ("Not all bytes were written to socket");
            if (sentSize == -1) throw std::system_error (std::error_code (errno, std::system_category ()), "Unable to send to client socket");
        };
        void close () {
            shutdown (fd, SHUT_RDWR);
            ::close (fd);
            closed = true;
        }
    };
}