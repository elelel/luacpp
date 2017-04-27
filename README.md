# LuaCpp - C++ wrapper library for lua C interface #

## Overview ##

LuaCpp is (yet another) C++11 header-only Lua interface library. 
The main difference from other C++ wrapper libraries is that it's
goal is to bring type-safety and interaction with third-party Lua
APIs.

The library was written for personal projects, so not all of C interface
is wrapped. If you use it and find something missing, don't hesitate
to open an issue.

## Adding to project ##
Clone the repo and add *include* directory to include directories path
of your project.
C Lua library's header files should be accessible through project's include
dirs as well. Link the native C Lua library to your project as usual if needed.

## Example ##

See [tests](test/luacpp_test.cpp) for more thorough examples.
For a project using this library see [qluacpp](https://github.com/elelel/qluacpp)
and [qluacpp-tutorial](https://github.com/elelel/qluacpp-tutorial)

### Basic operations ###

```c++

#include <cassert>
#include <string>

#include <luacpp/luacpp>

void main(int main(int argc, char *argv[]) {
 lua::state s;
 std::string str("Some string");
 char pchar[] = "Some string";
 // Push the variable to stack
 // The inferred template parameter is used by ::lua::type_policy<T> class
 // to get the methods that write/read values of T type
 s.push<>(str);
 // The last value on stack should be string
 // isstring is direct mapping of lua_isstring C API with lua state argument
 // replaced by *this making it a C++ method call on state
 assert(s.isstring(-1));
 // Read std::string from stack. Template parameter <std::string> is again used
 // to get type policy for reading/writing values of that type.
 // Argument -1 is the Lua stack index. Method get() is used to unpack
 // lua entity as std::string
 auto string_read = str.at<std::string>(-1).get();
 // Read the same stack location as const char*
 // Here operator() is used instead of get() (syntactic sugar
 auto string_read = str.at<char*>(-1)();  
 assert(str == string_read);
}
```

### Declaring and using a static table ###

At root namespace:

```c++
#include <luacpp/luacpp>

namespace myproject {
  namespace table {
    LUACPP_STATIC_TABLE_BEGIN(sales)
    LUACPP_TABLE_FIELD(date_str, std::string)
    LUACPP_TABLE_FIELD(year, unsigned int)
    LUACPP_TABLE_FIELD(month, unsigned int)
    LUACPP_TABLE_FIELD(day, unsigned int)
    LUACPP_TABLE_FIELD(amount, double)
    LUACPP_STATIC_TABLE_END()
  }
}
// Macro to declare policy for converting the type to/from lua stack contents
LUACPP_STATIC_TABLE_TYPE_POLICY(::myproject::table::sales)
```

Later it can be used like this:

```c++
  // Assuming s is ::lua::state created or acquired earlier
  myproject::table::sales sales(s, -1);  // Create sales table from stack at stack index -1
  sales.date_str = "New Year's Eve";
  sales.year = 2017;
  sales.month.set(12);
  sales.day = 31;
  sales.amount = 123.45;
  assert(sales.date_str() == "New Year's Eve");
  assert(sales.month() == 12);
  assert(sales.day.get() == 31);
  assert(sales.amount() == double{123.45});
  
```

### Getting C++ functions to Lua and calling them ###
At root namespace:

```c++
namespace my_project {
// Same function at a higher level of abstraction
static std::tuple<std::string, int> cpp_function(::lua::state st,
                                                      ::lua::entity<::lua::type_policy<std::string>> s,
                                               ::lua::entity<::lua::type_policy<int>> i) {
  auto str = s();
  auto num = i();
  std::string rslt1 = str + " - length " + std::to_string(str.size());
  int rslt2 = num + str.size();
  // Custom functions should always return a tuple
  return std::make_tuple(rslt1, rslt2);
}
}
// Declare cpp_function class in ::lua::function namespace. 4 in macro's name is
// the total number of arguments passed to the macro
LUACPP_STATIC_FUNCTION4(cpp_function,   // How the function will be called in Lua
                        ::my_roject::cpp_function,  // What function in C++ should handle the call
                        std::string, int  // Arguments that the handler will received wrapped in Lua entities
                        )
```

Later it can be used like this:

```c++
// After the following line our function will be callable from Lua
::lua::function::cpp_function().register_in_lua(s, cpp_function);b
// Call the function through Lua
auto rslt = s.call<result_type>("cpp_function", std::string("Test"), 123);

```

## Design ##

One of the most important challenges when interfacing with Lua API exported by a third-party application
is type safety. The main purpose of this library is to interface with Lua in a type-safe and type-extensible manner.
The library is architectured as set of generic operations funnel data through [type adapters](src/types) .
These adapters define how the data is written, read, and checked for type compliance on Lua stack.
You can write your own adapter by specializing lua::type_adapter class template, see [boolean specialization](src/types/boolean.hpp) for a simple example.

C macros are used heavily, unfortunutaly there's no other way of working with C++ on token level.

## License ##
MIT, like Lua

