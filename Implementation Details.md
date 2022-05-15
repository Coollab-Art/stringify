We rely on ADL to find a `to_string()` function from the namespace associated with the type.
We also try `std::to_string()` for primitive types which don't have a namespace.