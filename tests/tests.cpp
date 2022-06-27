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

class TypeWithMethod {
public:
    auto to_string() const -> std::string
    {
        return "TypeWithMethod";
    }
};

} // namespace Some_Random_Namespace

class TypeWithMethod {
public:
    auto to_string() const -> std::string
    {
        return "TypeWithMethod";
    }
};

struct TypeWithoutToString {
};

template<typename T>
auto fails_to_stringify(const T& value) -> bool
{
    return Cool::stringify(value).find("ERROR") != std::string::npos;
}

TEST_CASE("stringify a custom type from an unknown namespace")
{
    CHECK(Cool::stringify(Some_Random_Namespace::MyCustomType{5}) == "MyCustomType with 5");
    CHECK(Cool::stringify(Some_Random_Namespace::MyCustomType{12}) == "MyCustomType with 12");
}

TEST_CASE("stringify with a method")
{
    CHECK(Cool::stringify(TypeWithMethod{}) == "TypeWithMethod");
    CHECK(Cool::stringify(Some_Random_Namespace::TypeWithMethod{}) == "TypeWithMethod");
}

TEST_CASE("stringify a primitive type")
{
    CHECK(Cool::stringify(3) == "3");
    CHECK(Cool::stringify(7) == "7");
}

#include <optional>
TEST_CASE("stringify an optional-like type")
{
    CHECK(Cool::stringify((int*)nullptr) == "None");
    CHECK(Cool::stringify((std::optional<bool>)std::nullopt) == "None");
    CHECK(Cool::stringify(std::make_optional(Some_Random_Namespace::MyCustomType{5})) == "Some: MyCustomType with 5");
    CHECK(fails_to_stringify(std::make_optional(TypeWithoutToString{})));
    {
        TypeWithoutToString fail;
        CHECK(fails_to_stringify(&fail));
    }
}