# LuaCpp - C++ wrapper library for lua C interface #

## Overview ##

LuaCpp is (yet another) C++11 header-only Lua interface library. 
The main difference from other C++ wrapper libraries is that it's
primal goal is to bring type-safety.

The library was written for personal projects, so not all C interface
is wrapped. If you use it and find something missing, don't hesitate
to open an issue.

## Adding to project ##
Clone the repo and add *include* directory to include directories path
of your project.
C Lua library's header files should be accessible through project's include
dirs as well. Link the native C Lua library to your project as usual if needed.

## Example ##

```c++
#include <cassert>
#include <string>

#include <luacpp/luacpp>

void main(int main(int argc, char *argv[]) {
 lua::state s;
 std::string str("Some string");
 char pchar[] = "Some string";
 s.push<>(str);   // Push the variable to stack 
 assert(s.isstring(-1));  // The last value on stack should be string
 auto string_read = str.at<std::string>(-1).get();  // Read std::string from stack
 auto string_read = str.at<char*>(-1).get();  // Read the same stack location as const char*
 assert(str == string_read);
 
 // Declare my_table structure for table accessor class
 LUACPP_STATIC_TABLE_BEGIN(my_table);
 LUACPP_TABLE_FIELD(name, std::string, std::string);
 LUACPP_TABLE_FIELD(price, std::string, double);
 LUACPP_STATIC_TABLE_END();
 // Create my_table object
 s.newtable(-1);
 my_table(s, -1);
 t.name = "Gold";
 t.price = 1023.12;
 // t.price = "string"; // This will file at compile time
 assert(t.name() == "Gold");
 assert(t.price() == 1023.12);
}
```

See [tests](test/luacpp_test.cpp) for more examples

## Design ##

One of the most important challenges when interfacing with Lua API exported by a third-party application
is type safety. The main purpose of this library is to interface with Lua in a type-safe and type-extensible manner.
The library is architectured as set of generic operations funnel data through [type adapters](src/types) .
These adapters define how the data is written, read, and checked for type compliance on Lua stack.
You can write your own adapter by specializing lua::type_adapter class template, see [boolean specialization](src/types/boolean.hpp) for a simple example.

## License ##
MIT, like Lua

