/// \file    main.cpp

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <vulkan/vulkan.h>

#include <functional>
#include <iostream>
#include <stdexcept>

template <typename T>
class VDeleter
{
 public:
  VDeleter() : VDeleter([](T, VkAllocationCallbacks*) {})
  {
  }

  VDeleter(std::function<void(T, VkAllocationCallbacks*)> deletef)
  {
    this->deleter = [=](T obj) { deletef(obj, nullptr); };
  }

  VDeleter(const VDeleter<VkInstance>& instance,
      std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
  {
    this->deleter = [&instance, deletef](
        T obj) { deletef(instance, obj, nullptr); };
  }

  VDeleter(const VDeleter<VkDevice>& device,
      std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
  {
    this->deleter = [&device, deletef](
        T obj) { deletef(device, obj, nullptr); };
  }

  ~VDeleter()
  {
    cleanup();
  }

  const T* operator&() const
  {
    return &object;
  }

  T* replace()
  {
    cleanup();
    return &object;
  }

  operator T() const
  {
    return object;
  }

  void operator=(T rhs)
  {
    cleanup();
    object = rhs;
  }

  template <typename V>
  bool operator==(V rhs)
  {
    return object == T(rhs);
  }

 private:
  T object{VK_NULL_HANDLE};
  std::function<void(T)> deleter;

  void cleanup()
  {
    if (object != VK_NULL_HANDLE) {
      deleter(object);
    }
    object = VK_NULL_HANDLE;
  }
};

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
