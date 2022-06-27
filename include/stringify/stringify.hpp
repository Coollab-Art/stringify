#pragma once

namespace Cool {

#include "../generated/all_ways_of_finding_to_string.inl"

// Proper to_string for booleans
template<>
inline auto stringify(const bool& value) -> std::string
{
    return value ? "true" : "false";
}

// Default fallback if none of the methods we tried succeeded
template<typename T>
auto stringify(const T&) -> std::string
{
    return std::string{"[Cool::stringify] ERROR: Couldn't find a to_string() function for this type: "} + typeid(T).name();
}

} // namespace Cool