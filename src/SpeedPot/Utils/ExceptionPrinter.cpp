#include "ExceptionPrinter.hpp"

#include <cxxabi.h>
#include <iostream>
#include <sstream>

namespace SpeedPot::Utils {
    const std::string ExceptionPrinter::DEFAULT_LABEL = "SpeedPot default ";
    void ExceptionPrinter::print (std::exception const & exception, std::string const & label, std::ostream & target) {
        int status;
        char* realName = abi::__cxa_demangle (typeid (exception).name (), nullptr, nullptr, &status); // according to https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
        
        std::stringstream outputText;
        if (status == 0) {
            outputText << label << " exception handler called after throwing an instance of '" << realName << "'" << std::endl << "  what():  " << exception.what () << std::endl;
            target << outputText.str ();
            free (realName);
        } else {
            outputText << label << " exception hander failed: demangle returned " << status << "\n";
            target << outputText.str ();
            // realName == nullptr
        }
    }
}