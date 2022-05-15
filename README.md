# stringify

In a generic context you might not know how to turn a type into a string; for example, should you call `std::to_string(x)` or `glm::to_string(x)`? It depends on the actual type!<br/>
*stringify* makes all the efforts it can to find the right function and call it. It does so by relying on C++20's *requires* clause.

```cpp
const int x{3};
const glm::vec2 y{1.f, 7.f};

std::cout << "x: " << Cool::stringify(x) << '\n'
          << "y: " << Cool::stringify(y) << '\n';
```

## How to use

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