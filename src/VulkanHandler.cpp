#include "VulkanHandler.hpp"

// Includes
//----------
//   3rd Party Libraries
//  ---------------------

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "doctest.h"

//   Standard Libary
//  -----------------

#include <algorithm>
#include <set>
#include <string>
#include <vector>

// Weird crap (see README.md to see my justification)
//----------------------------------------------------

#define WHOLE(container) std::begin(container), std::end(container)
#define CWHOLE(container) std::cbegin(container), std::cend(container)
using namespace std;

// Constants
//-----------

const vector<const char*> VulkanHandler::k_validation_layers{
    "VK_LAYER_KHRONOS_validation"};
TEST_CASE("k_validation_layers is sorted")
{
  // Easier to compare.
  vector<string> k_validation_layers(
      CWHOLE(VulkanHandler::k_validation_layers));
  // Same name makes the assertion fail output more readable.
  CHECK(std::is_sorted(CWHOLE(k_validation_layers)));
}

// Method Definitions
//--------------------

vk::UniqueInstance createInstance();
// is used by:
VulkanHandler::VulkanHandler() : vk_instance_{createInstance()}
{
}

// Helpers
//---------

bool checkValidationLayerSupport();
vector<const char*> getExtensions();
// are used by:
vk::UniqueInstance createInstance()
{
  if (VulkanHandler::k_enable_validation_layers
      && !checkValidationLayerSupport()) {
    throw std::runtime_error("validation layers requested, but not available!");
  }

  vk::ApplicationInfo app_info{ //
      "Hello Triangle",         // pApplicationName
      VK_MAKE_VERSION(1, 0, 0), // application version
      "No Engine",              //
      VK_MAKE_VERSION(1, 0, 0), // engine version
      VK_API_VERSION_1_0};      //

  auto extensions = getExtensions();

  vk::InstanceCreateInfo create_info{{}, &app_info, 0, {},
      static_cast<uint32_t>(extensions.size()), extensions.data()};
  if (VulkanHandler::k_enable_validation_layers) {
    create_info.enabledLayerCount =
        static_cast<uint32_t>(VulkanHandler::k_validation_layers.size());
    create_info.ppEnabledLayerNames = VulkanHandler::k_validation_layers.data();
  }

  return vk::createInstanceUnique(create_info);
}

bool checkValidationLayerSupport()
{
  // set<string> is sorted, and its elements are trivially comparable.
  std::set<string> available_layer_names{};
  for (const auto& layer_properties : vk::enumerateInstanceLayerProperties()) {
    available_layer_names.emplace(layer_properties.layerName);
  }

  return std::includes(CWHOLE(available_layer_names),
      CWHOLE(VulkanHandler::k_validation_layers));
}

vector<const char*> getExtensions()
{
  uint32_t glfw_extension_count{};
  const char** glfw_extensions =
      glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  vector<const char*> extensions(glfw_extension_count);
  std::copy_n(glfw_extensions, glfw_extension_count, begin(extensions));

  return extensions;
}

// vim:set et ts=2 sw=0 sts=0:

