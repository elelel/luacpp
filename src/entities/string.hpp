#pragma once

namespace lua {

  template <typename T>
  struct char_pointer : public entity<char_pointer<T>, T, const char*> {
    // The interface type should always be the base CRTP class
    typedef entity<char_pointer<T>, T, const char*> interface_type;

    using entity<char_pointer<T>, T, const char*>::entity;
    
    inline bool type_matches() const {
      return this->s_.isstring(this->idx_);
    }
    
    // Non generic behaviour: char pointer array should always be read as const
    inline const char* get_unsafe() const {
      return this->s_.tostring(this->idx_);
    }

    inline void set(T value) const {
      return this->s_.pushstring((T)value);
    }
  };

  template <typename T>
  struct std_string : public entity<std_string<T>, T, T> {
    // The interface type should always be the base CRTP class
    typedef entity<std_string<T>, T, T> interface_type;
    
    using entity<std_string<T>, T, T>::entity;
    
    inline bool type_matches() const {
      return this->s_.isstring(this->idx_);
    }
    
    inline T get_unsafe() const {
      return T(this->s_.tostring(this->idx_));
    }

    inline void set(T value) const {
      return this->s_.pushstring(value.c_str());
    }
  };
  
  template <>
  struct entity_type<char*> {
    typedef char_pointer<char*>::interface_type value;
  };

  template <>
  struct entity_type<const char*> {
    typedef char_pointer<const char*>::interface_type value;
  };

  template <>
  struct entity_type<std::string> {
    typedef std_string<std::string>::interface_type value;
  };

  template <>
  struct entity_type<const std::string> {
    typedef std_string<const std::string>::interface_type value;
  };

  template <size_t N>
  struct entity_type<char[N]> {
    typedef char_pointer<char*>::interface_type value;
  };

  template <size_t N>
  struct entity_type<const char[N]> {
    typedef char_pointer<const char*>::interface_type value;
  };

  template <size_t N>
  struct entity_type<const char(&)[N]> {
    typedef char_pointer<const char*>::interface_type value;
  };
    
}

