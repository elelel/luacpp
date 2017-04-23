#pragma once

namespace lua {

  namespace type_policy {
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
        return std::string(s.tostring(idx));
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

      inline static void set(::lua::state s, int idx, write_type value) {
        s.pushstring(value.c_str());
        if (idx != 0) s.replace(idx);
      }
    };
  }

  template <>
  struct get_type_policy<char*> {
    typedef type_policy::char_pointer<char*> value;
  };

  template <>
  struct get_type_policy<const char*> {
    typedef type_policy::char_pointer<const char*> value;
  };

  
  template <>
  struct get_type_policy<std::string> {
    typedef type_policy::std_string<std::string> value;
  };

  template <>
  struct get_type_policy<const std::string> {
    typedef type_policy::std_string<const std::string> value;
  };

  template <size_t N>
  struct get_type_policy<char[N]> {
    typedef type_policy::char_pointer<char*> value;
  };

  template <size_t N>
  struct get_type_policy<const char[N]> {
    typedef type_policy::char_pointer<char*> value;
  };

  template <size_t N>
  struct get_type_policy<const char(&)[N]> {
    typedef type_policy::char_pointer<const char*> value;
  };
    
}

