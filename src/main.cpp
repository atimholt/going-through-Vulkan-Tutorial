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
#include <string>

using namespace std::literals::string_literals;

int main(int argc, char* argv[])
{
  int test_result{0};
#ifndef DOCTEST_CONFIG_DISABLE
  doctest::Context context;

  context.setOption("no-run", true);

  context.applyCommandLine(argc, argv);

  auto begin_argv = argv + 1;
  auto end_argv   = argv + argc;
  if (end_argv != std::find(begin_argv, end_argv, "--test"s)) {
    context.setOption("no-run", false);
    context.setOption("exit", true);
  }

  test_result = context.run();
  if (context.shouldExit()) return test_result;
#endif
  HelloTriangleApplication app;

  try {
    app.run();
  }
  catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS + test_result;
}

// vim:set et ts=2 sw=2 sts=2:

