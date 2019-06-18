#include "VulkanHandler.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <algorithm>
#include <vector>

void VulkanHandler::initVulkan()
{
  createInstance();
}

std::vector<const char*> getExtensions()
{
  uint32_t glfw_extension_count{};
  const char** glfw_extensions =
      glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  std::vector<const char*> extensions(glfw_extension_count);
  std::copy_n(glfw_extensions, glfw_extension_count, std::begin(extensions));

  return extensions;
}

void VulkanHandler::createInstance()
{
  vk::ApplicationInfo app_info{
      "Hello Triangle",         // pApplicationName
      VK_MAKE_VERSION(1, 0, 0), // application version
      "No Engine",              //
      VK_MAKE_VERSION(1, 0, 0), // engine version
      VK_API_VERSION_1_0        //
  };

  auto extensions = getExtensions();

  vk::InstanceCreateInfo create_info{{}, &app_info, 0, {},
      static_cast<uint32_t>(extensions.size()), extensions.data()};

  vk_instance_ = vk::createInstanceUnique(create_info);
}

// vim:set et ts=2 sw=0 sts=0:

