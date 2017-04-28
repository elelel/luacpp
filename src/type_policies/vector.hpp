#pragma once

namespace lua {
  template <typename T>
  struct type_policy<vector_element<T>> {
    typedef T write_type;
    typedef T read_type;

    static inline bool type_matches(::lua::state s, const int idx) {
      return s.istable(idx); // Boxed type is not checked
    }
      
    static inline read_type get_unsafe(::lua::state s, const int idx, const int i) {
      s.rawgeti(idx, i);
      auto rslt = entity<type_policy<read_type>>(s, -1).get();
      s.pop(1);
      return rslt;
    }

    static inline void apply_unsafe(::lua::state s, const int idx, std::function<void(const lua::state&, int)> f,
                                    const int i) {
      s.rawgeti(idx, i);
      f(s, idx);
      s.pop(1);
    }

    static inline void set(::lua::state s, const int idx, write_type value, const int i)  {
      if (type_matches(s, idx)) {
        s.push<>(i);
        s.push<>(value);
        s.settable(idx - 2);
      } else {
        throw std::runtime_error("Can't create table field from non-table lua variable in stack");
      }
    }
  };


  template <typename T>
  struct type_policy<std::vector<T>> {
    typedef std::vector<T> write_type;
    typedef entity<::lua::vector<T>> read_type;

    static inline bool type_matches(::lua::state s, int idx) {
      return s.istable(idx); 
    }
      
    static inline read_type get_unsafe(::lua::state s, int idx) {
      return read_type(s, idx).get();
    }

    static inline void apply_unsafe(::lua::state s, int idx, std::function<void(const lua::state&, int)> f) {
      f(s, idx);
    }

    static inline void set(::lua::state s, int idx, const write_type& value) {
      if (type_matches(s, idx)) {
        ::lua::vector<T> lv(s, idx);
        for (size_t i = 0; i < value.size(); ++i) {
          lv.at(i).set(value[i]);
        }

        const auto sz = lv.size();
        if (sz > value.size()) {
          for (int i = value.size(); i < lv.size(); ++i) {
            lv.at(i).remove();
          }; 
        }
      } else {
        throw std::runtime_error("Luacpp: Can't assign vector to a non-table lua variable in stack");
      }
    }
  };
  
  
}
