#pragma once

#include <d3d11.h>
#include <expected>
#include <filesystem>
#include <string>
#include <variant>
#include <wrl/client.h>

namespace ccb {
namespace fs = std::filesystem;
using Microsoft::WRL::ComPtr;

class Shader {
public:
  [[nodiscard]] static std::expected<Shader, std::string>
  create_vertex(ComPtr<ID3D11Device> device, const fs::path &file_path, const std::string &entry_point);
  [[nodiscard]] static std::expected<Shader, std::string> create_pixel(const fs::path &file_path,
                                                                       const std::string &entry_point);

private:
  explicit Shader() noexcept;

  [[nodiscard]] static std::expected<ComPtr<ID3DBlob>, std::string> compile(const fs::path &file_path,
                                                                            const std::string &entry_point);

  ComPtr<ID3DBlob> m_bytecode;
  std::variant<ComPtr<ID3D11VertexShader>, ComPtr<ID3D11PixelShader>> m_shader;
};
} // namespace ccb