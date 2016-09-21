
#include "ValidationLayer.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <algorithm>


using std::begin;
using std::end;
using std::cbegin;
using std::cend;
using std::string;

auto as_sorted_names(
    const std::vector<const char*>& validation_layers)
{
  std::vector<string> ret{};
  for (auto const& desired_layer : validation_layers) {
    ret.emplace_back(desired_layer);
  }
  std::sort(begin(ret), end(ret));
  return ret;
}

auto as_sorted_names(
    const std::vector<VkLayerProperties>& available_layers)
{
  std::vector<string> ret{};
  for (auto const& available_layer : available_layers) {
    ret.emplace_back(available_layer.layerName);
  }
  std::sort(begin(ret), end(ret));
  return ret;
}

bool checkValidationLayerSupport()
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> available_layers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, available_layers.data());

  auto available_layers_names = as_sorted_names(available_layers);
  auto validation_layers      = as_sorted_names(kValidationLayers);

  // clang-format off
  return std::includes(
      cbegin(available_layers_names), cend(available_layers_names),
      cbegin(validation_layers),      cend(validation_layers));
  // clang-format on
}

// vim:set et ts=2 sw=2 sts=2:

