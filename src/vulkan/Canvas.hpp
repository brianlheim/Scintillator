#ifndef SRC_VULKAN_CANVAS_HPP_
#define SRC_VULKAN_CANVAS_HPP_

#include "vulkan/Vulkan.hpp"

#include <memory>
#include <vector>

namespace scin { namespace vk {

class Device;
class ImageSet;

/*! Contains the data and state required to render to a set of Vulkan Images.
 *
 * Can be provided to the Compositor as either an output target or an intermediate target for rendering.
 */
class Canvas {
public:
    Canvas(std::shared_ptr<Device> device);
    ~Canvas();

    /*! Makes a set of ImageViews, a Render Pass, and then a set of Framebuffers.
     *
     * \param images A pointer to an Images class.
     * \return true on success, false on failure.
     */
    bool create(std::shared_ptr<ImageSet> images);

    /*! Reclaims the Vukan resources associated with the Canvas.
     */
    void destroy();

    VkExtent2D extent() const { return m_extent; }
    size_t numberOfImages() { return m_numberOfImages; }
    uint32_t width() const { return m_extent.width; }
    uint32_t height() const { return m_extent.height; }
    VkRenderPass renderPass() { return m_renderPass; }
    VkFramebuffer framebuffer(size_t index) { return m_framebuffers[index]; }
    VkImage image(size_t index);

private:
    std::shared_ptr<Device> m_device;
    std::shared_ptr<ImageSet> m_images;
    VkExtent2D m_extent;
    size_t m_numberOfImages;
    std::vector<VkImageView> m_imageViews;
    VkRenderPass m_renderPass;
    std::vector<VkFramebuffer> m_framebuffers;
};

} // namespace vk

} // namespace scin

#endif // SRC_VULKAN_CANVAS_HPP_