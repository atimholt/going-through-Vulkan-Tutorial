#include "VulkanHandler.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

#define WHOLE(container) std::begin(container), std::end(container)
#define CWHOLE(container) std::cbegin(container), std::cend(container)

const std::vector<const char*> VulkanHandler::k_validation_layers{
    "VK_LAYER_KHRONOS_validation"};


VulkanHandler::VulkanHandler()
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
  if (k_enable_validation_layers && !checkValidationLayerSupport()) {
    throw std::runtime_error("validation layers requested, but not available!");
  }

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
  if (k_enable_validation_layers) {
    create_info.enabledLayerCount =
        static_cast<uint32_t>(k_validation_layers.size());
    create_info.ppEnabledLayerNames = k_validation_layers.data();
  }

  vk_instance_ = vk::createInstanceUnique(create_info);
}

bool VulkanHandler::checkValidationLayerSupport()
{
  using namespace std;

  set<string> available_layer_names{};
  for (const auto& layer_properties : vk::enumerateInstanceLayerProperties()) {
    available_layer_names.emplace(layer_properties.layerName);
  }

  set<string> validation_layers_sorted{};
  for (const auto& layer : VulkanHandler::k_validation_layers) {
    validation_layers_sorted.emplace(layer);
  }

  return includes(
      CWHOLE(available_layer_names), CWHOLE(validation_layers_sorted));
}

// vim:set et ts=2 sw=0 sts=0:

