#include "renderer.h"

#include <format>

#define DX11_CHECK(result, msg)                                                                                        \
  do {                                                                                                                 \
    if (FAILED(result)) {                                                                                              \
      return std::unexpected(std::format("DX11 error {:#x} ({}, {}): {}", result, __FILE__, __LINE__, msg));           \
    }                                                                                                                  \
  } while (0)

namespace ccb {
Renderer::Renderer() noexcept {}

std::expected<Renderer, std::string> Renderer::create(void *native_win_handle, uint32_t window_w, uint32_t window_h) {
  Renderer r{};
  HWND hwnd = static_cast<HWND>(native_win_handle);
  if (!hwnd) {
    return std::unexpected("Failed to convert windown handle into hwnd");
  }

  DX11_CHECK((CreateDXGIFactory1(IID_PPV_ARGS(&r.m_factory))), "Failed to create dxgi factory");
  r.m_factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

  constexpr D3D_FEATURE_LEVEL device_feature_level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
  DX11_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &device_feature_level, 1,
                               D3D11_SDK_VERSION, &r.m_device, nullptr, &r.m_ctx),
             "Failed to create dx11 device");

  DXGI_SWAP_CHAIN_DESC1 swapchain_desc{.Width = window_w,
                                       .Height = window_h,
                                       .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
                                       .SampleDesc{.Count = 1, .Quality = 0},
                                       .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
                                       .BufferCount = 2,
                                       .SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD};

  DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc{.Windowed = true};
  DX11_CHECK(r.m_factory->CreateSwapChainForHwnd(r.m_device.Get(), hwnd, &swapchain_desc, &fullscreen_desc, nullptr,
                                                 &r.m_swapchain),
             "Failed to create dxgi swapchain");
  
  ComPtr<ID3D11Texture2D> back_buffer{};
  DX11_CHECK(r.m_swapchain->GetBuffer(0, IID_PPV_ARGS(&back_buffer)), "Failed to get back buffer from swapchain");
  DX11_CHECK(r.m_device->CreateRenderTargetView(back_buffer.Get(), nullptr, &r.m_render_target),
             "Failed to create render target view");
  return r;
}
} // namespace ccb
