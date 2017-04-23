#pragma once

namespace lua {
  namespace detail {
    template <typename T>
    struct floating {
      typedef T write_type;
      typedef T read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isnumber(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return s.tonumber(idx);
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        f(s, idx);
      }

      inline static void set(::lua::state s, int idx, T value) {
        s.pushnumber(write_type(value));
        if (idx != 0) s.replace(idx);
      }
    };
  
  }
  
  template <>
  struct type_policy<double> : public detail::floating<double> {
  };

  template <>
  struct type_policy<const double> : public detail::floating<const double> {
  };
  
  template <>
  struct type_policy<float> : public detail::floating<float> {
  };

  template <>
  struct type_policy<const float> : public detail::floating<const float> {
  };
  
}

