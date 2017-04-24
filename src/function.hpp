#pragma once

#include <functional>

#define LUACPP_DECLARE_FUNCTION(NAME, LAMBDA)                           \
  namespace lua {                                                       \
  namespace function {                                                  \
  template <typename return_tuple_t, typename... Args>                  \
  struct NAME_type {                                                    \
    NAME(const ::lua::state& s, const std::string& name,                \
         std::function<return_tuple_t(const ::lua::state& s, Args...)> f) { \
      s.pushcfunction(&c_function);                                     \
      s.setglobal(#NAME);                                               \
    }                                                                   \
                                                                        \
    static int c_function(lua_State* c_state) {                         \
      ::lua::state s(c_state);                                          \
      const int num_args = s.gettop();                                  \
      if (num_args == sizeof...(Args)) {                                \
        auto args = std::tuple_cat(std::make_tuple(s, s.get_values<std::tuple<Args...>>(1))); \
        auto rslt = ::lua::apply_tuple<>(LAMBDA, args);                 \
        s.push_tuple(rslt);                                             \
        return std::tuple_size<decltype(rslt)>::value;                  \
      } else {                                                          \
        throw std::runtime_error("Luacpp error: function is invoked with " + std::to_string(num_args) + \
                                 " arguments, but should be with " + std::to_string(sizeof...(Args))); \
      }                                                                 \
    }                                                                   \
  };                                                                    \
  }                                                                     \
  }                                                                     \

