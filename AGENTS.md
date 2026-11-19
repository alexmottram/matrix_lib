# Agent instructions

Learning project with three goals: (1) financial derivatives pricing, (2) linear algebra, (3) better C++ (new features, best practices).

It has two layers: `matrix_lib`, a lightweight C++23 matrix library (`double` elements only, no third-party runtime dependencies, GoogleTest is test-only), and a planned `pricing_lib` built on it (one-way dependency: pricing depends on matrix). The roadmap is in `.github/copilot-instructions.md`.

When reviewing, explain concepts and trade-offs and suggest fitting modern C++ features as guidance, without writing the implementation of mathematical code.

**The full, authoritative rules are in `.github/copilot-instructions.md`** (including the project map). Read them before making changes. Scoped rules are in `.github/instructions/`:

- `mathematical.instructions.md` – applies to `src/matrix/matrix.h`, `src/matrix/matrix.cpp`, `tests/matrix/matrix_linear_algebra.cpp`, `src/pricing/**`, `tests/pricing/**`
- `tests.instructions.md` – applies to `tests/**`

Reusable workflows: agents in `.github/agents/` (`test-writer` writes and runs tests; read-only `code-reviewer` and `math-reviewer` review and list missing tests), the `/add-tests` prompt, and a `pre-push` hook in `.githooks/` that builds and runs all tests (enable with `git config core.hooksPath .githooks`).

## Hard rules

- The user writes the mathematical functionality themselves (e.g. `lin_solve()`, `is_row_echelon_form()`, `augmented_matrix()`). Do not provide logical implementations of it, or of non-mathematical code in that area (accessors, row swapping, creators).
- Do provide feedback on user-written code, tests for all changes or questions, and code for repetitive tasks that mirror existing user code (e.g. `row_replace` after `column_replace`).
- Every GoogleTest `TEST`/`TEST_F` must print a clear `std::cout` explanation before its assertions.
- Do not edit files under `cmake-build-*`. Avoid unrelated refactoring.

## Build and test

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --verbose
```

CI builds on Ubuntu and Windows; keep changes portable.
