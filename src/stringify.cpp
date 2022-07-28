#include <fmt/core.h>
#include <stringify/stringify.hpp>

namespace Cool {

template<>
auto stringify(const bool& value) -> std::string
{
    return value
               ? "true"
               : "false";
}

template<>
auto stringify(const std::chrono::system_clock::time_point& value) -> std::string
{
    /// hh_mm_ss isn't yet supported on GCC :(
    // const auto timepoint = std::chrono::hh_mm_ss{value.time_since_epoch()};
    // return std::format(
    //     "{}:{}'{}\"{}",
    //     timepoint.hours().count(),
    //     timepoint.minutes().count(),
    //     timepoint.seconds().count(),
    //     std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count() % 1000
    // );

    const auto time = std::chrono::system_clock::to_time_t(value);
#if !defined(__GNUC__)
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
    const auto local_time = localtime(&time);
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if !defined(__GNUC__)
#pragma warning(pop)
#endif
    if (local_time)
    {
        return fmt::format(
            "{:02d}:{:02d}'{:02d}\"{:03d}",
            local_time->tm_hour,
            local_time->tm_min,
            local_time->tm_sec,
            std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count() % 1000
        );
    }
    else
    {
        return "Failed to stringify time!";
    }
}

} // namespace Cool