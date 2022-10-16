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

template<typename T>
auto successfully_stringifies(const T& value) -> bool
{
    return !fails_to_stringify<T>(value);
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
    CHECK(Cool::stringify(std::make_optional(std::make_optional(5))) == "Some: Some: 5");
    CHECK(fails_to_stringify(std::make_optional(TypeWithoutToString{})));
    {
        TypeWithoutToString fail;
        CHECK(fails_to_stringify(&fail));
    }
}

#include <list>
#include <vector>
TEST_CASE("stringify a range")
{
    CHECK(Cool::stringify(std::vector{1, 2, 7}) == "{ 1, 2, 7 }");
    CHECK(Cool::stringify(std::list{1, 2, 7}) == "{ 1, 2, 7 }");
}

TEST_CASE("stringify a boolean")
{
    CHECK(successfully_stringifies(true));
    CHECK(successfully_stringifies(false));
    CHECK(Cool::stringify(true) != "1");  // We want better representations than "1" and "0"
    CHECK(Cool::stringify(false) != "0"); // e.g. "true" and "false"
}

TEST_CASE("stringify a std::chrono type")
{
    const auto now = std::chrono::system_clock::now();
    CHECK(successfully_stringifies(now));
    std::cout << "Stringification of the current time:\n"
              << Cool::stringify(now) << '\n';
}

#include <iostream>
struct WithOstream {
    int x;
};

std::ostream& operator<<(std::ostream& os, WithOstream x)
{
    os << x.x;
    return os;
}

TEST_CASE("stringify using ostream operator <<")
{
    CHECK(Cool::stringify(WithOstream{5}) == "5");
}

TEST_CASE("stringify using ostream operator << and optional")
{
    CHECK(Cool::stringify(std::make_optional(WithOstream{5})) == "Some: 5");
}