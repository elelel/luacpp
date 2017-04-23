#pragma once

#include <tuple>

#include "state_base.hpp"

namespace lua {
  // Main interface class
  struct state;

  // Generic lua entity (primitive types, tables, functions) holder
  template <typename policy_t>
  struct entity;
  
  //Type adapter, maps C++ type to corresponding entity type.
  template <typename T>
  struct type_policy;
  
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

  /* Generic stack entity.
     Type policies should follow the concept::

    All reading functions should correct the stack on return

    // Checks if the value on stack looks like the right type
    inline static bool type_matches(::lua::state s, int idx)
    // Reads the value on stack without the check,
    // the return value is copy-constructed
    inline static T get_unsafe(::lua::state s, int idx);
    // Places the value on the stack if needed, and calls function f(const lua::state&, idx),
    // no copying should occur in the process
    template <typename F>
    inline static void apply_unsafe(::lua::state s, int idx, F f, args...);
    // Puts the value on stack
    inline static void set(::lua::state s, int idx, T value, args...);
   */

  template <typename policy_t>
  struct entity {
    typedef typename policy_t::read_type read_type;
    typedef typename policy_t::write_type write_type;

    entity(const ::lua::state& s, const int idx) :
      s_(s),
      idx_(idx) {
    }

    // -- Forwarding to policy -
    template <typename... Args>
    inline bool type_matches(Args&&... args) const {
      return policy_t::type_matches(s_, idx_, args...);
    }

    template <typename... Args>
    inline read_type get_unsafe(Args&&... args) const {
      return policy_t::get_unsafe(s_, idx_, args...);
    }

    template <typename... Args>
    inline void set(write_type value, Args&&... args) const {
      policy_t::set(s_, idx_, value, args...);
    }

    template <typename F, typename... Args>
    inline void apply_unsafe(F f, Args&&... args) {
      policy_t::apply_unsafe(s_, idx_, f, args...);
    }

    // -- Syntactic suger --
    
    template <typename... Args>
    inline read_type get(Args... args) const {
      if (type_matches(args...)) {
        return get_unsafe(args...);
      } else {
        throw std::runtime_error("Can't get lua enity's value safely: typecheck failed");
      }
    }

    template <typename F, typename... Args>
    inline read_type apply(F f, Args... args) const {
      if (type_matches(args...)) {
        return apply_unsafe(args...);
      } else {
        throw std::runtime_error("Can't get lua enity's value safely: typecheck failed");
      }
    }
    
    template <typename... Args>
    inline read_type operator()(Args... args) const {
      return get(args...);
    }

    // Note that operator= sets the entity's content, does not assign one entity to another
    inline void operator=(write_type value) const {
      set(value);
    }
  protected:
    const lua::state s_;
    const int idx_;
  };
  
      
}
