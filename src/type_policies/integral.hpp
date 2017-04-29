#pragma once

namespace lua {
  namespace detail {
    template <typename T>
    struct integral {
      typedef T write_type;
      typedef typename std::remove_reference<T>::type read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isnumber(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return read_type(s.tonumber(idx));
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        f(s, idx);
      }

      inline static void set(::lua::state s, int idx, T value) {
        s.pushnumber(write_type(value));
        if (idx != 0) s.replace(idx - 1);
      }
    };
  }
  
  template <>
  struct type_policy<int> : public detail::integral<int> {
  };

  template <>
  struct type_policy<const int> : public detail::integral<const int> {
  };
  
  template <>
  struct type_policy<const int&> : public detail::integral<const int&> {
  };
  
  template <>
  struct type_policy<unsigned int> : public detail::integral<unsigned int>  {
  };

  template <>
  struct type_policy<const unsigned int> : public detail::integral<const unsigned int>  {
  };
  
}

