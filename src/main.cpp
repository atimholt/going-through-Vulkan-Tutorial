/// \file    main.cpp

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <cstdlib>
#include <ostream>

int main(int argc, char* argv[])
{
  ////////////////////////////// Testing Stuff ////
  doctest::Context context;                      //
  context.setOption("no-breaks", true);          //
  context.setOption("no-run", true);             //
  context.applyCommandLine(argc, argv);          //
  auto test_results = context.run();             //
  if (context.shouldExit()) return test_results; //
  /////////////////////////////////////////////////

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window =
      glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

  uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

  std::cout << extension_count << " extensions supported" << std::endl;

  glm::mat4 matrix;
  glm::vec4 vec;
  auto test = matrix * vec;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();

  return EXIT_SUCCESS + test_results;
}

// vim:set et ts=2 sw=2 sts=2:

