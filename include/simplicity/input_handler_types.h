#pragma once

#include <functional>

namespace simplicity {

enum class InputHandlerError {
        kSuccess,
        kGenericInputError,
};

// using raw function pointers
// this is probably dangerous. Must be a better way to do this
// TODO figure out
/* typedef void (*InputCallback)(); */
typedef std::function<void()> InputCallback;

// pointer to the caller
typedef void* Context;

struct Callback {
        Context context_;  // pointer to the object that the callback is from
        InputCallback function_;  // callback function

        Callback() {

        }

        Callback(Context context, InputCallback function) {
                context_ = context;
                function = function;
        }
};

enum class Event {
        W_KEY_PRESS,
        A_KEY_PRESS,
        S_KEY_PRESS,
        D_KEY_PRESS,
        ESC_KEY_PRESS,
};

}  // namespace simplicity
