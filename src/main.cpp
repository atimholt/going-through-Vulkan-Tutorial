/// \file    main.cpp

#include "HelloTriangleApplication.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <cstdlib>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  using namespace std;
  /////////////////////////////////////////////////////////////// Testing Stuff

  vector<string> args(argv, argv + argc);
  sort(begin(args), end(args));
  if (std::binary_search(cbegin(args), cend(args), "--do-nothing")) {
    return EXIT_SUCCESS;
  }
  if (std::binary_search(cbegin(args), cend(args), "--run-as-tests")) {
    doctest::Context context;
    context.setOption("no-breaks", true);
    context.applyCommandLine(argc, argv);
    context.setOption("exit", true);
    context.setOption("no-run", false);
    auto test_results = context.run();
    if (context.shouldExit()) return test_results;
    return EXIT_SUCCESS + test_results;
  }
  /////////////////////////////////////////////////////////////////////////////

  HelloTriangleApplication app;

  try {
    app.run();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

// vim:set et ts=2 sw=0 sts=0:

