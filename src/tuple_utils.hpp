#pragma once

namespace lua {
  template <typename... X>
  struct tuple_tail_type;

  template <typename head_t>
  struct tuple_tail_type<std::tuple<head_t>> {
    typedef std::tuple<> type;
  };

  template <typename head_t, typename... tail_t>
  struct tuple_tail_type<std::tuple<head_t, tail_t...> > {
    typedef std::tuple<tail_t...> type;
  };
} 
