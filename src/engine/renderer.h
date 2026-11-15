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
  [[nodiscard]] static std::expected<Renderer, std::string> create();

private:
  explicit Renderer() noexcept;

  ComPtr<IDXGIFactory2> m_factory{nullptr};
  ComPtr<ID3D11Device> m_device{nullptr};
  ComPtr<ID3D11DeviceContext> m_ctx{nullptr};
  ComPtr<IDXGISwapChain1> m_swapchain{nullptr};
  ComPtr<ID3D11RenderTargetView> m_render_target{nullptr};
};
} // namespace ccb