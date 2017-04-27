#include <catch.hpp>

#include <luacpp/luacpp>

SCENARIO("Test state (only native calls)") {
  GIVEN("New Lua state") {
    lua::state s;
    WHEN("Pushing a number") {
      lua_Number initial = 0x12345678;
      s.pushnumber(initial);
      THEN("Number on stack should match the number pushed") {
        REQUIRE(s.isnumber(-1));
        auto actual = s.tonumber(-1);
        REQUIRE(actual == initial);
        WHEN("Pushing another number") {
          lua_Number another_initial = 0x1ABCDEF9;
          s.pushnumber(another_initial);
          THEN("The numbers on stack should match") {
            REQUIRE(s.isnumber(-1));
            auto actual = s.tonumber(-1);
            REQUIRE(actual == another_initial);
            REQUIRE(s.isnumber(-2));
            actual = s.tonumber(-2);
            REQUIRE(actual == initial);

            WHEN("Poping a number") {
              s.pop(1);
              THEN("Only the first number should remain") {
                REQUIRE(s.isnumber(-1));
                auto actual = s.tonumber(-1);
                REQUIRE(actual == initial);
              }
            }
          }
        }
      }
    }
    WHEN("Pushing a string") {
      const char * initial = "Test string";
      s.pushstring(initial);
      THEN("String on stack should match the string pushed") {
        REQUIRE(s.isstring(-1));
        auto actual = s.tostring(-1);
        REQUIRE(strcmp(actual, initial) == 0);
      }
    }
    WHEN("Pushing a boolean") {
      bool initial = true;
      s.pushboolean(initial);
      THEN("Boolean on stack should match the boolean pushed") {
        REQUIRE(s.isboolean(-1));
        auto actual = (bool)s.toboolean(-1);
        REQUIRE(actual == initial);
      }
    }

  }
}

SCENARIO("Test basic type entities") {
  lua::state s;
  GIVEN("A bool") {
    WHEN("is pushed as literal") {
      s.push<>(true);
      THEN("The last item on stack should be boolean") {
        REQUIRE(s.isboolean(-1));
      }
    }
    WHEN("is pushed as named param") {
      bool initial = true;
      s.push<>(initial);
      THEN("The last item on stack should be boolean") {
        REQUIRE(s.isboolean(-1));
        THEN("Read it, the booleans should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(actual_unsafe == initial);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(actual_safe == initial);
        }
      }
    }
  }
  
  GIVEN("An int") {
    WHEN("is pushed as literal") {
      s.push<>(123);
      THEN("The last item on stack should be number") {
        REQUIRE(s.isnumber(-1));
      }
    }
    WHEN("is pushed as named param") {
      int initial = 0x12345678;
      s.push<>(initial);
      THEN("It should be on stack as number") {
        REQUIRE(s.isnumber(-1));
        THEN("Read it, the numbers should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(actual_unsafe == initial);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(actual_safe == initial);
        }
      }
    }
  }
  
  GIVEN("A double") {
    WHEN("is pushed as literal") {
      s.push<>(123.45);
      THEN("The last item on stack should be number") {
        REQUIRE(s.isnumber(-1));
      }
    }
    WHEN("Writing it to stack") {
      double initial{1.0/3.0};
      s.push<>(initial);
      THEN("The last item on stack should be number") {
        REQUIRE(s.isnumber(-1));
        THEN("Read it, the numbers should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(actual_unsafe == initial);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(actual_safe == initial);
        }
      }
    }
  }
  
  GIVEN("A char* literal") {
    WHEN("Writing it to stack") {
      s.push<>("Testing...");
      THEN("It should be on stack as string") {
        REQUIRE(s.isstring(-1));
        THEN("Read it, the strings should match") {
          auto actual_unsafe = s.at<decltype("Testing...")>(-1).get_unsafe();
          REQUIRE(strcmp(actual_unsafe, "Testing...") == 0);
          auto actual_safe = s.at<decltype("Testing...")>(-1).get();
          REQUIRE(strcmp(actual_safe, "Testing...") == 0);
        }
      }
    }
  }

  GIVEN("A char[]") {
    char initial[] = "Testing...";
    WHEN("Writing it to stack") {
      s.push<>(initial);
      THEN("It should be on stack as string") {
        REQUIRE(s.isstring(-1));
        THEN("Read it, the strings should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(strcmp(actual_unsafe, initial) == 0);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(strcmp(actual_safe, initial) == 0);
        }
      }
    }
  }

  GIVEN("A const char[]") {
    const char initial[] = "Testing...";
    WHEN("Writing it to stack") {
      s.push<>(initial);
      THEN("It should be on stack as string") {
        REQUIRE(s.isstring(-1));
        THEN("Read it, the strings should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(strcmp(actual_unsafe, initial) == 0);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(strcmp(actual_safe, initial) == 0);
        }
      }
    }
  }

  GIVEN("A char*") {
    char initial_array[] = "Testing...";
    char* initial = initial_array;
    WHEN("Writing it to stack") {
      s.push<>(initial);
      THEN("It should be on stack as string") {
        REQUIRE(s.isstring(-1));
        THEN("Read it, the strings should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(strcmp(actual_unsafe, initial) == 0);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(strcmp(actual_safe, initial) == 0);
        }
      }
    }
  }
  
  GIVEN("A const char*") {
    const char initial_array[] = "Testing...";
    const char* initial = initial_array;
    WHEN("Writing it to stack") {
      s.push<>(initial);
      THEN("It should be on stack as string") {
        REQUIRE(s.isstring(-1));
        THEN("Read it, the strings should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(strcmp(actual_unsafe, initial) == 0);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(strcmp(actual_safe, initial) == 0);
        }
      }
    }
  }

  GIVEN("An std::string") {
    std::string initial{"Testing"};
    WHEN("Writing it to stack") {
      s.push<>(initial);
      THEN("It should be on stack as string") {
        REQUIRE(s.isstring(-1));
        THEN("Read it, the strings should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(actual_unsafe == initial);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(actual_safe == initial);
        }
      }
    }
  }
}

namespace bogus_namespace_to_test_macros {
  // Create table struct
  // Forward declaration for recursion field
  struct my_table;
  // Declare the struct called my_table
  LUACPP_STATIC_TABLE_BEGIN(my_table);
  LUACPP_TABLE_FIELD_STR_KEY(name, std::string, std::string);
  // LUACPP_TABLE_FIELD is an alias to LUACPP_TABLE_FIELD_STR_KEY with const char* key
  LUACPP_TABLE_FIELD(ticker, std::string);
  LUACPP_TABLE_FIELD_STR_KEY(rating, const char*, const char*);
  LUACPP_TABLE_FIELD_STR_KEY(price, std::string, double);
  LUACPP_TABLE_FIELD_STR_KEY(exchange_code, std::string, std::string);
  LUACPP_TABLE_FIELD(table_like_myself, my_table);
  LUACPP_STATIC_TABLE_END();
}

// This HAS to be invoked from a .hpp root
LUACPP_STATIC_TABLE_TYPE_POLICY(bogus_namespace_to_test_macros::my_table)

SCENARIO("Table test") {
  GIVEN("Lua state and custom table class") {
    lua::state s;

    WHEN("Creating a raw table") {
      s.newtable();
      THEN("It shoule be on stack as table") {
        REQUIRE(s.istable(-1));
        WHEN("Creating my_table struct and setting value") {
          // Instantiate my_table
          bogus_namespace_to_test_macros::my_table t(s, -1);
          WHEN("Setting table's fields") {
            const std::string initial_name = "Test stock exchange instrument";
            const std::string initial_ticker = "TICKR";
            const char* initial_rating = "B++";
            double initial_price{1.2345};
            const std::string initial_exchange_code = "NYSE";
            // Test setters
            t.name.set(initial_name);
            t.ticker.set(initial_ticker);
            t.rating.set(initial_rating);
            t.price.set(initial_price);
            // Test operator=() overloads
            t.exchange_code = initial_exchange_code;
            WHEN("Reading table's fields") {
              // Test getters
              std::string actual_name = t.name.get();
              std::string actual_ticker = t.ticker.get();
              const char* actual_rating = t.rating.get();
              double actual_price = t.price.get();
              // Test operator()() overlaods
              std::string actual_exchange_code = t.exchange_code();
            
              THEN("Try to get it") {
                REQUIRE(actual_name == initial_name);
                REQUIRE(actual_ticker == initial_ticker);
                REQUIRE(strcmp(actual_rating, initial_rating) == 0);
                REQUIRE(actual_price == initial_price);
                REQUIRE(actual_exchange_code == initial_exchange_code);
              }
            }
            WHEN("Accessing another table within the table") {
              auto initial_name = "That is a name in inner table";
              t.table_like_myself().name = initial_name;
              auto actual_name = t.table_like_myself().name();
              REQUIRE(actual_name == initial_name);
              auto initial_price{765.32};
              t.table_like_myself().price = initial_price;
              auto actual_price = t.table_like_myself().price();
              REQUIRE(actual_price == initial_price);
            }
          }
        }
      }
    }
  }
}


// Raw C function: takes a string and a number, returns modified string an modified number
static int test_c_function(lua_State* l) {
  lua::state s(l);
  const int n_args = s.gettop();
  if (n_args == 2) {
    // First argument has to be string
    auto str = s.at<std::string>(1).get();
    // Second argument has to be number
    auto num = s.at<int>(2).get();
    s.pop(n_args);
    std::string rslt1 = str + " - length " + std::to_string(str.size());
    s.push<>(rslt1);
    int rslt2 = num + str.size();
    s.push<>(rslt2);

    return 2;
  } else {
    throw std::runtime_error("Test C function expects 2 arguments, but received " + std::to_string(n_args));
  }
}

// Same function at a higher level of abstraction
static std::tuple<std::string, int> test_cpp_function(::lua::state st,
                                                      ::lua::entity<::lua::type_policy<std::string>> s,
                                               ::lua::entity<::lua::type_policy<int>> i) {
  auto str = s();
  auto num = i();
  std::string rslt1 = str + " - length " + std::to_string(str.size());
  int rslt2 = num + str.size();
  return std::make_tuple(rslt1, rslt2);
}

// Declare test_cpp_function class in ::lua::function namespace
LUACPP_STATIC_FUNCTION3(test_cpp_function, std::string, int)

SCENARIO("Functions test") {
  GIVEN("Lua state") {
    lua::state s;
    typedef std::tuple<std::string, int> result_type;
    WHEN("Register raw c function") {
      s.register_lua("test_c_function", &test_c_function);

      THEN("Call, get and check results") {
        auto rslt = s.call<result_type>("test_c_function", std::string("Test"), 123);
        auto& actual_str = std::get<0>(rslt);
        auto& actual_num = std::get<1>(rslt);
        REQUIRE(actual_str == std::string("Test - length 4"));
        REQUIRE(actual_num == 127);
      }
      THEN("Call, apply lambda and check results") {
        std::string actual_str;
        int actual_num{0};
        const int n_result = 2;
        // Version with caller clean stack responsibility
        auto callback = [&actual_str, &actual_num] (const lua::state& s) {
          // First argument has to be string
          auto actual_str = s.at<std::string>(1).get();
          // Second argument has to be number
          auto actual_num = s.at<int>(0).get();
          s.pop(n_result);
          return 0; // We've balanced the stack, so inform that there're 0 items are to be corrected
        };
        s.call_and_apply<>(callback, 2, "test_c_function", std::string("Test"), 123);
      }
    }
    WHEN("Register cpp function") {
      ::lua::function::test_cpp_function().register_in_lua(s, test_cpp_function);
      THEN("Address for the function stored in Lua should match the real one") {
        s.getglobal(::lua::function::test_cpp_function().desc_table_name());
        bool is_desc_table_nil = s.isnil(-1);
        REQUIRE(!is_desc_table_nil);
        bool is_desc_table_table = s.istable(-1);
        REQUIRE(is_desc_table_table);
        s.push<>("test_cpp_function");
        s.gettable(-2);
        bool is_pfun_lightuserdata = s.islightuserdata(-1);
        REQUIRE(is_pfun_lightuserdata);
        auto fd = (::lua::function::test_cpp_function_function_descriptor*)s.at<void*>(-1)();
      }
      THEN("Call the cpp function") {
        auto rslt = s.call<result_type>("test_cpp_function", std::string("Test"), 123);
        auto& actual_str = std::get<0>(rslt);
        auto& actual_num = std::get<1>(rslt);
        REQUIRE(actual_str == std::string("Test - length 4"));
        REQUIRE(actual_num == 127);
      }
      THEN("Unregister function") {
        ::lua::function::test_cpp_function().unregister_from_lua(s);
      }
    }
  }

}
