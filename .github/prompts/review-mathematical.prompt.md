---
description: Review and test user-written mathematical or matrix code without providing implementations
---

Review the code I point to (selection, file, or the function name I give you).

Follow `.github/instructions/mathematical.instructions.md`:

- Do not write or propose any logical implementation of mathematical functionality, or any non-mathematical implementation in that area (accessors, row swapping, creators).
- Give feedback on correctness, edge cases, numerical concerns (e.g. floating-point comparison, zero pivots), precondition validation and exceptions, and efficiency. Describe problems and trade-offs; do not supply replacement code.
- Provide GoogleTest code covering the behavior, including invalid-input and boundary cases, following `.github/instructions/tests.instructions.md`.
- Build and run with `ctest --test-dir build --verbose`, then report which tests fail and what the evidence shows. Do not fix the implementation.
