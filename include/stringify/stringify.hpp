#pragma once

namespace Cool {

// Default fallback if none of the implementations we tried succeeded
template<typename T>
auto stringify(const T&) -> std::string
{
    return std::string{"[Cool::stringify] ERROR: Couldn't find a to_string() function for this type: "} + typeid(T).name();
}

// Proper to_string for booleans
template<>
inline auto stringify(const bool& value) -> std::string
{
    return value ? "true" : "false";
}

#include "../generated/all_ways_of_finding_to_string.inl" // Must be after the declaration of `stringify()`, otherwise some concepts fail because they don't know about `stringify()`.

} // namespace Cool