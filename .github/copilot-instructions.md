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

## Linear algebra implementation guidance

- Do not implement, propose implementation approaches, or volunteer fixes for functions in the linear algebra area (including `lin_solve()`, `is_row_echelon_form()`, and `augmented_matrix()`) unless the user specifically asks for implementation suggestions or changes. The user wants to develop these implementations independently and use Copilot to test, review, and improve code they provide.
- When asked to test, review, or provide feedback on a user-authored linear algebra implementation, stay within that scope: identify behavior with tests or concrete evidence and discuss the implementation provided, but do not write replacement algorithms or unsolicited implementation plans.

## Tests and validation

- Add focused GoogleTest coverage for behavior changes, including relevant invalid-input and boundary cases.
- Every GoogleTest `TEST`/`TEST_F` body must write a clear `std::cout` explanation of the behavior being tested. Put the explanation before assertions so it remains useful when a test fails, and include relevant inputs, expected behavior, and before/after values when these help explain the example.
- Keep test output instructional and specific to the test rather than using generic progress messages. Compile-time checks inside test bodies must also print what property they verify.
- Include `<iostream>` in test files that use `std::cout`; prefer `\n` over `std::endl` unless flushing is needed. Preserve useful matrix/value output alongside the explanation where it clarifies the operation.
- In tests that modify values inside loops, print a concise message for each value that actually changes, including its coordinates or iteration index and its old and new values. Do not print every unchanged value; keep loop output bounded and informative.
- Use `ctest --verbose` when reviewing successful test output; CTest otherwise hides `std::cout` from passing tests.
- Run the relevant tests with CTest after changes. A typical local workflow is:

  ```sh
  cmake -S . -B build
  cmake --build build
  ctest --test-dir build --verbose
  ```

- The GitHub Actions workflow builds and tests on Ubuntu and Windows. Keep changes portable across both platforms.
