/// \file    main.cpp

#include "HelloTriangleApplication.hpp"
#include "VDeleter.hpp"

// waf-generated header
#include "config.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char* argv[])
{
#ifdef NDEBUG
  std::cout << "debugging off\n";
#else
  std::cout << "debugging on\n";
#endif

  int res{0};
#ifndef DOCTEST_CONFIG_DISABLE
  doctest::Context context(argc, argv);

  context.setOption("no-run", true);

  res = context.run();
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

  return EXIT_SUCCESS + res;
}

// vim:set et ts=2 sw=2 sts=2:

