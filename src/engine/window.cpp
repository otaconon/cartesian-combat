#include "window.h"
#include <SDL3/SDL.h>
#include <print>

#define SDL_CHECK(result)                                                                                              \
  do {                                                                                                                 \
    if (!(result)) {                                                                                                   \
      return std::unexpected(std::format("SDL error ({}, {}): {}", __FILE__, __LINE__, SDL_GetError()));               \
    }                                                                                                                  \
  } while (0)

namespace ccb {
Window::Window(SDL_Window *handle) noexcept : m_handle(handle) {}

std::expected<Window, std::string> Window::create(int w, int h) {
  SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window *handle;
  SDL_CHECK(handle = SDL_CreateWindow("Cartesian Combat", w, h, SDL_WINDOW_RESIZABLE));

  return Window(handle);
}

void Window::Deleter::operator()(SDL_Window *w) const noexcept { SDL_DestroyWindow(w); }
} // namespace ccb
