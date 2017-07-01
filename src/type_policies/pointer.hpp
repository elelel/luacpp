#pragma once

namespace lua {
  namespace detail {
    template <typename T>
    struct void_pointer {
      // Void_Pointers are ints in Lua
      typedef T write_type;
      typedef typename std::remove_reference<T>::type read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.islightuserdata(idx) || s.isfunction(idx) || s.iscfunction(idx) || s.isthread(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return s.topointer(idx);
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        f(s, idx);
      }

      inline static void set(::lua::state s, int idx, T value) {
        // Writes void always as light user data
        s.pushlightuserdata(write_type(value));
        if (idx != 0) s.replace(idx);
      }
    };
  }
  
  template <>
  struct type_policy<void*> : public detail::void_pointer<void*> {
  };

  template <>
  struct type_policy<const void*> : public detail::void_pointer<const void*> {
  };
}
