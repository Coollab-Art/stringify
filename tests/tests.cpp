#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <stringify/stringify.hpp>

namespace Some_Random_Namespace {

struct MyCustomType {
    int x;
};

auto to_string(const MyCustomType& x) -> std::string
{
    return "MyCustomType with " + std::to_string(x.x);
}

} // namespace Some_Random_Namespace

TEST_CASE("stringify a custom type from an unknown namespace")
{
    CHECK(Cool::stringify(Some_Random_Namespace::MyCustomType{5})
          == "MyCustomType with 5");
    CHECK(Cool::stringify(Some_Random_Namespace::MyCustomType{12})
          == "MyCustomType with 12");
}

TEST_CASE("stringify a primitive type")
{
    CHECK(Cool::stringify(3)
          == "3");
    CHECK(Cool::stringify(7)
          == "7");
}