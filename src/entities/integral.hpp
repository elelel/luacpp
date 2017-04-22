#pragma once

namespace lua {
  template <typename T>
  struct integral : public entity<integral<T>, T, T> {
    // The interface type should always be the base CRTP class
    typedef entity<integral<T>, T, T> interface_type;
    
    using entity<integral<T>, T, T>::entity;
    
    inline bool type_matches() const {
      return this->s_.isnumber(this->idx_);
    }
    
    inline T get_unsafe() const {
      return T(this->s_.tonumber(this->idx_));
    }

    inline void set(T value) const {
      return this->s_.pushnumber((T)value);
    }
  };
  
  template <>
  struct entity_type<int> {
    typedef integral<int>::interface_type value;
  };

  template <>
  struct entity_type<const int> {
    typedef integral<const int>::interface_type value;
  };

  template <>
  struct entity_type<unsigned int> {
    typedef integral<unsigned int>::interface_type value;
  };

  template <>
  struct entity_type<const unsigned int> {
    typedef integral<const unsigned int>::interface_type value;
  };
  
}

