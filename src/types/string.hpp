#pragma once

#include <string>

#include "../type_adapter.hpp"

namespace lua {

  /*
    Non-generics: char pointer array should always be read as const
  */
  
  template <typename T>
  struct type_adapter_pchar {
    typedef type_adapter_pchar<T> type;
    
    inline static bool type_matches(const lua::state_base& s, int idx) {
      return s.isstring(idx);
    }

    inline static const char* get_unsafe(const lua::state_base& s, int idx) {
      return s.tostring(idx);
    }
    
    inline static void push(const lua::state_base& s, T value) {
      return s.pushstring(value);
    }
  };

  template <>
  struct type_adapter<char*> : public type_adapter_pchar<char*> {
  };

  template <>
  struct type_adapter<const char*> : public type_adapter_pchar<const char*> {
  };

  template <size_t X>
  struct type_adapter<char[X]> {
    typedef char value_type[X];
    typedef type_adapter<value_type> type;
    
    inline static bool type_matches(const lua::state_base& s, int idx) {
      return s.isstring(idx);
    }

    inline static const char* get_unsafe(const lua::state_base& s, int idx) {
      return s.tostring(idx);
    }
    
    inline static void push(const lua::state_base& s, value_type value) {
      return s.pushstring(value);
    }
  };

  template <size_t X>
  struct type_adapter<const char[X]> {
    typedef const char value_type[X];
    typedef type_adapter<value_type> type;
    
    inline static bool type_matches(const lua::state_base& s, int idx) {
      return s.isstring(idx);
    }

    inline static const char* get_unsafe(const lua::state_base& s, int idx) {
      return s.tostring(idx);
    }
    
    inline static void push(const lua::state_base& s, value_type value) {
      return s.pushstring(value);
    }
  };

  template <typename T>
  struct type_adapter_std_string {
    typedef type_adapter<T> type;

    inline static bool type_matches(const lua::state_base& s, int idx) {
      return s.isstring(idx);
    }

    inline static T get_unsafe(const lua::state_base& s, int idx) {
      return std::string(s.tostring(idx));
    }
    
    inline static void push(const lua::state_base& s, const std::string& value) {
      return s.pushstring(value.c_str());
    }
  };

  template <>
  struct type_adapter<std::string> : public type_adapter_std_string<std::string> {
  };

  template <>
  struct type_adapter<const std::string> : public type_adapter_std_string<const std::string> {
  };

}
