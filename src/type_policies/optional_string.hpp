#pragma once

#include "string.hpp"
#include "optional.hpp"

namespace lua {
  template <>
  struct type_policy<std::optional<char*>> : public detail::optional<char*> {};
  template <>
  struct type_policy<std::optional<const char*>> : public detail::optional<const char*> {};
  template <>
  struct type_policy<std::optional<std::string>> : public detail::optional<std::string> {};
  template <>
  struct type_policy<std::optional<const std::string>> : public detail::optional<const std::string> {};
  template <>
  struct type_policy<const std::optional<const std::string>&> : public detail::optional<const std::string> {};

  template <size_t N>
  struct type_policy<std::optional<char[N]>> : public detail::optional<char*> {};
  template <size_t N>
  struct type_policy<std::optional<const char[N]>> : public detail::optional<const char*> {};
  template <size_t N>
  struct type_policy<const std::optional<char[N]>&> : public detail::optional<const char*> {};
}
