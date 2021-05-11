#include "SingleNotifyEvent.hpp"

namespace SpeedPot::Utils {
    bool SingleNotifyEvent::isSet () {
        std::lock_guard <std::mutex> lockGuard (lock);
        return isSet_;
    }
    
    void SingleNotifyEvent::set () {
        std::lock_guard <std::mutex> lockGuard (lock);
        isSet_ = true;
        trigger.notify_one ();
    }
    
    void SingleNotifyEvent::clear () {
        std::lock_guard <std::mutex> lockGuard (lock);
        isSet_ = false;
    }
    
    void SingleNotifyEvent::wait () {
        while (!isSet ()) {
            std::unique_lock <std::mutex> uniqueLock (lock);
            trigger.wait (uniqueLock);
        }
    }
}