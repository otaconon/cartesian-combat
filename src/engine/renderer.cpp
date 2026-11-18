#include "renderer.h"

#include "error.h"
#include <format>


namespace ccb {
Renderer::Renderer() noexcept {}

std::expected<void, std::string> Renderer::init_render_target() {
  ComPtr<ID3D11Texture2D> back_buffer{};
  DX_CHECK(m_swapchain->GetBuffer(0, IID_PPV_ARGS(&back_buffer)), "Failed to get back buffer from swapchain");
  DX_CHECK(m_device->CreateRenderTargetView(back_buffer.Get(), nullptr, &m_render_target),
             "Failed to create render target view");
}

std::expected<Renderer, std::string> Renderer::create(void *native_win_handle, uint32_t width, uint32_t height) {
  Renderer r;
  r.m_width = width;
  r.m_height = height;

  HWND hwnd = static_cast<HWND>(native_win_handle);
  if (!hwnd) {
    return std::unexpected("Failed to convert windown handle into hwnd");
  }

  DX_CHECK((CreateDXGIFactory1(IID_PPV_ARGS(&r.m_factory))), "Failed to create dxgi factory");
  r.m_factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

  constexpr D3D_FEATURE_LEVEL device_feature_level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
  DX_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &device_feature_level, 1,
                               D3D11_SDK_VERSION, &r.m_device, nullptr, &r.m_ctx),
             "Failed to create dx11 device");

  DXGI_SWAP_CHAIN_DESC1 swapchain_desc{.Width = width,
                                       .Height = height,
                                       .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
                                       .SampleDesc{.Count = 1, .Quality = 0},
                                       .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
                                       .BufferCount = 2,
                                       .SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD};

  DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc{.Windowed = true};
  DX_CHECK(r.m_factory->CreateSwapChainForHwnd(r.m_device.Get(), hwnd, &swapchain_desc, &fullscreen_desc, nullptr,
                                                 &r.m_swapchain),
             "Failed to create dxgi swapchain");

  r.init_render_target();

  return r;
}
std::expected<void, std::string> Renderer::on_resize(uint32_t width, uint32_t height) {
  m_width = width;
  m_height = height;
  m_ctx->Flush();
  m_render_target.Reset();
  DX_CHECK(m_swapchain->ResizeBuffers(0, m_width, m_height, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 0),
             "Failed to resize swapchain buffers");
  RETURN_IF_ERROR((init_render_target()));
}
void Renderer::render() {
  D3D11_VIEWPORT viewport{.TopLeftX = 0,
                          .TopLeftY = 0,
                          .Width = static_cast<float>(m_width),
                          .Height = static_cast<float>(m_height),
                          .MinDepth = 0.0f,
                          .MaxDepth = 1.0f};
  constexpr float clear_color[] = {0.1f, 0.1f, 0.1f, 1.0f};
  m_ctx->ClearRenderTargetView(m_render_target.Get(), clear_color);
  m_ctx->RSSetViewports(1, &viewport);
  m_ctx->OMSetRenderTargets(1, m_render_target.GetAddressOf(), nullptr);
  m_swapchain->Present(1, 0);
}
ComPtr<ID3D11Device> Renderer::get_device() { 
  return m_device;
}
} // namespace ccb
