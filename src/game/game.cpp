#include <SDL3/SDL_events.h>
#include <engine/renderer.h>
#include <engine/window.h>
#include <engine/error.h>
#include <print>

std::expected<void, std::string> run() {
  ASSIGN_OR_RETURN(auto window, ccb::Window::create(900, 900));

  auto [window_w, window_h] = window.get_dim();
  ASSIGN_OR_RETURN(auto renderer, ccb::Renderer::create(window.get_native_handle(), window_w, window_h));

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
        auto [w, h] = window.get_dim();
        RETURN_IF_ERROR(renderer.on_resize(static_cast<uint32_t>(w), static_cast<uint32_t>(h)));
      }
    }
  }
  return {};
}

int main() {
  if (auto res = run(); !res) {
    std::println(stderr, "{}", res.error());
    return 1;
  }
  return 0;
}
