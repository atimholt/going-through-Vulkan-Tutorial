#include "ValidationLayerHelpers.hpp"

// Includes
//----------

//   3rd Party Libraries
//  ---------------------

#include <vulkan/vulkan.hpp>

#include "doctest.h"

//   Experimental Standard Library
//  -------------------------------

// range-v3 removes the default template parameters for std containers.
// I know, right?
#define RANGES_NO_STD_FORWARD_DECLARATIONS
#include <range/v3/all.hpp>

//   Standard Libary
//  -----------------

#include <string>
#include <vector>

// Global Using Statements/Namespace Aliases
//-------------------------------------------

using ranges::view::all;
namespace view = ranges::view;

using std::string;
using std::vector;

//-------------------------------------------
// Global Using Statements/Namespace Aliases

namespace v_layer {

// Constants
//-----------

// const vector<const char*> k_layers{...};
TEST_CASE("k_layers is sorted")
{
  // strings -> less code to compare elements.
  // Same name makes doctest CHECK output more readable.
  vector<string> v_layer__k_layers{all(v_layer::k_layers)};

  CHECK(ranges::is_sorted(v_layer__k_layers));
}

// Functions
//-----------

bool checkSupport()
{
  // set<string> is sorted, and its elements are trivially comparable.
  std::set<string> available_layer_names{};
  for (const auto& layer_properties : vk::enumerateInstanceLayerProperties()) {
    available_layer_names.emplace(layer_properties.layerName);
  }

  return ranges::includes(available_layer_names, v_layer::k_layers);
}
TEST_CASE("v_layer::checkSupport()")
{
  CHECK(checkSupport());
}

//-----------
// Functions

} // namespace v_layer

// vim:set et ts=2 sw=0 sts=0:

