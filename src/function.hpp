#pragma once

#define LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)         \
  namespace lua {                                                       \
  namespace function {                                                  \
                                                                        \
  typedef decltype(HANDLER_NAME) NAME##_c_function_type;                \
  struct NAME##_function_descriptor :                                   \
    public detail::function_descriptor<decltype(HANDLER_NAME)> {};      \
                                                                        \
  struct NAME : public detail::function_base<NAME##_c_function_type> {  \
    typedef NAME type;                                                  \
    typedef detail::function_base<NAME##_c_function_type> base_type;    \
                                                                        
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT2(NAME, HANDLER_NAME,\
                                                     ARG1_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT4(NAME, HANDLER_NAME, \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE,         \
                                                     ARG3_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>>, \
                                         entity<type_policy<ARG3_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT5(NAME, HANDLER_NAME, \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE,         \
                                                     ARG3_TYPE,         \
                                                     ARG4_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>>, \
                                         entity<type_policy<ARG3_TYPE>>, \
                                         entity<type_policy<ARG4_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT6(NAME, HANDLER_NAME, \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE,         \
                                                     ARG3_TYPE,         \
                                                     ARG4_TYPE,         \
                                                     ARG5_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>>, \
                                         entity<type_policy<ARG3_TYPE>>, \
                                         entity<type_policy<ARG4_TYPE>>, \
                                         entity<type_policy<ARG5_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT7(NAME, HANDLER_NAME, \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE,         \
                                                     ARG3_TYPE,         \
                                                     ARG4_TYPE,         \
                                                     ARG5_TYPE,         \
                                                     ARG6_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>>, \
                                         entity<type_policy<ARG3_TYPE>>, \
                                         entity<type_policy<ARG4_TYPE>>, \
                                         entity<type_policy<ARG5_TYPE>>, \
                                         entity<type_policy<ARG6_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT8(NAME, HANDLER_NAME, \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE,         \
                                                     ARG3_TYPE,         \
                                                     ARG4_TYPE,         \
                                                     ARG5_TYPE,         \
                                                     ARG6_TYPE,         \
                                                     ARG7_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>>, \
                                         entity<type_policy<ARG3_TYPE>>, \
                                         entity<type_policy<ARG4_TYPE>>, \
                                         entity<type_policy<ARG5_TYPE>>, \
                                         entity<type_policy<ARG6_TYPE>>, \
                                         entity<type_policy<ARG7_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \
  
#define LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT9(NAME,              \
                                                     ARG1_TYPE,         \
                                                     ARG2_TYPE,         \
                                                     ARG3_TYPE,         \
                                                     ARG4_TYPE,         \
                                                     ARG5_TYPE,         \
                                                     ARG6_TYPE,         \
                                                     ARG7_TYPE,         \
                                                     ARG8_TYPE)         \
  static int wrapper_c_function(lua_State* l) {                         \
    return base_type::wrapper_c_function<NAME##_function_descriptor,    \
                                         entity<type_policy<ARG1_TYPE>>, \
                                         entity<type_policy<ARG2_TYPE>>, \
                                         entity<type_policy<ARG3_TYPE>>, \
                                         entity<type_policy<ARG4_TYPE>>, \
                                         entity<type_policy<ARG5_TYPE>>, \
                                         entity<type_policy<ARG6_TYPE>>, \
                                         entity<type_policy<ARG7_TYPE>>, \
                                         entity<type_policy<ARG8_TYPE>> \
                                         >(l, #NAME);                   \
  }                                                                     \


#define LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                         \
                                                                        \
  template <typename client_function_t>                                 \
  static void register_in_lua(const lua::state& s, client_function_t f) { \
    auto std_f = detail::make_std_function<>(f);                        \
    NAME##_function_descriptor::instance().client_c_function = std_f;   \
    base_type::register_in_lua<NAME##_function_descriptor>              \
      (s, #NAME, &wrapper_c_function);                                  \
  }                                                                     \
                                                                        \
  static void unregister_from_lua(const lua::state& s) {                \
    base_type::unregister_from_lua(s, #NAME);                           \
  }                                                                     \
  };                                                                    \
  }                                                                     \
  }                                                                     \

#define LUACPP_STATIC_FUNCTION2(NAME, HANDLER_NAME, ARG1_TYPE)                \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                     \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                       \

#define LUACPP_STATIC_FUNCTION3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE)             \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION4(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE)  \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION5(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION6(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION7(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION8(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION9(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE, ARG8_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE, ARG8_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \

#define LUACPP_STATIC_FUNCTION10(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE, ARG8_TYPE, ARG9_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_BEGIN(NAME, HANDLER_NAME)                             \
  LUACPP_DETAIL_STATIC_FUNCTION_ARG_DEPENDENT3(NAME, HANDLER_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE, ARG8_TYPE, ARG9_TYPE) \
  LUACPP_DETAIL_STATIC_FUNCTION_END(NAME)                               \
          
          
namespace lua {
  namespace function {
    namespace detail {
      template<typename T>
      std::function<typename std::enable_if<std::is_function<T>::value, T>::type>
      make_std_function(T *t) {
        return { t };
      }
      
      template <std::size_t I = 0, typename tuple_t>
      typename std::enable_if<0 == std::tuple_size<tuple_t>::value, std::tuple<>>::type
      inline static make_args_from_stack(const lua::state& s) {
        return std::tuple<>();
      }

      template <std::size_t I = 0, typename tuple_t>
      typename std::enable_if<0 != std::tuple_size<tuple_t>::value, tuple_t>::type 
      inline static make_args_from_stack(const lua::state& s) {
        typedef typename std::tuple_element<0, tuple_t>::type A;
        return std::tuple_cat(std::make_tuple(A(s, I + 1)),
                              make_args_from_stack<I + 1, typename ::lua::tuple_tail_type<tuple_t>::type>(s));
      }

      template <typename F>
      struct function_descriptor {
        inline static function_descriptor& instance() {
          static function_descriptor i;
          return i;
        }
        
        std::function<F> client_c_function;
      private:
        function_descriptor() {};
      };

      template <typename F>
      struct function_base {
        typedef function_base<F> type;
        typedef F* f_type;
        typedef std::function<F> std_function_type;
        typedef typename std_function_type::result_type result_tuple_type;

        static const char* desc_table_name() {
          static const char name[] = "__luacpp_function";
          return name;
        }

        template <typename function_descriptor_t, typename... Args>
        static int wrapper_c_function(lua_State* l, const char* name) {
          ::lua::state s(l);
          s.getglobal(desc_table_name());
          if (!s.isnil(-1)) {
            if (s.istable(-1)) {
              s.push<>(name);
              s.gettable(-2);
              if (!s.isnil(-1)) {
                if (s.islightuserdata(-1)) {
                  auto fd = (function_descriptor_t*)s.at<void*>(-1)();
                  s.pop(2);
                  const auto n_args = s.gettop();
                  const auto n_args_expected = sizeof...(Args);
                  if (n_args == n_args_expected) {
                    typedef std::tuple<Args...> args_tuple_type;
                    auto args = std::tuple_cat(std::tuple<state>(s), 
                                               make_args_from_stack<0, args_tuple_type>(s));
                    auto rslt = apply_tuple(fd->client_c_function, args);
                    s.pop(n_args_expected);
                    s.push_tuple(rslt);
                    return std::tuple_size<typename type::result_tuple_type>::value;
                  } else {
                    throw std::runtime_error("Luaccpp function " + std::string(name) +
                                             " registered as taking " + std::to_string(n_args_expected) +
                                             " arguments, but was called with " + std::to_string(n_args));
                  }
                } else {
                  s.pop(2);
                  throw std::runtime_error("Luacpp function " + std::string(name) +
                                           " pointer in " + desc_table_name() + " table is malformed");
                }
              } else {
                s.pop(2);
                throw std::runtime_error("Luacpp function called, but function descriptor for "
                                         + std::string(name) + " in "
                                         + desc_table_name() + " table is nil");
              }
              s.pop(2);
            } else {
              s.pop(1);
              throw std::runtime_error("Luacpp function called, but " + std::string(desc_table_name()) + " is not a table");
            }
          } else {
            s.pop(1);
            throw std::runtime_error("Luacpp function called, but " + std::string(desc_table_name()) + " Lua global is nil");
          }
        }

        template <typename function_descriptor_t, typename wrapper_c_function_t>
        static void register_in_lua(const lua::state& s, const char* name,
                                    wrapper_c_function_t wrapper_c_function) {
          s.getglobal(desc_table_name());
          if (s.isnil(-1)) {
            // If the function descriptor table does not exit, create it
            s.pop(1);
            s.newtable();
            s.setglobal(desc_table_name());
            s.getglobal(desc_table_name());
          }
          if (s.istable(-1)) {
            s.push<>(name);
            s.pushlightuserdata((void*)&function_descriptor_t::instance());
            s.settable(-3);
            s.pop(1);
            s.register_lua(name, wrapper_c_function);
          } else {
            s.pop(1);
            throw std::runtime_error("Luacpp function register is called for " + std::string(name) +
                                     ", but " + std::string(desc_table_name()) + " is not a table");
          }
        }
        
        static void unregister_from_lua(const lua::state& s, const char* name) {
          s.getglobal(desc_table_name());
          if (!s.isnil(-1)) {
            if (s.istable(-1)) {
              // Remove pointer from descriptor table
              s.push<>(name);
              s.pushnil();
              s.settable(-3);
              s.pop(1);
              // Remove Lua_CFunction registration
              s.pushnil();                                                  
              s.setglobal(name);                                   
            } else {
              throw std::runtime_error("Luacpp function " + std::string(name) + " unregister called, but "
                                       + std::string(desc_table_name()) + " is not a table in Lua globals");
            }
          } else {
            s.pop(1);
            throw std::runtime_error("Luacpp function " + std::string(name) + " unregister called, but "
                                     + std::string(desc_table_name()) + " Lua global is nil");
          }
        }                                                               
      };
    }
  }    

}
