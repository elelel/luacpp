#pragma once

namespace lua {

  template <typename T>
  struct floating : public entity<floating<T>, T, T> {
    // The interface type should always be the base CRTP class
    typedef entity<floating<T>, T, T> interface_type;
    
    using entity<floating<T>, T, T>::entity;

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
  struct entity_type<double> {
    typedef floating<double>::interface_type value;
  };

  template <>
  struct entity_type<const double> {
    typedef floating<const double>::interface_type value;
  };

  template <>
  struct entity_type<float> {
    typedef floating<float>::interface_type value;
  };

  template <>
  struct entity_type<const float> {
    typedef floating<const float>::interface_type value;
  };
    
}

