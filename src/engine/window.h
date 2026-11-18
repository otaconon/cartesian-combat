#pragma once

#include <expected>
#include <memory>
#include <string>
#include <utility>

struct SDL_Window;

namespace ccb {
class Window {
public:
  [[nodiscard]] static std::expected<Window, std::string> create(int w, int h);
  [[nodiscard]] void *get_native_handle(); // TODO: Change to get_hwnd
  [[nodiscard]] std::pair<int, int> get_dim();

private:
  struct Deleter {
    void operator()(SDL_Window *win) const noexcept;
  };

  explicit Window(SDL_Window *handle) noexcept;

  std::unique_ptr<SDL_Window, Deleter> m_handle{};
};
} // namespace ccb
