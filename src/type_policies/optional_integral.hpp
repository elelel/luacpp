#pragma once

#include "integral.hpp"
#include "optional.hpp"

namespace lua {
  template <>
  struct type_policy<std::optional<int>> : public detail::optional<int> {
  };

  template <>
  struct type_policy<const std::optional<int>> : public detail::optional<const int> {
  };

  template <>
  struct type_policy<const std::optional<int>&> : public detail::optional<const int&> {
  };

  template <>
  struct type_policy<std::optional<unsigned int>> : public detail::optional<unsigned int> {
  };

  template <>
  struct type_policy<const std::optional<unsigned int>> : public detail::optional<const unsigned int> {
  };

  template <>
  struct type_policy<const std::optional<unsigned int>&> : public detail::optional<const unsigned int&> {
  };
}
