#pragma once

#include <tuple>

#include "state_base.hpp"

#include "entity.hpp"

namespace lua {
  struct state;
  template <typename derived_t, typename T, typename read_t>
  struct entity;
  
  struct state : public state_base {

    typedef state type;
    using state_base::state_base;

    void swap(state& other) {
      state_base::swap(other);
    }

    state& operator=(const state& other) {
      type tmp(other);
      swap(tmp);
      return *this;
    }

    template <typename T>
    auto at(int idx) const -> typename entity_type<T>::value {
      typedef typename entity_type<T>::value return_type;
      return return_type(*this, idx);
    }

    template <typename T>
    void push(T value) const {
      at<T>(0) = value;
    }

    template <typename return_tuple_t, typename args_tuple_t, typename result_callback_t>
    inline void call_function(const char* name, const args_tuple_t& args,
                              result_callback_t f) {
      getglobal(name);
      if (isfunction(-1)) {
        push_tuple(args);
        int rc = pcall(l_, std::tuple_size<args_tuple_t>::value,
                       std::tuple_size<return_tuple_t>::value, 0);
        if (rc == 0) {
          auto rslt = get_values<return_tuple_t>();
          f(rslt);
          pop(std::tuple_size<return_tuple_t>::value);
          return rslt;
        } else {
          throw std::runtime_error(std::string("call_function p_call failed: ") + name);
        }
      } else {
        throw std::runtime_error(std::string(name) + " is not a function in Lua global list, can't pcall");
      }
    }

    // Meta-functions to push onto stack
    template <std::size_t I = 0, typename... Tp>
    typename std::enable_if<I == sizeof...(Tp), void>::type
    inline push_tuple(const std::tuple<Tp...>& t) const {
    }

    template <std::size_t I = 0, typename... Tp>
    typename std::enable_if<I < sizeof...(Tp), void>::type
    inline push_tuple(const std::tuple<Tp...>& t) const {
      typedef decltype(std::get<I>(t)) A;
      push<A>(std::get<I>(t));
      push_tuple<I + 1, Tp...>(t);
    }

      template <typename tuple_t>
      inline void push_tuple(const tuple_t& t) const {
        push_tuple<0, tuple_t>(t);
      }

    // Meta-functions to read from stack
    template <std::size_t I = 0, typename tuple_t>
    typename std::enable_if<0 == std::tuple_size<tuple_t>::value, tuple_t>::type
    inline get_values_(int idx = -1) const {
      return std::tuple<>();
    }

    template <std::size_t I = 0, typename tuple_t>
    typename std::enable_if<0 != std::tuple_size<tuple_t>::value, tuple_t>::type
    inline get_values_(int idx = -1) const {
      typedef typename std::tuple_element<0, tuple_t>::type A;
      A value = at<A>(idx - I).get();
      return std::tuple_cat(std::tuple<A>(value), get_values_<I + 1,
                            typename tuple_tail_type<tuple_t>::type>(idx));
    }
    
    template <typename tuple_t>
    tuple_t inline get_values(int idx = -1) const {
      return get_values_<0, tuple_t>(idx);
    }
  };
}
