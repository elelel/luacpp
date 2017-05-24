#pragma once

#include <functional>
#include <tuple>

#include "state_base.hpp"

#include "declarations.hpp"

namespace lua {  
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
    auto at(int idx) const -> entity<type_policy<T>> {
      return entity<type_policy<T>>(*this, idx);
    }
    
    template <typename T>
    void push(T value) const {
      at<T>(0) = value;
    }

    // Meta-functions to push onto stack
    template <typename T, typename... Ts>
    void push_variadic(const T& value, Ts... values) const {
      push<T>(value);
      push_variadic(values...);
    }

    template <typename T>
    void push_variadic(const T& value) const {
      push<T>(value);
    }

    void push_variadic() const {};
    
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

    template <std::size_t I = 0, typename tuple_t>
    typename std::enable_if<0 == std::tuple_size<tuple_t>::value, tuple_t>::type
    inline get_values_reverse_(int idx = -1) const {
      return std::tuple<>();
    }

    template <std::size_t I = 0, typename tuple_t>
    typename std::enable_if<0 != std::tuple_size<tuple_t>::value, tuple_t>::type
    inline get_values_reverse_(int idx = -1) const {
      typedef typename std::tuple_element<0, tuple_t>::type A;
      A value = at<A>(idx - (std::tuple_size<tuple_t>::value - I -1)).get();
      return std::tuple_cat(std::tuple<A>(value), get_values_reverse_<I + 1,
                            typename tuple_tail_type<tuple_t>::type>(idx));
    }
    
    template <typename tuple_t>
    tuple_t inline get_values_reverse(int idx = -1) const {
      return get_values_reverse_<0, tuple_t>(idx);
    }

    // Call functions
    template <typename callback_t,
              typename... Args>
    inline void call_and_apply(callback_t f,
                               const int n_result,
                               const char* name, Args&&... args) const {
      getglobal(name);
      if (isfunction(-1)) {
        push_variadic(std::forward<Args>(args)...);
        int rc = pcall(sizeof...(args), n_result, 0);
        if (rc == 0) {
          int correct_stack_size = f(*this);
          pop(correct_stack_size);
        } else {
          throw std::runtime_error(std::string("Luacpp call_and_apply error: call to ")
                                   + name + " failed with error " + std::to_string(rc));
        }
      } else {
        throw std::runtime_error(std::string("Luacpp call_and_apply error: ") + name
                                 + " is not a function name in Lua global list, can't pcall");
      }
    }
    
    template <typename return_tuple_t, typename... Args>
    inline return_tuple_t call(const char* name, Args&&... args) const {
      getglobal(name);
      if (isfunction(-1)) {
        push_variadic(std::forward<Args>(args)...);
        int rc = pcall(sizeof...(args), std::tuple_size<return_tuple_t>::value, 0);
        if (rc == 0) {
          auto rslt = get_values_reverse<return_tuple_t>();
          pop(std::tuple_size<return_tuple_t>::value);
          return rslt;
        } else {
          throw std::runtime_error(std::string("Luacpp call error: call to ")
                                   + name + " failed with error " + std::to_string(rc));
        }
      } else {
        throw std::runtime_error(std::string("Luacpp call error: ") + name
                                 + " is not a function name in Lua global list, can't pcall");
      }
    }

    template <typename... Args>
    inline int call_with_results_on_stack(const char* name, const int& result_sz,
                                                     Args&&... args) const {
      getglobal(name);
      if (isfunction(-1)) {
        push_variadic(std::forward<Args>(args)...);
        int rc = pcall(sizeof...(args), result_sz, 0);
        if (rc == 0) {
          return result_sz;
        } else {
          throw std::runtime_error(std::string("Luacpp call error: call to ")
                                   + name + " failed with error " + std::to_string(rc));
        }
      } else {
        throw std::runtime_error(std::string("Luacpp call error: ") + name
                                 + " is not a function name in Lua global list, can't pcall");
      }
    }

  };
  

}
