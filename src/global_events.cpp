#include "simplicity/global_events.h"

#include <iostream>

namespace simplicity {

GlobalEventsError RegisterEvent(const Event& event, Callback callback) {
        event_map_[event] = callback;
}

GlobalEventsError ProcessEvent(const Event& event) {
        if (event_map_.find(event) == event_map_.end()) {

                // the event was not found
                std::cout << "This event was not registered." << std::endl;
                return GlobalEventsError::kUnregistered;
        }

        event_map_[event]();

        return GlobalEventsError::kSuccess;
}

}  // namespace simplicity
