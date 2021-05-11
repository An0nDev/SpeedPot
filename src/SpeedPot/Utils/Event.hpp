#pragma once

#include <mutex>
#include <condition_variable>

namespace SpeedPot::Utils {
    class Event {
        bool isSet_ = false;
        std::mutex lock;
        std::condition_variable trigger;
    public:
        bool isSet ();
        void set ();
        void clear ();
        void wait ();
    };
}
