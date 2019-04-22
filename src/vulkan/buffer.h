#ifndef SRC_VULKAN_BUFFER_H_
#define SRC_VULKAN_BUFFER_H_

#include "vulkan/scin_include_vulkan.h"

#include <memory>

namespace scin {

namespace vk {

class Device;

class Buffer {
   public:
    Buffer(std::shared_ptr<Device> device);

   private:
    std::shared_ptr<Device> device_;
    VkBuffer buffer_;
    VkDeviceMemory device_memory_;
};

}    // namespace vk

}    // namespace scin

#endif    // SRC_VULKAN_BUFFER_H_

