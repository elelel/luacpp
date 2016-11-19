#pragma once

#include "lua_afx.hpp"

#include "exceptions.hpp"

#include <tuple>

namespace lua {
  struct state_base {
    typedef state_base type;

    state_base(lua_State* L) :
      L_(L) {
    }
    
    state_base(const type& other) :
      L_(other.L_) {
    }
    
    state_base(type&& other) :
      L_(std::move(other.L_)) {
    }
        
    void swap(type& other) {
      std::swap(L_, other.L_);
    }
    
    type& operator=(const type& other) {
      type tmp(other);
      swap(tmp);
      return *this;
    }

    lua_State*& lua_state() {
      return L_;
    }

    // Translations of standard lua_ functions
    inline void pop(const int n) {
      lua_pop(L_, n);
    }

    inline void getglobal(const char* name) {
      lua_getglobal(L_, name);
    }
    
    inline void getfield(int idx, const char* key) {
      lua_getfield(L_, idx, key);
    }

    inline void getfield(const char* key) {
      getfield(-1, key);
    }

    inline void setfield(int idx, const char* key) {
      lua_setfield(L_, idx, key);
    }
    
    inline void setfield(const char* key) {
      setfield(-1, key);
    }

    inline int luatype(int idx = -1) {
      return lua_type(L_, idx);
    }

    inline const char* luatypename(int tp) {
      return lua_typename(L_, tp);
    }

    inline bool isnil(int idx = -1) {
      return static_cast<bool>(lua_isnil(L_, idx));
    }
    
    inline bool isnumber(int idx = -1) {
      return lua_isnumber(L_, idx) == 1;
    }

    inline bool istable(int idx = -1) {
      return lua_istable(L_, idx) == 1;
    }

    inline bool isstring(int idx = -1) {
      return lua_isstring(L_, idx) == 1;
    }

    inline bool isboolean(int idx = -1) {
      return lua_isboolean(L_, idx) == 1;
    }
    
    inline lua_Number tonumber(int idx = -1) {
      return lua_tonumber(L_, idx);
    }
    
    inline const char* tostring(int idx = -1) {
      return lua_tostring(L_, idx);
    }
    
    inline bool toboolean(int idx = -1) {
      return lua_toboolean(L_, idx) == 1;
    }

    inline void pushstring(const char* s) {
      lua_pushstring(L_, s);
    }

    inline void pushnumber(const lua_Number& v) {
      lua_pushnumber(L_, v);
    }

    inline void pushboolean(const bool& v) {
      lua_pushboolean(L_, v);
    }

    inline void pushnil() {
      lua_pushnil(L_);
    }

    inline void pushcclosure(lua_CFunction fn, int n) {
      lua_pushcclosure(L_, fn, n);
    }

    inline int next(int idx = -1) {
      return lua_next(L_, idx);
    }

    inline void createtable(int narr, int nrec) {
      lua_createtable(L_, narr, nrec);
    }

    inline void settable(int index) {
      lua_settable(L_, index);
    }

  protected:
    lua_State* L_;
  };
}
