/// \file    main.cpp

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <vulkan/vulkan.h>

#include <functional>
#include <iostream>
#include <stdexcept>

class HelloTriangleApplication
{
 public:
  void run()
  {
    initVulkan();
    mainLoop();
  }

 private:
  void initVulkan()
  {
  }

  void mainLoop()
  {
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
