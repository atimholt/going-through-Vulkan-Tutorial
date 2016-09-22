#pragma once

#include "VDeleter.hpp"

// waf-generated header
#include "config.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class HelloTriangleApplication
{
 public:
  void run();

 private:
  GLFWwindow* window_;
  VDeleter<VkInstance> instance_{vkDestroyInstance};

  void initWindow();
  void initVulkan();

  void createInstance();

  void mainLoop();
};

// vim:set et ts=2 sw=2 sts=2:

