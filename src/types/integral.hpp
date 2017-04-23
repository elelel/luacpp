#pragma once

namespace lua {
  namespace type_policy {
    template <typename T>
    struct integral {
      typedef T write_type;
      typedef T read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isnumber(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return s.tonumber(idx);
      }

      inline static read_type get(::lua::state s, int idx) {
        if (type_matches(s, idx)) {
          return get_unsafe(s, idx);
        }
      }

      template <typename F>
      inline static void apply(::lua::state s, int idx, F f) {
        if (type_matches(s, idx)) {
          f(s, idx);
        }
      }

      inline static void set(::lua::state s, int idx, T value) {
        s.pushnumber(write_type(value));
        if (idx != 0) s.replace(idx);
      }
    };
  }
  
  template <>
  struct get_type_policy<int> {
    typedef type_policy::integral<int> value;
  };

  template <>
  struct get_type_policy<const int> {
    typedef type_policy::integral<const int> value;
  };
  
  template <>
  struct get_type_policy<unsigned int> {
    typedef type_policy::integral<int> value;
  };

  template <>
  struct get_type_policy<const unsigned int> {
    typedef type_policy::integral<const int> value;
  };
  
}

