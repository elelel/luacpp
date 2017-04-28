#pragma once

#include "declarations.hpp"

namespace lua {
  
  /* Generic stack entity.
     Type policies should follow the concept::

    All reading functions should correct the stack on return

    // Checks if the value on stack looks like the right type
    inline static bool type_matches(::lua::state s, int idx)
    // Reads the value on stack without the check,
    // the return value is copy-constructed
    inline static T get_unsafe(::lua::state s, int idx);
    // Places the value on the stack if needed, and calls function f(const lua::state&, idx),
    // no copying should occur in the process
    template <typename F>
    inline static void apply_unsafe(::lua::state s, int idx, F f, args...);
    // Puts the value on stack
    inline static void set(::lua::state s, int idx, T value, args...);
   */

  template <typename policy_t>
  struct entity {
    typedef typename policy_t::read_type read_type;
    typedef typename policy_t::write_type write_type;

    entity(const ::lua::state& s, const int idx) :
      s_(s),
      idx_(idx) {
    }

    // -- Forwarding to policy -
    template <typename... Args>
    inline bool type_matches(Args&&... args) const {
      return policy_t::type_matches(s_, idx_, args...);
    }

    template <typename... Args>
    inline read_type get_unsafe(Args&&... args) const {
      return policy_t::get_unsafe(s_, idx_, args...);
    }

    template <typename... Args>
    inline void set(write_type value, Args&&... args) const {
      policy_t::set(s_, idx_, value, args...);
    }

    template <typename F, typename... Args>
    inline void apply_unsafe(F f, Args&&... args) const {
      policy_t::apply_unsafe(s_, idx_, f, args...);
    }

    // -- Syntactic suger --
    
    template <typename... Args>
    inline read_type get(Args... args) const {
      if (type_matches(args...)) {
        return get_unsafe(args...);
      } else {
        throw std::runtime_error(make_typecheck_error_msg("entity get"));
      }
    }

    template <typename F, typename... Args>
    inline read_type apply(F f, Args... args) const {
      if (type_matches(args...)) {
        return apply_unsafe(args...);
      } else {
        throw std::runtime_error(make_typecheck_error_msg("entity apply"));
      }
    }
    
    template <typename... Args>
    inline read_type operator()(Args... args) const {
      return get(args...);
    }

    // Note that operator= sets the entity's content, does not assign one entity to another
    inline void operator=(write_type value) const {
      set(value);
    }

    // Accessors
    const lua::state& lua_state() const {
      return s_;
    }

    const int& index() const {
      return idx_;
    }
  protected:
    const lua::state s_;
    const int idx_{0};

  private:
    std::string make_typecheck_error_msg(const std::string& operation) const {
      auto actual_type_pc = s_.typename_lua(s_.type_lua(idx_));
      auto actual_content_pc = s_.tostring(idx_);
      std::string actual_type;
      std::string actual_content;
      if (actual_type_pc == nullptr) 
        actual_type = "<Oops, got null from Lua when tried to get actual type name string>";
      else
        actual_type = actual_type_pc;
      if (actual_content_pc == nullptr) 
        actual_content = "<Oops, got null from Lua when tried to get actual content as string>";
      else
        actual_content = actual_content_pc;
        
      return "Luacpp " + operation + ": typecheck failed (Lua type at stack index "
        + std::to_string(idx_) + " is " + actual_type + "; content as string: " + actual_content + ")";
    }
  };

}
