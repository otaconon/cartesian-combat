#include <SDL3/SDL_events.h>
#include <engine/renderer.h>
#include <engine/window.h>
#include <print>

int main() {
  auto window = ccb::Window::create(900, 900);
  if (!window) {
    std::println(stderr, "{}", window.error());
    return 1;
  }
  
  auto [window_w, window_h] = window->get_dim();
  auto result = ccb::Renderer::create(window->get_native_handle(), window_w, window_h);
  if (!result) {
    std::println(stderr, "{}", result.error());
    return 1;
  }
  ccb::Renderer renderer = std::move(*result);
  
  std::println("Hello world");

  bool should_quit = false;
  while (!should_quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EventType::SDL_EVENT_QUIT:
        should_quit = true;
        break;
      case SDL_EventType::SDL_EVENT_WINDOW_RESIZED:
        auto [w, h] = window->get_dim();
				result = renderer.on_resize(static_cast<uint32_t>(w), static_cast<uint32_t>(h));
        if (!result) {
          std::println(stderr, "{}", result.error(0);
          return 1;
        }
      }
    }
  }
}
