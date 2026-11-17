---
applyTo: "tests/**"
---

# Test conventions

- Add focused GoogleTest coverage for behavior changes, including relevant invalid-input and boundary cases.
- Every `TEST`/`TEST_F` body must write a clear `std::cout` explanation of the behavior being tested. Put the explanation before assertions so it remains useful when a test fails, and include relevant inputs, expected behavior, and before/after values when these help explain the example.
- Keep test output instructional and specific to the test rather than using generic progress messages. Compile-time checks inside test bodies must also print what property they verify.
- Include `<iostream>` in test files that use `std::cout`; prefer `\n` over `std::endl` unless flushing is needed. Preserve useful matrix/value output alongside the explanation where it clarifies the operation.
- In tests that modify values inside loops, print a concise message for each value that actually changes, including its coordinates or iteration index and its old and new values. Do not print every unchanged value; keep loop output bounded and informative.
- Use `ctest --verbose` when reviewing successful test output; CTest otherwise hides `std::cout` from passing tests.
