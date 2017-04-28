#pragma once

namespace lua {

  /*

vector element - type_policy<vector_element>, reading: entity<T>, writing T, keeps i in state
vector - returns elements, has type_policy<vector>

   */

 
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
    
    value_type get() {
      s_.rawgeti(idx_, i_);
      auto rslt = entity<type_policy<value_type>>(s_, idx_)();
      s_.pop();
      return rslt;
    }

    void set(value_type value) {
      // Assume the table is on the top
      s_.pushnil();
      entity<type_policy<value_type>>(s_, idx_) = value;
      s_.rawseti(idx_, i_);
    }

    void remove() {
      s_.pushnil();
      s_.rawseti(idx_, i_);
    }

    void operator=(value_type value) {
      set(value);
    }

  private:
    const lua::state s_;
    const int idx_{0};
    const int i_;
  };
  
  
  template <typename T>
  struct vector {
    typedef vector<T> type;
    typedef vector_element<T> value_type;
        
    vector(const lua::state& s, const int idx) :
      s_(s),
      idx_(idx) {
      if (!s_.istable(idx_))
        throw std::runtime_error("Luacpp error: can't construct lua vector from non-table stack value");
    }

    ~vector() {
      s_.pop(n_pop_);
    }

    size_t size() const {
      return s_.objlen(idx_);
    }

    vector_element<T> at(const int i) const {
      return vector_element<T>(s_, idx_, i);
    }

    vector_element<T> operator[](const int i) const {
      return at(i);
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
