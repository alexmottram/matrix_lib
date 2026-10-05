# Copilot instructions

## Project goals

- This is a lightweight C++ matrix library intended to be easy to embed in other codebases, including mathematical-puzzle projects.
- Prefer a small, focused core and standard-library facilities. Keep the core free of third-party runtime dependencies; test-only dependencies are acceptable.
- Prioritize mathematical correctness and clear behavior. When performance choices are non-obvious, explain the trade-offs rather than optimizing speculatively.
- The current `Matrix` stores `double` values. Keep changes consistent with the existing API; do not introduce templates or broaden supported element types without a concrete requirement.

## Design and implementation

- Use C++23 and follow the existing CMake project structure and C++ conventions.
- Preserve a clear separation between the core matrix functionality and presentation. Keep `std::ostream` formatting independent of GUI frameworks; any future GUI integration should be optional and outside the core.
- The public API is still evolving, so breaking changes are acceptable when they materially improve the design. Keep related declarations, implementations, examples, and tests consistent, and call out meaningful API changes.
- Validate dimensions, indices, and operation preconditions. Use exceptions for invalid or undefined operations, following existing exception types and behavior.
- Avoid unrelated refactoring and generated files. Do not edit files under `cmake-build-*`.

## Tests and validation

- Add focused GoogleTest coverage for behavior changes, including relevant invalid-input and boundary cases.
- Run the relevant tests with CTest after changes. A typical local workflow is:

  ```sh
  cmake -S . -B build
  cmake --build build
  ctest --test-dir build --output-on-failure
  ```

- The GitHub Actions workflow builds and tests on Ubuntu and Windows. Keep changes portable across both platforms.
