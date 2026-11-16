#include <engine/window.h>
#include <engine/renderer.h>
#include <print>

int main() {
  auto window = ccb::Window::create(900, 900);
  if (!window) {
    std::println(stderr, "{}", window.error());
    return 1;
  }
  
  auto renderer = ccb::Renderer::create(window->get_native_handle(), window->get_dim().w, window->get_dim().h);
  if (!renderer) {
    std::println(stderr, "{}", renderer.error());
    return 1;
  }

  std::println("Hello world");
}
