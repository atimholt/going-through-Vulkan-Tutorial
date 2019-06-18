
#include <memory>

class HelloTriangleApplication
{
 public:
  static const int k_width  = 800;
  static const int k_height = 600;

  HelloTriangleApplication();
  ~HelloTriangleApplication();

  void run();

 private:
  struct WindowHandler;
  std::unique_ptr<WindowHandler> window_handler_;

  void initVulkan();
  void mainLoop();
};

// vim:set et ts=2 sw=0 sts=0:

