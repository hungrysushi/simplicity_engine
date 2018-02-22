#include "simplicity/resource_manager.h"

#include <algorithm>

namespace simplicity {

ResourceManager::ResourceManager() {
        // TODO
}

ResourceManager::~ResourceManager() {
        // clean up all allocated resources and free them
        for (auto it = resources_.begin(); it != resources_.end(); it++) {
                if (it->deallocate == nullptr) {
                        delete (uint8_t*) it->buffer;
                } else {
                        it->deallocate();
                }
        }

        // everything else should be cleared up automatically
}

ResourceError ResourceManager::Allocate(VoidPtr& target, const uint32_t size, const bool use_pool) {

        if (use_pool) {

                // allocate from pool
                target = pool_->allocate(size);

                // track the resource
                resources_.emplace_back(
                                target,
                                size,
                                [&]() {
                                        pool_->deallocate(target);
                                }
                );
        } else {

                // allocate on heap
                target = (VoidPtr) new uint8_t[size];

                resources_.emplace_back(target, size);
        }
}

ResourceError ResourceManager::Save(const VoidPtr& target, const uint32_t size, std::function<void()> deallocator) {
        
        resources_.emplace_back(target, size, deallocator);
}

ResourceError ResourceManager::Deallocate(VoidPtr& target) {
        // find the pointer and delete it
        auto resource = std::find_if(resources_.begin(), resources_.end(), [&](const ResourcePtr& item) {
                        return item.buffer == target;
                        });

        if (resource == resources_.end()) {
                // the item being deallocated was not found
                return ResourceError::kTargetNotFound;
        }

        if (resource->deallocate == nullptr) {

                // this was allocated on the heap
                // TODO does this need to be cast to uint32_t first?
                delete[] resource->buffer;
        } else {

                // buffer was either allocated outside, or from the pool.
                // Either way, we have a closure to handle it
                resource->deallocate();
        }

        resources_.erase(resource);

        // TODO find if it exists in the map and remove it

        return ResourceError::kSuccess;
}

ResourceError ResourceManager::ReservePool(const uint32_t size) {
        
        // if a previous pool exists, clear it
        if (pool_ != nullptr) {
                delete pool_;
        }

        // reserve an amount of memory in the pool
        pool_ = new MemoryPool(size);

        return ResourceError::kSuccess;
}

ResourceError ResourceManager::GetNamed(std::string key, VoidPtr& target) {
        auto value = named_resources_.find(key);

        if (value == named_resources_.end()) {

                // the key doesn't exist
                return ResourceError::kKeyNotFound;
        } else {

                target = value->second;
                return ResourceError::kSuccess;
        }
}

ResourceError ResourceManager::SetNamed(std::string key, VoidPtr& target) {
        named_resources_[key] = target;
}

uint32_t ResourceManager::Size() {

        // TODO
        return 0;
}

}  // namespace simplicity
