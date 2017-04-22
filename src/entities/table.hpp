#pragma once

#define LUACPP_STATIC_TABLE_BEGIN( TABLE_NAME )         \
  class TABLE_NAME {                                    \
private:                                                \
 const lua::state_base s_;                              \
 const int idx_;                                        \
public:                                                 \
 TABLE_NAME(const lua::state_base& s, int idx) :        \
   s_(s),                                               \
   idx_(idx) {                                          \
   }                                                    \


#define LUACPP_DETAIL_CAT(x, y) PRIMITIVE_CAT(x, y)
#define LUACPP_DETAIL_PRIMITIVE_CAT(x, y) x ## y

#define LUACPP_STATIC_TABLE(TABLE_NAME)

#define LUACPP_ADD_TABLE_FIELD( TABLE_NAME, NAME, KEY_TYPE, VALUE_TYPE ) \
  struct TABLE_NAME##_##NAME##_type : public lua::table_field {         \
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
  LUACPP_DETAIL_PUSH_TABLE_FIELD_NAME( TABLE_NAME, NAME)                \
  



namespace lua {
  template <typename T, typename read_t>
  struct table_field : public entity<table_field<T, read_t>, T, read_t> {
    // The interface type should always be the base CRTP class
    typedef entity<table_field<T, read_t>, T, read_t> interface_type;
    
    using entity<table_field<T, read_t>, T, read_t>::entity;
    
    inline bool type_matches() const {
      return this->s_.istable(this->idx_);
    }

    template <typename key_t>
    inline read_t get_unsafe(key_t key) const {
      this->s_.push<>(key);
      s_.gettable(idx_ - 1);
      auto rslt = entity_type<T>::value(this->s_, this->idx_);
      s_.pop(1);
      return rslt;
    }

    template <typename key_t>
    inline void apply(key_t key, std::function<void(const lua::state&)>) {
      if (type_matches()) {
        this->s_.push<>(key);
        s_.gettable(idx_ - 1);
        f(s_);
        s_.pop(1);
      } else {
        throw std::runtime_error("Can't apply function to table field from non-table lua variable in stack");
      }
    }

    template <typename key_t>
    read_t get(key_t key) const {
      if (type_matches()) {
        this->s_.push<>(key);
        s_.gettable(idx_ - 1);
        entity_type<T>::value(this->s_, this->idx_) v;
        auto rslt = v.get();
      } else {
        throw std::runtime_error("Can't get table field from non-table lua variable in stack");
      }
    }

    inline void set(T value) const {
      if (type_matches()) {
        this->s_.push<>(key);
        this->s_.push<>(value);
        s_.gettable(idx_ - 1);
      } else {
        throw std::runtime_error("Can't create table field from non-table lua variable in stack");
      }
    }
  };

  template <>
  struct entity_type<const bool> {
    typedef table_field<bool>::interface_type value;
  };
    
}
