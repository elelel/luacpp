#pragma once

#include "state_base.hpp"
#include "stack_value.hpp"

namespace lua {

  struct stack_adapter {
    typedef stack_adapter type;

    stack_adapter(const state_base& s) :
      s_(s) {
    }

    stack_adapter(const type& other) :
      s_(other.s_) {
    }

    stack_adapter(type&& other) :
      s_(std::move(other.s_)) {
    }

    void swap(type& other) {
      std::swap(s_, other.s_);
    }

    template <typename T>
    stack_value<T> at(int idx) const {
      return stack_value<T>(s_, idx);
    }
    
  private:
    lua::state_base s_;
  };
}

