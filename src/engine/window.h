#pragma once

#include <SDL3/SDL.h>
#include <expected>
#include <string>
#include <memory>

namespace ccb {
class Window {
public:
  static std::expected<Window, std::string> create(int w, int h);

private:
  struct Deleter {
    void operator()(SDL_Window *win) const noexcept { SDL_DestroyWindow(win); }
  };

  explicit Window(SDL_Window *handle) noexcept;

  std::unique_ptr<SDL_Window, Deleter> m_handle;
};
} // namespace ccb
