#pragma once

namespace lua {

  namespace detail {
    template <typename T>
    struct char_pointer {
      typedef T write_type;
      // Char pointer array should always be read as const
      typedef const char* read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isstring(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return s.tostring(idx);
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        f(s, idx);
      }

      inline static void set(::lua::state s, int idx, T value) {
        s.pushstring(write_type(value));
        if (idx != 0) s.replace(idx);
      }
    };

    template <typename T>
    struct std_string {
      typedef T write_type;
      typedef T read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isstring(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        auto pchar = s.tostring(idx);
        if (pchar == nullptr) {
          throw std::runtime_error("Luacpp get unsafe std::string failed: can't construct the string from nullptr");
        }
        return std::string(pchar);
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        f(s, idx);
      }

      inline static void set(::lua::state s, int idx, write_type value) {
        s.pushstring(value.c_str());
        if (idx != 0) s.replace(idx);
      }
    };
  }

  template <>
  struct type_policy<char*> : public detail::char_pointer<char*> {
  };

  template <>
  struct type_policy<const char*> : public detail::char_pointer<const char*> {
  };

  
  template <>
  struct type_policy<std::string> : public detail::std_string<std::string> {
  };

  template <>
  struct type_policy<const std::string> : public detail::std_string<const std::string> {
  };

  template <size_t N>
  struct type_policy<char[N]> : public detail::char_pointer<char*> {
  };

  template <size_t N>
  struct type_policy<const char[N]> : public detail::char_pointer<char*> {
  };

  template <size_t N>
  struct type_policy<const char(&)[N]> : public detail::char_pointer<const char*> {
  };
    
}

