# stringify

In a generic context you might not know how to turn a type into a string; for example, should you call `std::to_string(x)` or `glm::to_string(x)`? It depends on the actual type!<br/>
*stringify* makes all the efforts it can to find the right function and call it. (*NB*: It does so by relying on C++20's *requires* clause.)

**Example:**

```cpp
const int x{3};
const glm::vec2 y{1.f, 7.f};

std::cout << "x: " << Cool::stringify(x) << '\n'
          << "y: " << Cool::stringify(y) << '\n';
```

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/stringify)
target_link_libraries(${PROJECT_NAME} PRIVATE stringify::stringify)
```

Then include it as:
```cpp
#include <stringify/stringify.hpp>
```

## How to use

### Free function

You simply need to implement a `to_string(const MyType& x)` fonction for your type `MyType`.<br/>
⚠️ `to_string(const MyType& x)` and `MyType` should be in the same namespace!

```cpp
namespace Some_Random_Namespace {

struct MyCustomType {
    int field;
};

auto to_string(const MyCustomType& x) -> std::string
{
    return "MyCustomType with " + std::to_string(x.field);
}

} // namespace Some_Random_Namespace
```

### Method

You can also implement a `to_string()` method:

```cpp
namespace Some_Random_Namespace {

class MyCustomType {
public:
    auto to_string() const -> std::string
    {
        return "MyCustomType with " + std::to_string(field);
    }

private:
    int field{3};
};

} // namespace Some_Random_Namespace
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
