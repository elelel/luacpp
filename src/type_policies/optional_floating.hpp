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
  struct type_policy<std::optional<unsigned double>> : public detail::optional<unsigned double> {
  };

  template <>
  struct type_policy<const std::optional<unsigned double>> : public detail::optional<const unsigned double> {
  };

  template <>
  struct type_policy<const std::optional<unsigned double>&> : public detail::optional<const unsigned double&> {
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

  template <>
  struct type_policy<std::optional<unsigned float>> : public detail::optional<unsigned float> {
  };

  template <>
  struct type_policy<const std::optional<unsigned float>> : public detail::optional<const unsigned float> {
  };

  template <>
  struct type_policy<const std::optional<unsigned float>&> : public detail::optional<const unsigned float&> {
  };
  
}
