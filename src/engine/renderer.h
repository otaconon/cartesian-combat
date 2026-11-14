#pragma once

#include <d3d11.h>
#include <dxgi1_3.h>
#include <d3dcompiler.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace ccb {
class Renderer {
public:
  Renderer();
  ~Renderer();

private:
  ComPtr<IDXGIFactory2> m_factory{nullptr};
  ComPtr<ID3D11Device> m_device{nullptr};
  ComPtr<ID3D11DeviceContext> m_ctx{nullptr};
  ComPtr<IDXGISwapChain1> m_swapchain{nullptr};
  ComPtr<ID3D11RenderTargetView> m_render_target{nullptr};

};
} // namespace ccb