#pragma once

namespace lua {
 
  template <typename T>
  struct vector_element {
    typedef vector_element<T> type;
    typedef T value_type;
    
    vector_element(const lua::state s, const int idx, const int i) :
      s_(s),
      idx_(idx),
      i_(i) {
      if (!s_.istable(idx_))
        throw std::runtime_error("Luacpp error: can't construct lua vector element from non-table stack value");
    }

    vector_element(const type& other) :
      s_(other.s_),
      idx_(other.idx_),
      i_(other.i_) {
    }

    vector_element(type&& other) :
      s_(std::move(other.s_)),
      idx_(std::move(other.idx_)),
      i_(other.i_) {
    }

    void swap(type& other) {
      std::swap(s_, other.s_);
      std::swap(idx_, other.idx_);
      std::swap(i_, other.i_);
    }
    
    value_type get() const {
      s_.rawgeti(idx_, i_);
      auto rslt = entity<type_policy<value_type>>(s_, -1)();
      s_.pop();
      return rslt;
    }

    value_type operator()() const {
      return get();
    }

    template <typename F, typename... Args>
    void apply(F f, Args... args) const {
      s_.rawgeti(idx_, i_);
      f(s_, -1);
      s_.pop();
    }

    void set(value_type value) const {
      s_.push<>(value);
      s_.rawseti(-2 , i_);
    }

    void operator=(value_type value) const {
      set(value);
    }

    void operator=(value_type value) {
      set(value);
    }

  private:
    const lua::state s_;
    const int idx_{0};
    const int i_;  // Index in vector in oligophrenic format
  };

  template <typename T>
  struct vector {
    typedef vector<T> type;
    typedef T value_type;
    typedef vector_element<T> element_type;
        
    vector(const lua::state& s, const int idx) :
      s_(s),
      idx_(idx) {
      if (s_.isnil(idx)) {
        s_.newtable();
        s_.replace(idx - 1);
      } else {
        if (!s_.istable(idx_)) throw std::runtime_error("Luacpp error: can't construct lua vector from non-table stack value");
      }
    }

    ~vector() {
      s_.pop(n_pop_);
    }

    size_t size() const {
      return s_.objlen(idx_);
    }

    element_type at(const int i) const {
      return element_type(s_, idx_, i + 1);
    }

    element_type operator[](const int i) const {
      return at(i);
    }

    void push_back(const value_type& value) const {
      int i = s_.objlen(idx_);
      i += 1; // Adjust for oligophrenic indexing
      s_.push<>(value);
      s_.rawseti(idx_ - 1, i);
    }

    void pop() const {
      int i = s_.objlen(idx_);
      s_.pushnil();
      s_.rawseti(idx_ - 1, i);
    }
    
    void balance_stack() {
      s_.pop(n_pop_);
      n_pop_ = 0;
    }
  private:
    lua::state s_;
    int idx_{0};

    mutable int n_pop_{0};
  };
}
