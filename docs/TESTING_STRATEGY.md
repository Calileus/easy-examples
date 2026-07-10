# Testing Strategy

## Purpose

Define a repeatable testing policy for EasyExamples that balances educational simplicity with enterprise-style quality gates.

## Test Taxonomy

### 1) Smoke Tests

Scope: fast executable-level validation that programs start, run, and exit successfully.

Current smoke coverage:

- `vscode_cmake_easiest_smoke`
- `vscode_cmake_w2src_smoke`
- `moderncpp_containers_smoke`
- `exception_handling_smoke`

### 2) Functional/Behavioral Tests

Scope: deterministic logic checks for module behavior.

Current functional coverage:

- `financial_simple_test`
- `financial_threaded_test`
- `windows_dialog_input_validation_test`
- Optional: `financial_gtest_suite` (when GTest is available)

### 3) Strict-Warnings Quality Gates

Scope: compile with warnings-as-errors in selected modules to prevent quality drift.

Current strict jobs:

- `strict-warnings-polimorficsmart`
- `strict-warnings-root-selected`
- `strict-warnings-selector-isolation`

## CI Baselines

### Windows root pipeline (`BUILD_WINDOWS_EXAMPLES=ON`)

- Minimum discovered tests: **7**
- Required checks: configure, build (Debug/Release), discovery gate, test execution

### Linux console-only pipeline (`BUILD_WINDOWS_EXAMPLES=OFF`)

- Minimum discovered tests: **6**
- Required checks: configure, build, discovery gate, test execution

### Linux console-only pipeline (`BUILD_WINDOWS_EXAMPLES=OFF`, Clang)

- Minimum discovered tests: **6**
- Required checks: configure, build, discovery gate, test execution

### Strict root console-only pipeline (`BUILD_WINDOWS_EXAMPLES=OFF`)

- Minimum discovered tests: **6**
- Required checks: strict compile, discovery gate, test execution

## Local Reproduction Commands

### Root Windows flow

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug -N
ctest --test-dir build -C Debug --output-on-failure
```

### Linux/console-only parity flow

```bash
cmake -S . -B build_linux -DBUILD_TESTING=ON -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build_linux
ctest --test-dir build_linux -N
ctest --test-dir build_linux --output-on-failure
```

### Strict warnings flow

```bash
cmake -S . -B build_strict_root -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build_strict_root --config Debug
ctest --test-dir build_strict_root -C Debug -N
ctest --test-dir build_strict_root -C Debug --output-on-failure
```

## Acceptance Policy

A change is considered test-acceptable when:

1. Relevant local tests pass for touched modules.
2. Root discovery threshold is preserved (7 Windows, 6 console-only).
3. No strict-warning regressions are introduced in guarded modules.
4. New deterministic logic introduced in non-trivial code paths includes a test where practical.

## Roadmap (Testing)

1. Add deterministic unit tests for additional Win32 input/validation helper logic.
2. Add optional coverage reporting (without making it mandatory for contributors).
3. Introduce lightweight performance baselines for `PolimorficSmart` threading workloads.
4. Expand Linux matrix to an additional compiler lane once warning parity is stable. ✅ Completed (`build-linux-console-clang`)
