#include "VulkanHandler.hpp"

// Includes
//----------

//   My Includes
//  -------------

#include "ValidationLayerHelpers.hpp"

//   3rd Party Libraries
//  ---------------------

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "doctest.h"

//   Experimental Standard Library
//  -------------------------------

#include <range/v3/all.hpp>

//   Standard Libary
//  -----------------

#include <algorithm>
#include <set>
#include <string>
#include <vector>

// Global Using Statements/Namespace Aliases
//-------------------------------------------

using ranges::view::all;
namespace view = ranges::view;

using std::string;
using std::vector;

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

vector<const char*> getExtensions();
// is used by:
vk::UniqueInstance createInstance()
{
  if (v_layer::k_enable && !v_layer::checkSupport()) {
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

  if (v_layer::k_enable) {
    create_info.enabledLayerCount =
        static_cast<uint32_t>(v_layer::k_layers.size());
    create_info.ppEnabledLayerNames = v_layer::k_layers.data();
  }

  return vk::createInstanceUnique(create_info);
}
TEST_CASE("createInstance()" * test_suite("requires glfwInit"))
{
  CHECK(createInstance());
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

  vector<const char*> extensions{
      view::counted(glfw_extensions, glfw_extension_count)};

  return extensions;
}
TEST_CASE("getExtensions()" * test_suite("requires glfwInit"))
{
  CHECK(getExtensions().size() > 0);
}

// vim:set et ts=2 sw=0 sts=0:

