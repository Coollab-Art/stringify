#include <stringify/stringify.hpp>

namespace Cool {

template<>
auto stringify(const bool& value) -> std::string
{
    return value
               ? "true"
               : "false";
}

} // namespace Cool