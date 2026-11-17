#pragma once

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
