#pragma once

#include <exception>

#include "state_base.hpp"
#include "type_adapter.hpp"

namespace lua {

  template <typename T>
  struct stack_value {
    typedef stack_value<T> type;
    
    stack_value(const lua::state_base& s, const int idx) :
      s_(s),
      idx_(idx) {
    }
      
    inline bool type_matches() const {
      return type_adapter<T>::type_matches(s_, idx_);
    }

    inline auto get_unsafe() const
      -> decltype(type_adapter<T>::get_unsafe(lua::state_base(), int{0})) {
      return type_adapter<T>::get_unsafe(s_, idx_);
    }

    inline auto get() const
      -> decltype(type_adapter<T>::get_unsafe(lua::state_base(), int{0})) {
      if (type_matches()) {
        return get_unsafe();
      } else {
        throw std::runtime_error("Luacpp safe get value failed: value at stack does not match the static type");
      }
    }

    void set(T value) const {
      type_adapter<T>::push(s_, value);
      if (idx_ != 0) s_.replace(idx_);
    }

    inline type& operator=(T value) {
      set(value);
      return *this;
    }
      
  private:
    const lua::state_base s_;
    const int idx_;
  };
    
}
