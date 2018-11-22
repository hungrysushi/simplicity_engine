#pragma once

#include <functional>

namespace simplicity {

enum class GlobalEventsError {
        kSuccess,
        kUnregistered,
};

enum class Event {
        // keyboard events
        kWKeyPress,
        kAKeyPress,
        kSKeyPress,
        kDKeyPress,
        kEscKeyPress,
};

typedef std::function<void()> Callback;

}  // namespace simplicity
