# Copilot instructions

## Mathematical functionality (hard rule)

The user writes the mathematical functionality themselves (e.g. `lin_solve()`, `is_row_echelon_form()`, `augmented_matrix()`, and all pricing and numerical logic) and uses Copilot as a tester and reviewer. Do not provide logical implementations of it, or of non-mathematical code in that area (accessors, row swapping, creators). Feedback, tests, and code for repetitive tasks mirroring existing user code are welcome. Full rules: `.github/instructions/mathematical.instructions.md`.

## Project goals

This is a learning project. The goals, in order:

1. Improve knowledge of financial derivatives pricing.
2. Improve knowledge of linear algebra.
3. Improve C++ skills: learn new language features and best practices.

The project has two layers:

- `matrix_lib`: a lightweight `double`-only matrix library with no third-party runtime dependencies (test-only dependencies are acceptable). It stays `double`-only; do not introduce templates or broaden element types without a concrete requirement.
- `pricing_lib` (planned): derivatives pricing built on `matrix_lib`. Dependencies go one way only: pricing depends on matrix, never the reverse.

Roadmap (work in order; each stage pairs finance, linear algebra, and C++ goals):

1. Matrix foundations: solving, echelon form, rank, determinant, inverse.
2. Decompositions: LU, Cholesky, QR, eigenvalues.
3. Rates and discounting: curves, interpolation (splines), bond pricing.
4. Closed-form options: Black-Scholes, Greeks, implied volatility.
5. Lattices and PDEs: binomial trees, finite differences.
6. Monte Carlo: correlated paths, variance reduction, PCA.
7. Risk and portfolios: covariance, optimisation, VaR, least squares.
8. Stretch: American options (regression), SVD, performance work.

Progress is tracked item by item in `.github/roadmap.md`. Read it before suggesting what to work on next, never suggest items already ticked, and update it when an item is completed.

How to help with learning:

- Explain concepts, trade-offs, and relevant financial or mathematical context when reviewing code, rather than just giving answers.
- Suggest fitting modern C++ features or best practices (e.g. "`std::span` would fit here") as guidance only; never write mathematical implementations.
- Prioritize mathematical correctness and clear behavior. Explain non-obvious performance trade-offs rather than optimizing speculatively.

## Project map

Current layout (the pricing layer will be added as `src/pricing/` with tests in `tests/pricing/`, its own `pricing_lib` and `pricing_tests` targets, and a one-way dependency on `matrix_lib`; update this map when it is created). Include root is `src/`, so headers are included as `"matrix/..."` and `"utils/..."`:

- `src/matrix/matrix.h`, `src/matrix/matrix.cpp` – the `Matrix` class (storage, access, arithmetic, and the mathematical functionality).
- `src/matrix/matrix_iterator.*` – `Matrix::Iterator` / `ConstIterator` over elements.
- `src/matrix/matrix_slice_iterators.h`, `src/matrix/matrix_slice_views.*` – row/column iterators, ranges, and views.
- `src/matrix/matrix_lib.h` – convenience header including the full matrix API (include as `"matrix/matrix_lib.h"`; the include root is `src/`).
- `src/utils/external_deps.h` – single place for standard-library includes used by the library; add new std includes here rather than in individual files.
- `src/utils/std_extensions.h` – helper stream operators for std types.
- `tests/matrix/` – GoogleTest files for the matrix library, one per feature area; register new test files in `CMakeLists.txt`.
- `examples/main.cpp` – example executable (`matrix_example`).
- `CMakeLists.txt` – builds the `matrix_lib` library, `matrix_example`, and `matrix_tests` (CTest-discovered).
- `.github/agents/` – `test-writer` (writes and runs tests, never edits `src/`), plus read-only `code-reviewer` (C++ quality) and `math-reviewer` (mathematical correctness). Reviewers list missing tests but write none.
- `.github/roadmap.md` – tickable checklist of done and pending roadmap items; the source of truth for "what next".
- `.github/prompts/` – reusable prompts (`/add-tests`).
- `.githooks/pre-push` – builds and runs all tests before a push (enable with `git config core.hooksPath .githooks`).

## Design and implementation

- Use C++23 and follow the existing CMake project structure and C++ conventions.
- Preserve a clear separation between the core matrix functionality and presentation. Keep `std::ostream` formatting independent of GUI frameworks; any future GUI integration should be optional and outside the core.
- The public API is still evolving, so breaking changes are acceptable when they materially improve the design. Keep related declarations, implementations, examples, and tests consistent, and call out meaningful API changes.
- Validate dimensions, indices, and operation preconditions, and throw for invalid or undefined operations using the existing exception types:
  - `std::out_of_range` for row, column, or coordinate indices outside the matrix.
  - `std::invalid_argument` for mismatched dimensions or sizes (e.g. addition, subtraction, multiplication, ragged rows, row/column view size mismatch).
  - `std::length_error` when requested dimensions exceed the maximum element count.
- Avoid unrelated refactoring and generated files. Do not edit files under `cmake-build-*`.

## Tests and validation

- Add focused GoogleTest coverage for behavior changes, including relevant invalid-input and boundary cases. Detailed test conventions (including the mandatory `std::cout` explanations) are in `.github/instructions/tests.instructions.md`.
- Run the relevant tests with CTest after changes. `--verbose` shows test output. Use this workflow, which works for single-config (Ninja, Make) and multi-config (Visual Studio, Xcode) generators:

  ```sh
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
  cmake --build build --config Debug
  ctest --test-dir build -C Debug --verbose
  ```

- The GitHub Actions workflow builds and tests on Ubuntu and Windows. Keep changes portable across both platforms.

## Definition of done

- The project builds without new warnings and `ctest --test-dir build -C Debug --verbose` passes.
- New or changed behavior has tests that follow `.github/instructions/tests.instructions.md`.
- Related declarations, implementations, examples (`examples/main.cpp`), and `CMakeLists.txt` registrations are consistent.
- Meaningful API changes are called out in the summary.
