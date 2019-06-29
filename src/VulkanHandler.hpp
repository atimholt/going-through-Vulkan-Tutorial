#ifndef VULKAN_HANDLER_HPP_IS_INCLUDED
#define VULKAN_HANDLER_HPP_IS_INCLUDED

#include <vulkan/vulkan.hpp>

struct VulkanHandler
{
  vk::UniqueInstance vk_instance_;

  VulkanHandler();
};

#endif // !VULKAN_HANDLER_HPP_IS_INCLUDED

// vim:set et ts=2 sw=0 sts=0:

