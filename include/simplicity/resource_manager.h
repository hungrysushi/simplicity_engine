#pragma once

#include <map>
#include <string>
#include <vector>

#include "memory_pool.h"
#include "simplicity/types/resource_types.h"

namespace simplicity {

class ResourceManager {
public:
        ResourceManager();
        ~ResourceManager();

        ResourceError Allocate(VoidPtr& target, const uint32_t size, const bool use_pool = false);
        ResourceError Save(const VoidPtr& target, const uint32_t size, std::function<void()> deallocator);
        ResourceError Deallocate(VoidPtr& target);
        ResourceError ReservePool(uint32_t size);

        ResourceError GetNamed(std::string key, VoidPtr& target);
        ResourceError SetNamed(std::string key, VoidPtr& target);

        uint32_t Size();

        // a lookup table for multi-use resources
        std::map<std::string, VoidPtr> named_resources_;

        // store pointers to all resources for easy lookup
        std::vector<ResourcePtr> resources_;

        // memory pool for items that should ideally be together in memory
        MemoryPool *pool_ = nullptr;

};

}  // namespace simplicity
