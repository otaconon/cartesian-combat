#pragma once

#include <expected>
#include <string>
#include <memory>

struct SDL_Window;

namespace ccb {
class Window {
public:
  [[nodiscard]] static std::expected<Window, std::string> create(int w, int h);

private:
  struct Deleter {
    void operator()(SDL_Window *win) const noexcept;
  };

  explicit Window(SDL_Window *handle) noexcept;

  std::unique_ptr<SDL_Window, Deleter> m_handle;
};
} // namespace ccb
