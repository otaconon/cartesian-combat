#include "shader.h"
#include "error.h"

#include <d3dcompiler.h>

namespace ccb {
Shader::Shader() noexcept {}
std::expected<Shader, std::string> Shader::create_vertex(ComPtr<ID3D11Device> device, const fs::path &file_path,
                                                         const std::string &entry_point) {
  Shader shader;
  ASSIGN_OR_RETURN(shader.m_bytecode, Shader::compile(file_path, entry_point));
  DX_CHECK(device->CreateVertexShader(shader.m_bytecode->GetBufferPointer(), shader.m_bytecode->GetBufferSize(),
                                      nullptr, &shader.m_shader.emplace<ComPtr<ID3D11VertexShader>>()),
           "Failed to create vertex shader");
  return shader;
}
std::expected<Shader, std::string> Shader::create_pixel(const fs::path &file_path, const std::string &entry_point) {
  return std::unexpected("why call me?");
}

std::expected<ComPtr<ID3DBlob>, std::string> ccb::Shader::compile(const fs::path &file_path,
                                                                  const std::string &entry_point) {
  constexpr UINT compiler_flags = D3DCOMPILE_ENABLE_STRICTNESS;
  ComPtr<ID3DBlob> shader_bytecode{}, error_bytecode{};
  if (FAILED(D3DCompileFromFile(file_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry_point.c_str(),
                                "vs_5_0", compiler_flags, 0, &shader_bytecode, &error_bytecode))) {
    std::string error_msg = std::format("DX11 error: Failed to read shader from file {}\n", file_path.string());
    if (error_bytecode != nullptr) {
      error_msg += std::format("DX11 error: With message: {}\n", error_bytecode->GetBufferPointer());
    }
    return std::unexpected(error_msg);
  }

  return shader_bytecode;
}
} // namespace ccb
