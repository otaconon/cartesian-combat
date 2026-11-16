#pragma once

#include <expected>
#include <memory>
#include <string>

struct SDL_Window;

struct WindowDim {
  uint32_t w = 0, h = 0;
};

namespace ccb {
class Window {
public:
  [[nodiscard]] static std::expected<Window, std::string> create(int w, int h);
  [[nodiscard]] void *get_native_handle();
  [[nodiscard]] WindowDim get_dim();

private:
  struct Deleter {
    void operator()(SDL_Window *win) const noexcept;
  };

  explicit Window(SDL_Window *handle) noexcept;

  std::unique_ptr<SDL_Window, Deleter> m_handle{};
  WindowDim m_dim{};
};
} // namespace ccb
