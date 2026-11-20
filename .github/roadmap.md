# Roadmap progress

Single source of truth for what is done and what is next. Tick `[x]` when an item is implemented by the user, tested, and passing in CTest. Stage order follows `.github/copilot-instructions.md`.

## Stage 1: Matrix foundations

### Done

- [x] Construction: `(size_x, size_y)`, initializer lists, `std::vector<std::vector<double>>`, row/column factories
- [x] Element access, iterators, row/column views and ranges
- [x] Arithmetic: `+`, `-`, `*` (matrix and scalar)
- [x] `transpose()`
- [x] `is_square()`
- [x] `augment_columns(b)` (`[A | b]`, any number of columns)
- [x] `swap_rows(row1, row2)`

### Row operations

- [ ] `scale_row(row, factor)`: `std::out_of_range` for a bad row; decide whether `factor == 0` throws `std::invalid_argument`
- [ ] `add_scaled_row(target, source, factor)`: `R_target += factor * R_source`; decide the `target == source` behaviour; delete the const overload like `swap_rows`

### Echelon form and solving

- [ ] `is_row_echelon_form()`: needs a zero tolerance policy
- [ ] Row echelon form reduction (partial pivoting)
- [ ] `lin_solve(b)`: built on `augment_columns`; define singular-matrix behaviour (no solution vs infinitely many)

### Properties

- [ ] `rank()`
- [ ] `determinant()`
- [ ] `inverse()` (via `[A | I]`)

## Stage 2 onwards

Not started. Break a stage into items here when it begins.

## Rules for assistants

- Before suggesting a next step, read this file. Never suggest an item marked `[x]`.
- If the code shows an item is done but it is unticked (or the reverse), say so and ask the user to tick it; do not silently assume.
- Only the user's own implementation counts as done for mathematical items; tests alone do not tick them.
- When the user finishes an item, update this file as part of that change.
