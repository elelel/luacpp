#pragma once

namespace lua {
  template <typename T>
  struct boolean : public entity<boolean<T>, T, T> {
    // The interface type should always be the base CRTP class
    typedef entity<boolean<T>, T, T> interface_type;
    
    using entity<boolean<T>, T, T>::entity;
    
    inline bool type_matches() const {
      return this->s_.isboolean(this->idx_);
    }
    
    inline T get_unsafe() const {
      return T(this->s_.toboolean(this->idx_));
    }

    inline void set(T value) const {
      return this->s_.pushboolean((T)value);
    }
  };
  
  template <>
  struct entity_type<bool> {
    typedef boolean<bool>::interface_type value;
  };

  template <>
  struct entity_type<const bool> {
    typedef boolean<bool>::interface_type value;
  };
    
}
