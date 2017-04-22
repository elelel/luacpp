#pragma once

#include "../type_adapter.hpp"

namespace lua {
  template <typename T>
  struct type_adapter_numeric {
    typedef type_adapter_numeric<T> type;
    
    inline static bool type_matches(const lua::state_base& s, int idx) {
      return s.isnumber(idx);
    }

    inline static T get_unsafe(const lua::state_base& s, int idx) {
      return T(s.tonumber(idx));
    }
    
    inline static void push(const lua::state_base& s, T value) {
      s.pushnumber((T)value);
    }

  };

  template <>
  struct type_adapter<int> : public type_adapter_numeric<int> {
  };

  template <>
  struct type_adapter<const int> : public type_adapter_numeric<const int> {
  };

  template <>
  struct type_adapter<double> : public type_adapter_numeric<double> {
  };

  template <>
  struct type_adapter<const double> : public type_adapter_numeric<const double> {
  };

}
