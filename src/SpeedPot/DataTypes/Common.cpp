#include "Common.hpp"

namespace SpeedPot::DataTypes::Common {
    Byte* safeMalloc (size_t size) {
        void* result = std::malloc (size);
        if (result == nullptr) throw std::bad_alloc ();
        return (Byte*) result;
    }
}
std::ostream & operator<< (std::ostream & ostream, const SpeedPot::DataTypes::Common::Buffer & binaryRepresentation) {
    ostream << "(size " << binaryRepresentation.size << ")";
    for (SpeedPot::DataTypes::Common::Length byteIndex = 0; byteIndex < binaryRepresentation.size; byteIndex++) {
        ostream << " 0b";
        uint8_t byte = *(((uint8_t*) binaryRepresentation.pointer) + byteIndex);
        for (uint_least8_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            bool bit = byte & (0b10000000 >> bitIndex);
            ostream << (bit ? "1" : "0");
        }
    }
    return ostream;
};