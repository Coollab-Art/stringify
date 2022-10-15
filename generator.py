# ---HOW TO---
# Modify `ways_of_finding_to_string()`, then run this script.
# ------------


def ways_of_finding_to_string():
    return [
        ["UseStd", "std::to_string(value)"],
        ["UseAdl", "to_string(value)"],
        ["UseMethod", "value.to_string()"],
        ["UseOstream", "(std::stringstream{} << value).str()"],
        ["RangesImplementation", "internal::stringify__ranges<T>(value)"],
        ["OptionalLike",
            'value ? "Some: " + Cool::stringify(*value) : "None"'],
    ]


def all_ways_of_finding_to_string():
    concepts = ""
    implementations = ""
    first = True
    for [concept_name, implementation] in ways_of_finding_to_string():
        concepts += f"""
template<typename T>
concept {concept_name} = requires(T value)
{{
    {{{implementation}}} -> std::convertible_to<std::string>;
}};
"""
        implementations += f"""
{"else " if not first else ""}if constexpr(internal::{concept_name}<T>)
{{
    return {implementation};
}}"""
        first = False
    return f"""
namespace internal {{
{concepts}
}} // namespace internal

template<typename T>
auto stringify(const T& value) -> std::string
{{
    {implementations}
    else {{
        return std::string{{"[Cool::stringify] ERROR: Couldn't find a to_string() function for this type: "}} + typeid(T).name();
    }}
}}
"""


if __name__ == "__main__":
    from tooling.generate_files import generate
    generate(
        files=[
            all_ways_of_finding_to_string,
        ]
    )
