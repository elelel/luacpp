#pragma once

#include <optional>

namespace lua {
  namespace detail {
    template <typename T>
    struct optional {
      using write_type = std::optional<T>;
      using read_type = std::optional<typename std::remove_reference<T>::type>;
      using read_value_type = T;
      using value_policy = type_policy<read_value_type>;

      inline static bool type_matches(::lua::state s, int idx) {
        return s.isnil(idx) || value_policy::type_matches(s, idx);
      }

      inline static read_type get_unsafe(::lua::state s, int idx) {
        if (s.isnil(idx)) return read_type();
        else return read_type(value_policy::get_unsafe(s, idx));
      }

      template <typename F>
      inline static void apply_unsafe(::lua::state s, int idx, F f) {
        value_policy::apply_unsafe(s, idx);
      }

      inline static void set(::lua::state s, int idx, write_type value) {
        if (value) {
          value_policy::set(s, idx, *value);
        } else {
          s.pushnil();
          if (idx != 0) s.replace(idx - 1);
        }
      }
    };

  }
}
