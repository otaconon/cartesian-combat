#include <SDL3/SDL_events.h>
#include <engine/error.h>
#include <engine/renderer.h>
#include <engine/shader.h>
#include <engine/window.h>
#include <print>

namespace fs = std::filesystem;

std::expected<void, std::string> run() {
  /*================================== WINDOW, RENDERER ==================================*/
  ASSIGN_OR_RETURN(auto window, ccb::Window::create(900, 900));
  auto [window_w, window_h] = window.get_dim();
  ASSIGN_OR_RETURN(auto renderer, ccb::Renderer::create(window.get_native_handle(), window_w, window_h));

  /*================================== SHADERS ==================================*/
  ASSIGN_OR_RETURN(auto vs,
                   ccb::Shader::create_vertex(renderer.get_device(),
                                              fs::path("C:/dev/games/cartesian-combat/shaders/vertex.hlsl"), "Main"));

  /*================================== MAIN LOOP ==================================*/
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
    renderer.render();
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
