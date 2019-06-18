
#include "HelloTriangleApplication.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct HelloTriangleApplication::WindowHandler
{
  GLFWwindow* window_;

  WindowHandler() : window_{nullptr}
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(k_width, k_height, "Vulkan", nullptr, nullptr);
  }

  ~WindowHandler()
  {
    glfwDestroyWindow(window_);
    glfwTerminate();
  }
};

HelloTriangleApplication::HelloTriangleApplication()
    : window_handler_{new WindowHandler{}}
{
}

HelloTriangleApplication::~HelloTriangleApplication() = default;

void HelloTriangleApplication::run()
{
  vk_handler_.initVulkan();
  mainLoop();
}

void HelloTriangleApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window_handler_->window_)) {
    glfwPollEvents();
  }
}

// vim:set et ts=2 sw=0 sts=0:

