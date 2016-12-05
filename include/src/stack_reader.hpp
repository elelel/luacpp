#pragma once

#include "lua_afx.hpp"

#include "exceptions.hpp"
#include "state.hpp"

namespace lua {
  
  template <typename T>
  struct stack_reader {
  };

  template <>
  struct stack_reader<const char*> {
    static inline const char* read(const state& l, const int idx = -1) {
      if (l.isstring()) {
        return l.tostring(idx);
      } else {
        throw error::string_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return  "stack_reader<const char*>"; }
  };

  template <>
  struct stack_reader<std::string> {
    static inline std::string read(const state& l, const int idx = -1) {
      return std::string(l.tostring(idx));
    }
      
    static const std::string name() { return "stack_reader<std::string>"; }
  };
  
  template <>
  struct stack_reader<int> {
    static inline int read(const state& l, const int idx = -1) {
      if (l.isnumber(idx)) {
        return static_cast<int>(l.tonumber(idx));
      } else {
        throw error::number_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return "stack_reader<int>"; }
  };

  template <>
  struct stack_reader<unsigned int> {
    static inline int read(const state& l, const int idx = -1) {
      if (l.isnumber(idx)) {
        return static_cast<unsigned int>(l.tonumber(idx));
      } else {
        throw error::number_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return "stack_reader<int>"; }
  };

  template <>
  struct stack_reader<long> {
    static inline int read(const state& l, const int idx = -1) {
      if (l.isnumber(idx)) {
        return static_cast<unsigned int>(l.tonumber(idx));
      } else {
        throw error::number_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return "stack_reader<long>"; }
  };

  template <>
  struct stack_reader<unsigned long> {
    static inline int read(const state& l, const int idx = -1) {
      if (l.isnumber(idx)) {
        return static_cast<unsigned long>(l.tonumber(idx));
      } else {
        throw error::number_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return "stack_reader<unsigned long>"; }
  };

  template <>
  struct stack_reader<double> {
    static inline double read(const state& l, const int idx = -1) {
      if (l.isnumber(idx)) {
        return static_cast<double>(l.tonumber(idx));
      } else {
        throw error::number_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return "stack_reader<double>"; }
  };
  
  template <>
  struct stack_reader<bool> {
    static inline bool read(const state& l, const int idx = -1) {
      if (l.isboolean(idx)) {
        return static_cast<bool>(l.toboolean(idx));
      } else {
        throw error::boolean_expected(name(), l.luatypename(l.luatype()));
      }
    }

    static const std::string name() { return "stack_reader<bool>"; }
  };
}
