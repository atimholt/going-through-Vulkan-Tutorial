/// \file    main.cpp

#include <cstdlib>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char* argv[])
{
  ////////////////////////////// Testing Stuff ////
  doctest::Context context;                      //
  context.setOption("no-breaks", true);          //
  context.applyCommandLine(argc, argv);          //
  auto test_results = context.run();             //
  if (context.shouldExit()) return test_results; //
  /////////////////////////////////////////////////

  // My code here

  return EXIT_SUCCESS + test_results;
}

// vim:set et ts=2 sw=2 sts=2:

