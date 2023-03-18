#pragma once

#include <chrono>
#include <sstream>
#include <string>

#if !defined(__APPLE__)
#include <ranges>
#endif

namespace Cool {

template<typename T>
auto stringify(const T& value) -> std::string;

namespace internal {

// Ranges implementation
#if defined(__APPLE__) // TODO Remove this hack once Apple compiler has <ranges>
template<typename T>
concept Range = requires(T v) {
                    // clang-format off
    {v.begin()};
    {v.end()};
                    // clang-format on
                };

template<Range T>
#else
template<std::ranges::range T>
#endif
auto stringify__ranges(const T& value) -> std::string
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

} // namespace internal

#include "../generated/all_ways_of_finding_to_string.inl" // Must be after the declaration of `stringify()`, otherwise some concepts fail because they don't know about `stringify()`.

template<>
auto stringify(const bool&) -> std::string;
template<>
auto stringify(const std::chrono::system_clock::time_point&) -> std::string;

} // namespace Cool