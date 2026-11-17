# Agent instructions

Learning project with three goals: 
1) financial derivatives pricing, 
2) linear algebra, 
3) better C++ (new features, best practices). 

It has two layers: `matrix_lib`, a lightweight C++23 matrix library (`double` elements only, no third-party runtime dependencies, GoogleTest is test-only), and a planned `pricing_lib` built on it (dependency is one-way: pricing depends on matrix). The staged roadmap is in `.github/copilot-instructions.md`.

When reviewing, explain concepts and trade-offs and suggest fitting modern C++ features as guidance, without writing the implementation of mathematical code.

**The full, authoritative rules are in `.github/copilot-instructions.md`.** Scoped rules are in `.github/instructions/`:

- `mathematical.instructions.md` – applies to `src/matrix/matrix.h`, `src/matrix/matrix.cpp`, `tests/matrix/matrix_linear_algebra.cpp`, `src/pricing/**`, `tests/pricing/**`
- `tests.instructions.md` – applies to `tests/**`

Read these before making changes. The project map (which file holds what) is in `.github/copilot-instructions.md`.

## Hard rules

- The user writes the mathematical functionality themselves (e.g. `lin_solve()`, `is_row_echelon_form()`, `augmented_matrix()`). Do not provide logical implementations of it, or of non-mathematical code in that area (accessors, row swapping, creators).
- Do provide feedback on user-written code, tests for all changes or questions, and code for repetitive tasks that mirror existing user code (e.g. `row_replace` after `column_replace`).
- Every GoogleTest `TEST`/`TEST_F` must print a clear `std::cout` explanation before its assertions.
- Do not edit files under `cmake-build-*`. Avoid unrelated refactoring.

## Build and test

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --verbose
```

CI builds on Ubuntu and Windows; keep changes portable.
