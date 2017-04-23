#pragma once

namespace lua {
  namespace detail {
    template <typename T>
    struct boolean {
      // Booleans are ints in Lua
      typedef int write_type;
      typedef T read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isboolean(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return s.toboolean(idx);
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        f(s, idx);
      }

      inline static void set(::lua::state s, int idx, T value) {
        s.pushboolean(write_type(value));
        if (idx != 0) s.replace(idx);
      }
    };
  }
  
  template <>
  struct type_policy<bool> : public detail::boolean<bool> {
  };

  template <>
  struct type_policy<const bool> : public detail::boolean<const bool> {
  };
}
