#pragma once

#include <chrono>
#include <string>

#if !defined(__APPLE__)
#include <ranges>
#endif

namespace Cool {

// Default fallback if none of the implementations we tried succeeded
template<typename T>
auto stringify(const T&) -> std::string
{
    return std::string{"[Cool::stringify] ERROR: Couldn't find a to_string() function for this type: "} + typeid(T).name();
}

// Ranges implementation
#if defined(__APPLE__) // TODO Remove this hack once Apple compiler has <ranges>
template<typename T>
concept Range = requires(T v)
{
    // clang-format off
    {v.begin()} -> std::convertible_to<typename T::iterator>;
    {v.end()} -> std::convertible_to<typename T::iterator>;
    // clang-format on
};

template<Range T>
#else
template<std::ranges::range T>
#endif
auto stringify(const T& value) -> std::string
{
    std::string res{"{ "};
    bool        first = true;
    for (const auto& x : value)
    {
        if (!first)
        {
            res += ", ";
        }
        first = false;
        res += Cool::stringify(x);
    }
    res += " }";
    return res;
}

#include "../generated/all_ways_of_finding_to_string.inl" // Must be after the declaration of `stringify()`, otherwise some concepts fail because they don't know about `stringify()`.

template<>
auto stringify(const bool&) -> std::string;
template<>
auto stringify(const std::chrono::system_clock::time_point&) -> std::string;

} // namespace Cool