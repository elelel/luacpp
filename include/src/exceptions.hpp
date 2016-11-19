#pragma once

#include <stdexcept>

namespace lua {
  namespace error {
    struct string_expected : public std::runtime_error {
      string_expected(const std::string& where,
                      const std::string& actual) :
        runtime_error("Number expected in " + where + ", got " + actual) {
      }
    };
    
    struct number_expected : public std::runtime_error {
      number_expected(const std::string& where,
                      const std::string& actual) :
        runtime_error("Number expected in " + where + ", got " + actual) {
      }
    };

    struct boolean_expected : public std::runtime_error {
      boolean_expected(const std::string& where,
                       const std::string& actual) :
        runtime_error("Boolean expected in " + where + ", got " + actual) {
      }
    };

    struct function_expected : public std::runtime_error {
      function_expected(const std::string& where,
                        const std::string& actual) :
        runtime_error("Function expected in " + where + ", got " + actual) {
      }
    };

    struct table_expected : public std::runtime_error {
      table_expected(const std::string& where,
                     const std::string& actual) :
        runtime_error("Table expected in " + where + ", got " + actual) {
      }
    };
    
    struct call_failed : public std::runtime_error {
      call_failed(const std::string& where) :
        runtime_error("lua_call failed in " + where) {
      }
    };
  }
}
