#pragma once

#include <vector>

#include "lua_afx.hpp"

#include "state_base.hpp"

#include "tuple_utils.hpp"

namespace lua {
  template <typename T>
  struct stack_reader;
  
  template <typename T>
  struct stack_pusher; 
  
  struct state : state_base {
    typedef state type;

    state(lua_State* L) :
      state_base(L) {
    }

    state(const state& l) :
      state_base(l) {
    }

    state(type&& other) :
      state_base(std::move(other)) {
    }
        
    void swap(type& other) {
      state::swap(other);
    }
    
    type& operator=(const type& other) {
      type tmp(other);
      swap(tmp);
      return *this;
    }
    
    // Meta-functions to push onto stack
    template <std::size_t I = 0, typename... Tp>
    typename std::enable_if<I == sizeof...(Tp), void>::type
    inline push(const std::tuple<Tp...>& t) const {
    }

    template <std::size_t I = 0, typename... Tp>
    typename std::enable_if<I < sizeof...(Tp), void>::type
    inline push(const std::tuple<Tp...>& t) const {
      typedef decltype(std::get<I>(t)) A;
      stack_pusher<A>::push(*this, std::get<I>(t));
      push<I + 1, Tp...>(t);
    }

    template <typename tuple_t>
    inline void push(const tuple_t& t) const {
      push<0, tuple_t>(t);
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
      A value = get_value<A>(idx - I);
      return std::tuple_cat(std::tuple<A>(value), get_values_<I + 1,
                            typename tuple_tail_type<tuple_t>::type>(idx));
    }
    
    template <typename tuple_t>
    tuple_t inline get_values(int idx = -1) const {
      return get_values_<0, tuple_t>(idx);
    }

    template <typename T>
    T get_value(const int idx = -1) const {
      return stack_reader<T>::read(*this, idx);
    }
    
    template <typename T>
    void get_value_into(T& v, const int idx = -1) const {
      v = get_value<T>(idx);
    }
    
    // Meta-functions to read map-like tables
    template <std::size_t I = 0, typename tuple_t>
    typename std::enable_if<0 == std::tuple_size<tuple_t>::value, tuple_t>::type
    inline get_fields_(const std::vector<std::string>& keys, int idx = -1) const {
      return std::tuple<>();
    }

    template <std::size_t I = 0, typename tuple_t>
    typename std::enable_if<I < std::tuple_size<tuple_t>::value, tuple_t>::type
    inline get_fields_(const std::vector<std::string>& keys, int idx = -1) const {
      typedef typename std::tuple_element<0, tuple_t>::type A;
      A value = get_field<A>(keys[I].c_str(), idx);
      return std::tuple_cat(std::tuple<A>(value), get_fields_<I + 1,
                            typename tuple_tail_type<tuple_t>::type>(idx));
    }

    template <typename tuple_t>
    tuple_t inline get_fields(const std::vector<std::string>& keys, int idx = -1) const {
      if (std::tuple_size<tuple_t>::value == keys.size()) {
        return get_fields_<0, tuple_t>(keys, idx);
      } else {
        throw std::runtime_error("get_fields: tuple size and keys size are not equal");
      }
    }

    template <typename T>
    T get_field(const char* key, const int idx = -1) const {
      getfield(idx, key);
      T value = stack_reader<T>::read(*this);
      pop(1);
      return value;
    }

    template <typename T>
    void get_field_into(const char* key, T& v, const int idx = -1) const {
      v = get_field<T>(key, idx);
    }

    // Read array-like tables
    template <typename row_t>
    std::vector<row_t> get_rows(const int idx = -1, const size_t size_hint = 0) const {
      if (!istable()) throw error::table_expected("get_rows", luatypename(luatype()));
      std::vector<row_t> rslt;
      rslt.reserve(size_hint);
      pushnil();
      while (next(-2) != 0) {
        rslt.push_back(get_value<row_t>());
        pop(1);
      }
      return rslt;
    }

    template <typename row_t>
    void get_rows_into(std::vector<row_t>& table, const int idx = -1, const size_t size_hint = 0) const {
      table = get_rows<row_t>(idx, size_hint);
    }

    // Meta-functions to make function calls
    template <typename return_tuple_t,
              typename params_tuple_t>
    inline return_tuple_t pcall(const char* name,
                               const params_tuple_t& params) const {
      getglobal(name);
      if (lua_isfunction(L_, -1)) {
        push(params);
        int rc = lua_pcall(L_, std::tuple_size<params_tuple_t>::value,
                           std::tuple_size<return_tuple_t>::value, 0);
        if (rc == 0) {
          auto rslt = get_values<return_tuple_t>();
          pop(std::tuple_size<return_tuple_t>::value);
          return rslt;
        } else {
          throw error::call_failed(std::string(name));
        }
      } else {
        throw error::function_expected(std::string(name) + " for call in Lua global list",
                                       luatypename(luatype()));
      }
    }
  };
}
