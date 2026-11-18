#pragma once

#include <expected>
#include <format>

#define TRY_CONCAT_IMPL(x, y) x##y
#define TRY_CONCAT(x, y) TRY_CONCAT_IMPL(x, y)

#define RETURN_IF_ERROR_IMPL(tmp, ...)                                                                                 \
  do {                                                                                                                 \
    if (auto tmp = (__VA_ARGS__); !tmp) {                                                                              \
      return std::unexpected(std::move(tmp).error());                                                                  \
    }                                                                                                                  \
  } while (false)

#define RETURN_IF_ERROR(...) RETURN_IF_ERROR_IMPL(TRY_CONCAT(res_, __COUNTER__), __VA_ARGS__)

#define ASSIGN_OR_RETURN_IMPL(tmp, lhs, ...)                                                                           \
  auto tmp = (__VA_ARGS__);                                                                                            \
  if (!tmp) {                                                                                                          \
    return std::unexpected(std::move(tmp).error());                                                                    \
  }                                                                                                                    \
  lhs = *std::move(tmp)

#define ASSIGN_OR_RETURN(lhs, ...) ASSIGN_OR_RETURN_IMPL(TRY_CONCAT(res_, __COUNTER__), lhs, __VA_ARGS__)

#define DX_CHECK(result, msg)                                                                                          \
  do {                                                                                                                 \
    const HRESULT _dx_hr = (result);                                                                                   \
    if (FAILED(_dx_hr)) {                                                                                              \
      return std::unexpected(                                                                                          \
          std::format("DX11 error {:#x} ({}, {}): {}", static_cast<unsigned>(_dx_hr), __FILE__, __LINE__, msg));       \
    }                                                                                                                  \
  } while (0)
