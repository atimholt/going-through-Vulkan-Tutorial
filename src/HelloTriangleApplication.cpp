
#include "HelloTriangleApplication.hpp"

const int kWidth  = 800;
const int kHeight = 600;

void HelloTriangleApplication::run()
{
  initWindow();
  initVulkan();
  mainLoop();
}

void HelloTriangleApplication::initWindow()
{
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(kWidth, kHeight, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApplication::initVulkan()
{
  createInstance();
}

void HelloTriangleApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
  }
}

void HelloTriangleApplication::createInstance()
{
  // optional ------------------------------------
  VkApplicationInfo appInfo  = {};
  appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName   = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName        = "No Engine";
  appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion         = VK_API_VERSION_1_0;


  // required ------------------------------------
  VkInstanceCreateInfo createInfo = {};
  createInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo     = &appInfo;

  // akin to argc & argv
  unsigned int glfwExtensionCount = 0;
  const char** glfwExtensions;

  // fill them out
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  createInfo.enabledExtensionCount   = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;

  createInfo.enabledLayerCount = 0;
  // ---------------------------------------------

  VkResult result = vkCreateInstance(&createInfo, nullptr, instance_.replace());

  if (vkCreateInstance(&createInfo, nullptr, instance_.replace())
      != VK_SUCCESS) {
    throw std::runtime_error("failed to create instance!");
  }
}


// vim:set et ts=2 sw=2 sts=2:

