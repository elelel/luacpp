#pragma once

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
