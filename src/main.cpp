/// \file    main.cpp

#include "VDeleter.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

const int kWidth  = 800;
const int kHeight = 600;

class HelloTriangleApplication
{
 public:
  void run()
  {
    initWindow();
    initVulkan();
    mainLoop();
  }

 private:
  GLFWwindow* window;

  void initWindow()
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(kWidth, kHeight, "Vulkan", nullptr, nullptr);
  }

  void initVulkan()
  {
  }

  void mainLoop()
  {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }
};

int main(int argc, char* argv[])
{
#ifndef DOCTEST_CONFIG_DISABLE
  doctest::Context context(argc, argv);

  context.setOption("no-run", true);

  int res = context.run();
  if (context.shouldExit()) return res;
#endif
  HelloTriangleApplication app;

  try {
    app.run();
  }
  catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
