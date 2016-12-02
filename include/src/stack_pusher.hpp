#pragma once

#include "exceptions.hpp"
#include "state_base.hpp"

namespace lua {
  template <typename T>
  struct stack_pusher {
  };

  template <>
  struct stack_pusher<const char* const&> {
    static inline void push(const state_base& l, const char* const& v ) {
      l.pushstring(v);
    }

    const std::string name = "stack_pusher<const char*>";
  };

  template <>
  struct stack_pusher<const std::string&> {
    static inline void push(const state_base& l, const std::string& v) {
      l.pushstring(v.c_str());
    }
    const std::string name = "stack_pusher<std::string>";
  };
    
  template <>
  struct stack_pusher<const int&> {
    static inline void push(const state_base& l, const int& v) {
      l.pushnumber(v);
    }
    const std::string name = "stack_pusher<int>";
  };

  template <>
  struct stack_pusher<const unsigned int&> {
    static inline void push(const state_base& l, const int& v) {
      l.pushnumber(v);
    }
    const std::string name = "stack_pusher<int>";
  };

    
  template <>
  struct stack_pusher<const long&> {
    static inline void push(const state_base& l, const int& v) {
      l.pushnumber(v);
    }
    const std::string name = "stack_pusher<long>";
  };

  template <>
  struct stack_pusher<const unsigned long&> {
    static inline void push(state_base& l, const int& v) {
      l.pushnumber(v);
    }
    const std::string name = "stack_pusher<unsigned long>";
  };
  template <>
  struct stack_pusher<const bool&> {
    static inline void push(const state_base& l, const bool& v) {
      l.pushboolean(v);
    }
    const std::string name = "stack_pusher<bool>";    
  };

  template <>
  struct stack_pusher<const double&> {
    static inline void push(const state_base& l, const bool& v) {
      l.pushnumber(v);
    }
    const std::string name = "stack_pusher<double>";    
  };
}
