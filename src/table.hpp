#pragma once

#include <exception>

#include "state_base.hpp"
#include "type_adapter.hpp"

#define LUACPP_STATIC_TABLE_BEGIN( TABLE_NAME )         \
  class TABLE_NAME {                                    \
  private:                                              \
  const lua::state_base s_;                             \
  const int idx_;                                       \
  public:                                               \
  TABLE_NAME(const lua::state_base& s, int idx) :       \
    s_(s),                                              \
    idx_(idx) {                                         \
  }                                                     \


#define LUACPP_TABLE_FIELD_WITH_STR_KEY( NAME, KEY_TYPE, VALUE_TYPE )   \
  struct NAME##_type : public lua::table_field {              \
    using lua::table_field::table_field;                                \
    void set(VALUE_TYPE value) const  {                                 \
      table_field::set<KEY_TYPE, VALUE_TYPE>(#NAME, value);             \
    }                                                                   \
                                                                        \
    VALUE_TYPE get_unsafe() const {                                     \
      return table_field::get_unsafe<KEY_TYPE, VALUE_TYPE>(#NAME);      \
    }                                                                   \
                                                                        \
    VALUE_TYPE get() const {                                            \
      return table_field::get<KEY_TYPE, VALUE_TYPE>(#NAME);             \
    }                                                                   \
                                                                        \
    VALUE_TYPE operator=(VALUE_TYPE value) const {                      \
      set(value);                                                       \
      return value;                                                     \
    }                                                                   \
                                                                        \
    VALUE_TYPE operator()() const {                                     \
      return get();                                                     \
    }                                                                   \
  };                                                                    \
  NAME##_type NAME{s_, idx_};                                           \


#define LUACPP_TABLE_FIELD_WITH_INT_KEY( NAME, KEY_TYPE, VALUE_TYPE )   \
  struct integral_key_field_##NAME##_type : public lua::table_field {   \
    using lua::table_field::table_field;                                \
                                                                        \
    void set(VALUE_TYPE value) const {                                  \
      table_field::set<KEY_TYPE, VALUE_TYPE>(NAME, value);              \
    }                                                                   \
                                                                        \
    VALUE_TYPE get_unsafe() const {                                     \
      return table_field::get_unsafe<KEY_TYPE, VALUE_TYPE>(NAME);       \
    }                                                                   \
                                                                        \
    VALUE_TYPE get() const {                                            \
      return table_field::get<KEY_TYPE, VALUE_TYPE>(NAME);              \
    }                                                                   \
                                                                        \
    VALUE_TYPE operator=(VALUE_TYPE value) const {                      \
      set(value);                                                       \
      return value;                                                     \
    }                                                                   \
                                                                        \
    VALUE_TYPE operator()() const {                                     \
      return get();                                                     \
    }                                                                   \
  };                                                                    \
  integral_key_field_##NAME##_type integral_##NAME{s_, idx_};           \

#define LUACPP_STATIC_TABLE_END()               \
  };                                            \

namespace lua {
  
  struct table_field {

    // idx - stack offset to table
    table_field(const state_base& s, int idx) :
      s_(s),
      idx_(idx) {
    }

    inline bool type_matches() const {
      return s_.istable(idx_);
    }

    template <typename key_t, typename value_t>
    void set(key_t key, value_t value) const {
      if (type_matches()) {
        stack_adapter(s_).at<key_t>(0) = key;
        stack_adapter(s_).at<value_t>(0) = value;
        s_.settable(idx_ - 2);
      } else {
        throw std::runtime_error("Can't create table field from non-table lua variable in stack");
      }
    }

    template <typename key_t, typename value_t>
    auto get_unsafe(key_t key) const ->
      decltype(type_adapter<value_t>::get_unsafe(lua::state_base(), int{0})) {
      stack_adapter(s_).at<key_t>(0) = key;
      s_.gettable(idx_ - 1);
      auto rslt = type_adapter<value_t>::get_unsafe(s_, idx_);
      s_.pop(1);
      return rslt;
    }

    template <typename key_t, typename value_t>
    auto get(key_t key) const ->
      decltype(type_adapter<value_t>::get_unsafe(lua::state_base(), int{0})) {
      if (type_matches()) {
        stack_adapter(s_).at<key_t>(0) = key;
        s_.gettable(idx_ - 1);
        if (type_adapter<value_t>::type_matches(s_, idx_)) {
          auto rslt = type_adapter<value_t>::get_unsafe(s_, idx_);
          s_.pop(1);
          return rslt;
        } else {
          throw std::runtime_error("Luacpp safe get value table failed: value at stack does not match the static type");
        }
      } else {
        throw std::runtime_error("Can't create table field from non-table lua variable in stack");
      }
    }

  protected:
    const lua::state_base s_;
    const int idx_;
  };
  
}
