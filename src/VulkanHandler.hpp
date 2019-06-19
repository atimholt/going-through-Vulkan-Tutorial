#ifndef VULKAN_HANDLER_HPP_IS_INCLUDED
#define VULKAN_HANDLER_HPP_IS_INCLUDED

#include <vulkan/vulkan.hpp>

struct VulkanHandler
{
  static const std::vector<const char*> k_validation_layers;
#ifdef NDEBUG
  static const bool k_enable_validation_layers = false;
#else
  static const bool k_enable_validation_layers = true;
#endif

  vk::UniqueInstance vk_instance_;

  VulkanHandler();

  void createInstance();

  bool checkValidationLayerSupport();
};

#endif // !VULKAN_HANDLER_HPP_IS_INCLUDED

// vim:set et ts=2 sw=0 sts=0:

