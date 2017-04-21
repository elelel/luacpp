#pragma once

#include "../type_adapter.hpp"

namespace lua {
  template <typename T>
  struct type_adapter_boolean {
    typedef type_adapter_boolean<T> type;
    
    inline static bool type_matches(const lua::state_base& s, int idx) {
      return s.isboolean(idx);
    }

    inline static T get_unsafe(const lua::state_base& s, int idx) {
      return s.toboolean(idx);
    }
    
    inline static void push(const lua::state_base& s, T value) {
      return s.pushboolean(value);
    }

  };

  template <>
  struct type_adapter<bool> : public type_adapter_boolean<bool> {
  };

  template <>
  struct type_adapter<const bool> : public type_adapter_boolean<const bool> {
  };
}
