#pragma once

#include "floating.hpp"
#include "optional.hpp"

namespace lua {
  template <>
  struct type_policy<std::optional<double>> : public detail::optional<double> {
  };

  template <>
  struct type_policy<const std::optional<double>> : public detail::optional<const double> {
  };

  template <>
  struct type_policy<const std::optional<double>&> : public detail::optional<const double&> {
  };


  template <>
  struct type_policy<std::optional<float>> : public detail::optional<float> {
  };

  template <>
  struct type_policy<const std::optional<float>> : public detail::optional<const float> {
  };

  template <>
  struct type_policy<const std::optional<float>&> : public detail::optional<const float&> {
  };

  
}
