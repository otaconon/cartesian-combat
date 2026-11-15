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

std::expected<Renderer, std::string> Renderer::create() {
  Renderer r{};

  DX11_CHECK((CreateDXGIFactory1(IID_PPV_ARGS(&r.m_factory))), "Unable to create dxgi factory");

  constexpr D3D_FEATURE_LEVEL device_feature_level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
  DX11_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &device_feature_level, 1,
                               D3D11_SDK_VERSION, &r.m_device, nullptr, &r.m_ctx),
             "Unable to create dx11 device");

  return r;
}
} // namespace ccb
