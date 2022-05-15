#pragma once

namespace Cool {

namespace internal {

template<typename T>
concept UseStd = requires(T value)
{
    std::to_string(value);
};
template<typename T>
concept UseAdl = requires(T value)
{
    to_string(value);
};

} // namespace internal

template<internal::UseStd T>
auto stringify(const T& value) -> std::string
{
    return std::to_string(value);
}

template<internal::UseAdl T>
auto stringify(const T& value) -> std::string
{
    return to_string(value);
}

template<typename T>
auto stringify(const T&) -> std::string
{
    return std::string{"[Cool::stringify] ERROR: Couldn't find a to_string() function for this type: "} + typeid(T).name();
}

} // namespace Cool