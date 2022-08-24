# ---HOW TO---
# Modify `ways_of_finding_to_string()`, then run this script.
# ------------


def ways_of_finding_to_string():
    return [
        ["UseStd", "std::to_string(value)"],
        ["UseAdl", "to_string(value)"],
        ["UseMethod", "value.to_string()"],
        ["OptionalLike",
            'value ? "Some: " + Cool::stringify(*value) : "None"'],
    ]


def all_ways_of_finding_to_string():
    concepts = ""
    implementations = ""
    for [concept_name, implementation] in ways_of_finding_to_string():
        concepts += f"""
template<typename T>
concept {concept_name} = requires(T value)
{{
    {{{implementation}}};
}};
"""
        implementations += f"""
template<internal::{concept_name} T>
auto stringify(const T& value) -> std::string
{{
    return {implementation};
}}
"""
    return f"""
namespace internal {{
{concepts}
}} // namespace internal

{implementations}
"""


if __name__ == "__main__":
    from tooling.generate_files import generate
    generate(
        files=[
            all_ways_of_finding_to_string,
        ]
    )
