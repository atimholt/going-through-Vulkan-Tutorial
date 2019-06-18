
#include "HelloTriangleApplication.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>


// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct HelloTriangleApplication::WindowHandler
{
  GLFWwindow* window;

  WindowHandler() : window{nullptr}
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(HelloTriangleApplication::k_width,
            HelloTriangleApplication::k_height, "Vulkan", nullptr, nullptr);
  }

  ~WindowHandler()
  {
    glfwDestroyWindow(window);
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
  initVulkan();
  mainLoop();
}

void HelloTriangleApplication::initVulkan()
{
}

void HelloTriangleApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window_handler_->window)) {
    glfwPollEvents();
  }
}

// vim:set et ts=2 sw=0 sts=0:

