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
        auto actual = s.toboolean(-1);
        REQUIRE(actual == initial);
      }
    }

  }
}

SCENARIO("Test type adapter with basic types") {
  lua::state s;
  GIVEN("An int") {
    int initial = 0x12345678;
    WHEN("Writing it to stack") {
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
    double initial{1.0/3.0};
    WHEN("Writing it to stack") {
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
   GIVEN("A bool") {
    bool initial = true;
    WHEN("Writing it to stack") {
      s.push<>(initial);
      THEN("It should be on stack as string") {
        REQUIRE(s.isboolean(-1));
        THEN("Read it, the booleands should match") {
          auto actual_unsafe = s.at<decltype(initial)>(-1).get_unsafe();
          REQUIRE(actual_unsafe == initial);
          auto actual_safe = s.at<decltype(initial)>(-1).get();
          REQUIRE(actual_safe == initial);
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

SCENARIO("Table test") {
  GIVEN("Lua state and custom table class") {
    lua::state s;

    WHEN("Creating a raw table") {
      s.newtable();
      THEN("It shoule be on stack as table") {
        REQUIRE(s.istable(-1));
        WHEN("Creating my_table struct and setting value") {
          // Declare a local table struct called my_table
          LUACPP_STATIC_TABLE_BEGIN(my_table);
          LUACPP_TABLE_FIELD_WITH_STR_KEY(name, std::string, std::string);
          LUACPP_TABLE_FIELD_WITH_STR_KEY(ticker, const char*, std::string);
          LUACPP_TABLE_FIELD_WITH_STR_KEY(rating, const char*, const char*);
          LUACPP_TABLE_FIELD_WITH_STR_KEY(price, std::string, double);
          LUACPP_TABLE_FIELD_WITH_INT_KEY(1929, int, const char*);
          LUACPP_TABLE_FIELD_WITH_STR_KEY(exchange_code, std::string, std::string);
          LUACPP_STATIC_TABLE_END();
          // Instantiate my_table
          my_table t(s, -1);
          const std::string initial_name = "Test stock exchange instrument";
          const std::string initial_ticker = "TICKR";
          const char* initial_rating = "B++";
          double initial_price{1.2345};
          const char* initial_1929 = "The year of great market crash";
          const std::string initial_exchange_code = "NYSE";
          // Test setters
          t.name.set(initial_name);
          t.ticker.set(initial_ticker);
          t.rating.set(initial_rating);
          t.price.set(initial_price);
          t.integral_1929.set(initial_1929);
          // Test operator=() overloads
          t.exchange_code = initial_exchange_code;
          THEN("Try to get it") {
            // Test getters
            std::string actual_name = t.name.get();
            std::string actual_ticker = t.ticker.get();
            const char* actual_rating = t.rating.get();
            const char* actual_1929 = t.integral_1929.get();
            double actual_price = t.price.get();
            // Test operator()() overlaods
            std::string actual_exchange_code = t.exchange_code();
            
            REQUIRE(actual_name == initial_name);
            REQUIRE(actual_ticker == initial_ticker);
            REQUIRE(strcmp(actual_rating, initial_rating) == 0);
            REQUIRE(actual_price == initial_price);
            REQUIRE(strcmp(actual_1929, initial_1929) == 0);
            REQUIRE(actual_exchange_code == initial_exchange_code);
          }
        }
      }
    }
    
  }
}
