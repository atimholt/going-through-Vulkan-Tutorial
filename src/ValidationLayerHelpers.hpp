#ifndef VALIDATION_LAYER_HELPERS_HPP_IS_INCLUDED
#define VALIDATION_LAYER_HELPERS_HPP_IS_INCLUDED

// Perhaps don't include in a header (though it's not like I'm not going to
// use std::vector elsewhere)
#include <vector>

namespace v_layer {

const std::vector<const char*> k_layers{"VK_LAYER_KHRONOS_validation"};

bool checkSupport();

#ifdef NDEBUG
static const bool k_enable = false;
#else
static const bool k_enable = true;
#endif

} // namespace v_layer

#endif // !VALIDATION_LAYER_HELPERS_HPP_IS_INCLUDED

// vim:set et ts=2 sw=0 sts=0:

