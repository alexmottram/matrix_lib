---
description: Add GoogleTest coverage following this project's test conventions
---

Add GoogleTest tests for the behavior I describe (or for the code I point to).

- Follow `.github/instructions/tests.instructions.md`: every `TEST`/`TEST_F` prints a specific `std::cout` explanation before its assertions, includes `<iostream>`, uses `\n`, and prints only changed values in loops.
- Cover normal behavior, invalid inputs (expect the existing exception types), and boundary cases (empty, 1x1, non-square, first/last index).
- Put tests in the matching existing file under `tests/matrix/` (or `tests/pricing/` for pricing code), or create a new file and register it in `CMakeLists.txt` under the relevant tests target.
- Do not change the implementation under test.
- Run `cmake --build build` and `ctest --test-dir build --verbose`, and report the results.
