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

  auto renderer = ccb::Renderer::create(window->get_native_handle(), window->get_dim().w, window->get_dim().h);
  if (!renderer) {
    std::println(stderr, "{}", renderer.error());
    return 1;
  }
  
  std::println("Hello world");

  bool should_quit = false;
  while (!should_quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EventType::SDL_EVENT_QUIT:
        should_quit = true;
        break;
      }
    }
  }
}
