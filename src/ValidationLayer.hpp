
#pragma once

#include <vector>

const std::vector<const char*> kValidationLayers = {
    "VK_LAYER_LUNARG_standard_validation"};

bool checkValidationLayerSupport();

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// vim:set et ts=2 sw=2 sts=2:

