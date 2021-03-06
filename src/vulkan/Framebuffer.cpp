#include "vulkan/Framebuffer.hpp"

#include "comp/Canvas.hpp"
#include "vulkan/Device.hpp"
#include "vulkan/Image.hpp"

#include "spdlog/spdlog.h"

namespace scin { namespace vk {

Framebuffer::Framebuffer(std::shared_ptr<Device> device): m_device(device), m_canvas(new comp::Canvas(device)) {}

Framebuffer::~Framebuffer() { destroy(); }

bool Framebuffer::create(int width, int height, size_t numberOfImages) {
    for (auto i = 0; i < numberOfImages; ++i) {
        std::shared_ptr<FramebufferImage> image(new FramebufferImage(m_device));
        if (!image->create(width, height)) {
            spdlog::error("framebuffer failed to create images.");
            return false;
        }
        m_images.emplace_back(image);
    }

    if (!m_canvas->create(m_images)) {
        spdlog::error("framebuffer failed to create canvas.");
        return false;
    }

    return true;
}

void Framebuffer::destroy() {
    m_canvas->destroy();
    m_images.clear();
}

VkFormat Framebuffer::format() { return m_images[0]->format(); }
VkImage Framebuffer::image(size_t index) { return m_images[index]->get(); }

} // namespace vk

} // namespace scin
