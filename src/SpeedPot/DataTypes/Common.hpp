#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <new>
#include <iostream>

namespace SpeedPot::DataTypes::Common {
    typedef uintmax_t Length;
    typedef unsigned char Byte;
    Byte* safeMalloc (size_t size);

    class Buffer /* A block of data with a size */ {
    public:
        Byte* pointer;
        const Length size;
        explicit Buffer (Length const & size) : pointer (safeMalloc (size)), size (size) {
            // std::cout << "Buffer (Length const &) called" << std::endl;
            // std::cout << "made new pointer " << (void*) pointer << std::endl;
        };
        Buffer (Byte* const & pointer, Length const & size) /* normal constructor, uses existing data, TRANSFERRING OWNERSHIP */
        : pointer (pointer), size (size) {
            // std::cout << "Buffer (Byte* const &, Length const &) called" << std::endl;
            // std::cout << "made from existing pointer " << (void*) pointer << std::endl;
        };
        static Buffer copyFrom (Byte* const & oldPointer, Length const & size) /* makes a copy, returned object has ownership of copy */ {
            Byte* newPointer = safeMalloc (size);
            memcpy ((void*) newPointer, (void*) oldPointer, size);
            return Buffer (newPointer, size);
        };
        Buffer (Buffer const & old) /* copy-constructor */
        : pointer (nullptr), size (old.size) {
            // std::cout << "Buffer (Buffer const &) called" << std::endl;
            pointer = safeMalloc (size);
            // std::cout << "copying from old pointer " << (void*) old.pointer << " to new " << (void*) pointer << std::endl;
            memcpy ((void*) pointer, (void*) old.pointer, size);
        }
        Buffer (Buffer const && old) /* move-constructor */
        : pointer (nullptr), size (old.size) {
            // std::cout << "Buffer (Buffer const &&) called" << std::endl;
            pointer = safeMalloc (size);
            memcpy ((void*) pointer, (void*) old.pointer, size);
        }
        ~Buffer () /* destructor */ {
            // std::cout << "~Buffer () called" << std::endl;
            // std::cout << "freeing pointer " << (void*) pointer << std::endl;
            free ((void*) pointer);
        }
    };
}
std::ostream & operator<< (std::ostream & ostream, const SpeedPot::DataTypes::Common::Buffer & binaryRepresentation);