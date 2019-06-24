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

using std::string;
using std::vector;

using std::begin;
using std::end;
#define WHOLE(container) begin(container), end(container)

using std::cbegin;
using std::cend;
#define CWHOLE(container) cbegin(container), cend(container)

using doctest::test_suite;

// Unit test forward setup
//-------------------------

struct StubGLFWRAII
{
  // clang-format off
  StubGLFWRAII() { glfwInit(); }
  ~StubGLFWRAII() { glfwTerminate(); }
  // clang-format on
};

TEST_SUITE("requires glfwInit")
{
  // Note: GLFW is all global scope. Calling GLFW functions just requires
  // glfwInit() to be called somewhere.
  // That is, this object is not actually used anywhere.
  StubGLFWRAII glfw_raii{};
}

// Constants
//-----------

const vector<const char*> VulkanHandler::k_validation_layers{
    "VK_LAYER_KHRONOS_validation"};
TEST_CASE("k_validation_layers is sorted")
{
  // makes doctest CHECK output more readable
  using std::is_sorted;

  // strings -> less code to compare elements.
  // Same name makes doctest CHECK output more readable.
  vector<string> k_validation_layers(WHOLE(VulkanHandler::k_validation_layers));

  CHECK(is_sorted(CWHOLE(k_validation_layers)));
}

// Method Definitions
//--------------------

vk::UniqueInstance createInstance();
// is used by:
VulkanHandler::VulkanHandler() : vk_instance_{createInstance()}
{
}
TEST_CASE("VulkanHandler()" * test_suite("requires glfwInit"))
{ //                          ^ works in different suites. How do suites work?
  VulkanHandler a_vulkan_handler{};
  CHECK(a_vulkan_handler.vk_instance_);
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
TEST_CASE("createInstance()" * test_suite("requires glfwInit"))
{
  CHECK(createInstance());
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
TEST_CASE("checkValidationLayerSupport()")
{
  CHECK(checkValidationLayerSupport());
}

vector<const char*> getExtensions()
{
  uint32_t glfw_extension_count{};
  const char** glfw_extensions =
      glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  if (0 == glfw_extension_count) {
    throw std::runtime_error(
        "GLFW extensions required count is 0! Has glfwInit() been called?");
  }

  vector<const char*> extensions(glfw_extension_count);
  std::copy_n(glfw_extensions, glfw_extension_count, begin(extensions));

  return extensions;
}
TEST_CASE("getExtensions()" * test_suite("requires glfwInit"))
{
  CHECK(getExtensions().size() > 0);
}

// vim:set et ts=2 sw=0 sts=0:

