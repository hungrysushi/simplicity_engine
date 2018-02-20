#pragma once

#include <functional>

namespace simplicity {

enum class ResourceError {
        kSuccess,
        kTargetNotFound,
        kKeyNotFound,
};

struct ResourcePtr {
        uint8_t* buffer = nullptr;
        uint32_t size = 0;
        std::function<void()> deallocate = nullptr;

        ResourcePtr(void* b, uint32_t s)
                : buffer((uint8_t*) b),
                  size(s) {
                // nothing else to do
        }

        ResourcePtr(void* b, uint32_t s, std::function<void()> d)
                : buffer((uint8_t*) b),
                  size(s),
                  deallocate(d) {
                // nothing else to do
        }
};

typedef void* VoidPtr;

}  // namespace simplicity
