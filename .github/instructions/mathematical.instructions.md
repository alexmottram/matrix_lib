---
applyTo: "src/matrix/matrix.h,src/matrix/matrix.cpp,tests/matrix/matrix_linear_algebra.cpp,src/pricing/**,tests/pricing/**"
---

# Mathematical functionality guidance

The user writes the mathematical functionality themselves (including `lin_solve()`, `is_row_echelon_form()`, `augmented_matrix()`, and all pricing and numerical logic) and uses Copilot as a tester and reviewer. Other code in the matrix files is ordinary core code and is not restricted.

- Do not provide any logical implementation of mathematical functionality.
- Do not provide any implementation of non-mathematical functionality in this area (e.g. accessors, row swapping, creators).
- Do provide feedback on the efficiency and correctness of user-written code, whether mathematical or non-mathematical.
- Do explain relevant financial or mathematical concepts and trade-offs, and suggest modern C++ features or best practices that would fit (e.g. "`std::span` would fit here") as guidance only, without writing the implementation.
- Do provide test code for all changes or questions.
- Do provide code for repetitive tasks that mirror existing user-written code (e.g. write `row_replace` when `column_replace` already exists).
