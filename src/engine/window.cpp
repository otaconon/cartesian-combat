#include "window.h"
#include <print>

#define SDL_CHECK(ok)                                                          \
  do {                                                                         \
    if (!(ok)) {                                                               \
      std::println(stderr, "SDL error ({}, {}): {}", __FILE__, __LINE__,       \
                   SDL_GetError());                                            \
    }                                                                          \
  } while (0)

namespace ccb {
Window::Window(SDL_Window *handle) noexcept : m_handle(handle) {}

std::expected<Window, std::string> Window::create(int w, int h) {
  SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window *handle;
  SDL_CHECK(handle = SDL_CreateWindow("Cartesian Combat", w, h, SDL_WINDOW_RESIZABLE));

  return Window(handle);
}
} // namespace ccb
