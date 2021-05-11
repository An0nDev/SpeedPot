#pragma once

#include <iostream>
#include <exception>

namespace SpeedPot::Utils {
    class ExceptionPrinter {
        static const std::string DEFAULT_LABEL;
    public:
        static void print (std::exception const & exception, std::string const & label = DEFAULT_LABEL, std::ostream & target = std::cout);
    };
}