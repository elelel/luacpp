#pragma once

#include "state_base.hpp"

namespace lua {
  /* Generic stack entity.
     Specializations should follow the concept::

    Template parameters:
     derived_t - specialization class
     T - C++ type (for type dispatch)
     read_t - value return type, may be different from T

    All functions should correct the stack on return

    // The interface type should always be the base CRTP class and thus type
    // should be exported in specialization class
    typedef entity<specialized_entity<T>, T> interface_type;

    // Checks if the value on stack looks like the right type
    inline bool type_matches() const;  

    // Reads the value on stack without the check
    // The return value is copy-constructed
    inline read_type get_unsafe() const;
    // Puts the value on the stack, and calls function f(const lua::state&)
    // no copying should occur in the function
    inline void apply(std::function<void(const lua::state&>);
    // Sets the stack to the value
    inline void set(T value) const; 
   */

  template <typename derived_t, typename T, typename read_t>
  struct entity {
    typedef T value_type;
    typedef entity<derived_t, T, read_t> type;
    
    entity(const lua::state_base& s, const int idx) :
      s_(s),
      idx_(idx) {
    }
    
    inline bool type_matches() const {
      return static_cast<const derived_t*>(this)->type_matches();
    }
    
    inline read_t get_unsafe() const {
      return static_cast<const derived_t*>(this)->get_unsafe();
    }
    
    inline read_t get() const {
      if (type_matches()) {
        return get_unsafe();
      } else {
        throw std::runtime_error("Luacpp safe entity get() failed: value at stack does not match the static type");
      }
    }
    
    inline void set(T value) const {
      static_cast<const derived_t*>(this)->set(value);
      if (idx_ != 0) s_.replace(idx_);
    }

    // Note that operator= sets the entity's content, does not assign one entity to another
    inline void operator=(T value) const {
      set(value);
    }
    
    inline value_type operator()() const {
      return get();
    }
    
  protected:
    const lua::state_base s_;
    const int idx_;
  };
  
  /* Type adapter, maps C++ type to corresponding entity type.
     Specializations should export entity interface type as "value" type member:
     typedef specialized_entity<cpp_type>::interface_type value;
  */
  template <typename T>
  struct entity_type;
    

}

