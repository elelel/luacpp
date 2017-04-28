#pragma once

#include <exception>
#include <string>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "tuple_utils.hpp"

#define LUACPP_DETAIL_NATIVE_STATE_API2( RETURN_TYPE, NAME)     \
  inline RETURN_TYPE NAME() const {                             \
    typedef RETURN_TYPE return_type;                            \
    return RETURN_TYPE(lua_##NAME(l_));                         \
  };                                                            \
  
#define LUACPP_DETAIL_NATIVE_STATE_API4( RETURN_TYPE, NAME,     \
                                         TYPE1, ARG1)           \
  inline RETURN_TYPE NAME(TYPE1 ARG1) const {                   \
    typedef RETURN_TYPE return_type;                            \
    return return_type(lua_##NAME(l_, ARG1));                   \
  };                                                            \

#define LUACPP_DETAIL_NATIVE_STATE_API6( RETURN_TYPE, NAME,     \
                                         TYPE1, ARG1,           \
                                         TYPE2, ARG2)           \
  inline RETURN_TYPE NAME(TYPE1 ARG1, TYPE2 ARG2) const {       \
    typedef RETURN_TYPE return_type;                            \
    return RETURN_TYPE(lua_##NAME(l_, ARG1, ARG2));             \
  };                                                            \

#define LUACPP_DETAIL_NATIVE_STATE_API8( RETURN_TYPE, NAME,     \
                                         TYPE1, ARG1,           \
                                         TYPE2, ARG2,           \
                                         TYPE3, ARG3)           \
  inline RETURN_TYPE NAME(TYPE1 ARG1, TYPE2 ARG2,               \
                          TYPE3 ARG3) const {                   \
    typedef RETURN_TYPE return_type;                            \
    return RETURN_TYPE(lua_##NAME(l_, ARG1, ARG2, ARG3));       \
  };                                                            \

namespace lua {

  struct state_base {
    typedef state_base type;
    
    state_base() :
      l_(luaL_newstate()) {
    }

    state_base(lua_State* l) :
      l_(l) {
    }

    state_base(const type& other) :
      l_(other.l_) {
    }

    state_base(type&& other) :
      l_(std::move(other.l_)) {
    }

    void swap(type& other) {
      std::swap(l_, other.l_);
    }

    type& operator=(const type& other) {
      type tmp(other);
      swap(tmp);
      return *this;
    }
    
    lua_State* C_state() const {
      lua_State* l_copy = l_;
      return l_copy;
    }
    
    inline int type_lua(int idx = -1) const {
      return ::lua_type(l_, idx);
    }

    inline const char* typename_lua(int tp) const {
      return ::lua_typename(l_, tp);
    }

    inline void register_lua(const char* name,
                             lua_CFunction f) const {
      // calling a macro
      return lua_register(l_, name, f);
    }

    inline void pop() const {
      pop(1);
    }


    LUACPP_DETAIL_NATIVE_STATE_API2(void, pushnil)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, pushstring,
                                    const char*, s)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, pushnumber,
                                    lua_Number, n)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, pushboolean,
                                    int, n)
    LUACPP_DETAIL_NATIVE_STATE_API6(void, pushcclosure,
                                    lua_CFunction, fn,
                                    int, n)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, pushcfunction,
                                    lua_CFunction, fn)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, pushlightuserdata,
                                    void*, p)

    LUACPP_DETAIL_NATIVE_STATE_API2(int, gettop)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, pop,
                                    const int, n)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, replace,
                                    const int, n)
    
    LUACPP_DETAIL_NATIVE_STATE_API4(void, getglobal,
                                    const char*, name)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, setglobal,
                                    const char*, name)

    LUACPP_DETAIL_NATIVE_STATE_API4(int, isnil,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, isnumber,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, istable,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, isstring,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, isboolean,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, isfunction,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, islightuserdata,
                                    int, idx)
    
    LUACPP_DETAIL_NATIVE_STATE_API4(lua_Number, tonumber,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(const char*, tostring,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(int, toboolean,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(void*, topointer,
                                    int, idx)
    
    LUACPP_DETAIL_NATIVE_STATE_API6(void, createtable,
                                    int, narr,
                                    int, nrec)
    LUACPP_DETAIL_NATIVE_STATE_API2(void, newtable);
    LUACPP_DETAIL_NATIVE_STATE_API4(void, settable,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, gettable,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API6(void, getfield,
                                    int, idx,
                                    const char*, key)
    LUACPP_DETAIL_NATIVE_STATE_API6(void, setfield,
                                    int, idx,
                                    const char*, key)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, rawget,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API6(void, rawgeti,
                                    int, idx,
                                    int, n)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, rawset,
                                    int, idx)
    LUACPP_DETAIL_NATIVE_STATE_API6(void, rawseti,
                                    int, idx,
                                    int, n)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, next,
                                    int, idx)
#if (LUA_VERSION_NUM < 502)
    LUACPP_DETAIL_NATIVE_STATE_API4(void, objlen,
                                    int, idx)
    void rawlen(int idx) const {
      return objlen(idx);
    }
#else
    LUACPP_DETAIL_NATIVE_STATE_API4(void, rawlen,
                                    int, idx)
    void objlen(int idx) const {
      return rawlen(idx);
    }
#endif

    LUACPP_DETAIL_NATIVE_STATE_API8(int, pcall,
                                    int, nargs,
                                    int, nresults,
                                    int, errfunc)

    protected:
    lua_State* l_;
  };
}
