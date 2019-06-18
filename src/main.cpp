/// \file    main.cpp

#include "HelloTriangleApplication.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) // NOLINT(bugprone-exception-escape)
{
  ////////////////////////////// Testing Stuff ////
  doctest::Context context;                      //
  context.setOption("no-breaks", true);          //
  context.setOption("no-run", true);             //
  context.applyCommandLine(argc, argv);          //
  auto test_results = context.run();             //
  if (context.shouldExit()) return test_results; //
  /////////////////////////////////////////////////

  HelloTriangleApplication app;

  try {
    app.run();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS + test_results;
}

// vim:set et ts=2 sw=0 sts=0:

