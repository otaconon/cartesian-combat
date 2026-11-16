#pragma once

#include <d3d11.h>
#include <dxgi1_3.h>
#include <expected>
#include <string>
#include <wrl/client.h>

namespace ccb {
using Microsoft::WRL::ComPtr;

class Renderer {
public:
  [[nodiscard]] static std::expected<Renderer, std::string> create(void *window_handle, uint32_t window_w, uint32_t window_h);

private:
  explicit Renderer() noexcept;

  ComPtr<IDXGIFactory2> m_factory{};
  ComPtr<ID3D11Device> m_device{};
  ComPtr<ID3D11DeviceContext> m_ctx{};
  ComPtr<IDXGISwapChain1> m_swapchain{};
  ComPtr<ID3D11RenderTargetView> m_render_target{};
};
} // namespace ccb