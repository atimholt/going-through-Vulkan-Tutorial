
#include "HelloTriangleApplication.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <algorithm>

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct HelloTriangleApplication::WindowHandler
{
  GLFWwindow* window;

  WindowHandler() : window{nullptr}
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(k_width, k_height, "Vulkan", nullptr, nullptr);
  }

  ~WindowHandler()
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
};

HelloTriangleApplication::HelloTriangleApplication()
    : window_handler_{new WindowHandler{}}, vk_instance_{nullptr}
{
}

HelloTriangleApplication::~HelloTriangleApplication() = default;

void HelloTriangleApplication::run()
{
  initVulkan();
  mainLoop();
}

void HelloTriangleApplication::initVulkan()
{
  createInstance();
}

void HelloTriangleApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window_handler_->window)) {
    glfwPollEvents();
  }
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

void HelloTriangleApplication::createInstance()
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

