#pragma once

namespace SpeedPot::Utils {
    template <typename Pointer>
    class PointerCleaner { // Makes sure a pointer gets deleted if an exception is caught
        Pointer toClean;
    public:
        explicit PointerCleaner (Pointer const & toClean) : toClean (toClean) {};
        ~PointerCleaner () { delete toClean; };
    };
}
