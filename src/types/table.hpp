#pragma once

#define LUACPP_STATIC_TABLE_BEGIN( TABLE_NAME ) \
  class TABLE_NAME {                            \
private:                                        \
 const lua::state s_;                           \
 const int idx_;                                \
public:                                         \
 TABLE_NAME(const lua::state& s, int idx) :     \
   s_(s),                                       \
   idx_(idx) {                                  \
   }                                            \
                                                \
 inline void create() const {                   \
   s_.newtable();                               \
 }                                              \
 
#define LUACPP_TABLE_FIELD_STR_KEY(NAME, KEY_TYPE, VALUE_TYPE )         \
  struct NAME##_type_policy :                                           \
    public ::lua::detail::table_field_policy_base<KEY_TYPE, VALUE_TYPE> { \
    using base_type = ::lua::detail::table_field_policy_base<KEY_TYPE, VALUE_TYPE>; \
                                                                        \
    static inline read_type get_unsafe(::lua::state s, int idx)  {      \
      return base_type::get_unsafe(s, idx, #NAME);                      \
    }                                                                   \
                                                                        \
    static inline void apply_unsafe(::lua::state s, int idx, std::function<void(const lua::state&, int)> f) { \
      base_type::apply_unsafe(s, idx, f, #NAME);                        \
    }                                                                   \
                                                                        \
    static inline void set(::lua::state s, int idx, VALUE_TYPE value)   { \
      base_type::set(s, idx, value, #NAME);                             \
    }                                                                   \
  };                                                                    \
  ::lua::entity<NAME##_type_policy> NAME{s_, idx_};                     \

#define LUACPP_TABLE_FIELD(NAME, VALUE_TYPE)                    \
  LUACPP_TABLE_FIELD_STR_KEY(NAME, const char*, VALUE_TYPE)     \
  

#define LUACPP_STATIC_TABLE_END()               \
  };                                            \

#define LUACPP_STATIC_TABLE_TYPE_POLICY(ROOT_QUALIFIED_TABLE_NAME)      \
  namespace lua {                                                       \
  template <>                                                           \
  struct type_policy<ROOT_QUALIFIED_TABLE_NAME> {                       \
  typedef ROOT_QUALIFIED_TABLE_NAME write_type;                         \
  typedef ROOT_QUALIFIED_TABLE_NAME read_type;                          \
                                                                        \
  static inline bool type_matches(::lua::state s, int idx) {            \
    /* It may be not created yet  */                                    \
    return s.isnil(idx) || s.istable(idx);                              \
  }                                                                     \
                                                                        \
  static inline read_type get_unsafe(::lua::state s, int idx) {         \
    if (s.isnil(idx)) {                                                 \
      /* Assume we are pointing at correct place to create the table */ \
      s.newtable();                                                     \
      s.replace(idx);                                                   \
    }                                                                   \
    return read_type(s, idx);                                           \
  }                                                                     \
                                                                        \
  template <typename F>                                                 \
  static inline void apply_unsafe(::lua::state s, int idx, F f) {       \
    f(s, idx);                                                          \
  }                                                                     \
                                                                        \
  static inline void set(::lua::state s, int idx, write_type value) {   \
    throw std::runtime_error(std::string("Luacpp table ") + #ROOT_QUALIFIED_TABLE_NAME + " error: setting not implemented" ); \
  }                                                                     \
  };                                                                    \
  }                                                                     \
    
namespace lua {
  namespace detail {
    
    template <typename key_t, typename value_t>
    struct table_field_policy_base {
      typedef value_t write_type;
      typedef value_t read_type;

      static inline bool type_matches(::lua::state s, int idx) {
        return s.istable(idx); // Checks only for table type
      }
      
      static inline read_type get_unsafe(::lua::state s, int idx, key_t key) {
        s.push<>(key);
        s.gettable(idx - 1);
        auto rslt = entity<type_policy<read_type>>(s, idx).get();
        s.pop(1);
        return rslt;
      }

      static inline void apply_unsafe(::lua::state s, int idx, std::function<void(const lua::state&, int)> f, key_t key) {
        s.push<>(key);
        s.gettable(idx - 1);
        f(s, idx);
        s.pop(1);
      }

      static inline void set(::lua::state s, int idx, write_type value, key_t key)  {
        if (type_matches(s, idx)) {
          s.push<>(key);
          s.push<>(value);
          s.settable(idx - 2);
        } else {
          throw std::runtime_error("Can't create table field from non-table lua variable in stack");
        }
      }
    };
  
  }
  
}
