# Contributing

Thanks for helping improve EasyExamples.

## Prerequisites

- CMake 3.14+
- A C++ compiler with C++17 support (MSVC 2019+ recommended on Windows)

## Local Build

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Validate test discovery count:

```bash
ctest --test-dir build -C Debug -N
```

Current CI-aligned minimums:

- Root Windows build (`BUILD_WINDOWS_EXAMPLES=ON`): at least 7 tests
- Root strict console-only build (`BUILD_WINDOWS_EXAMPLES=OFF`): at least 6 tests

## Strict Warnings Gate (Optional Local Repro)

```bash
cmake -S PolimorficSmart -B build_strict -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON
cmake --build build_strict --config Debug
ctest --test-dir build_strict -C Debug --output-on-failure
```

Root-level strict warnings (selected modules only):

```bash
cmake -S . -B build_strict_root -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build_strict_root --config Debug
ctest --test-dir build_strict_root -C Debug --output-on-failure
```

Disable strict mode for individual modules when isolating failures:

```bash
cmake -S . -B build_strict_root -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON -DBUILD_WINDOWS_EXAMPLES=OFF -DEASYEXAMPLES_STRICT_WARNINGS_MODERNCPP_CONTAINERS=OFF
```

```bash
cmake -S . -B build_strict_root -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON -DBUILD_WINDOWS_EXAMPLES=OFF -DEASYEXAMPLES_STRICT_WARNINGS_EXCEPTION_HANDLING=OFF
```

## Contribution Workflow

1. Keep changes small and focused.
2. Prefer built-in platform/library features over adding dependencies.
3. Preserve existing behavior unless the change explicitly targets behavior.
4. Add or update tests when changing logic.
5. Update README or module docs when setup/build steps change.

## Coding Standards

- Use clear names; avoid one-letter identifiers.
- Keep modules independent where possible.
- Keep warning levels high and resolve new warnings where feasible.
- Avoid hidden coupling between examples.

## Pull Request Checklist

- [ ] Builds from repository root.
- [ ] `ctest` passes in at least one configuration.
- [ ] `ctest -N` from root reports at least 7 discovered tests.
- [ ] Documentation updated if needed.
- [ ] No unrelated generated artifacts committed.

## Troubleshooting

For CI/build incident response flow and reproducible diagnostics, see:

- `docs/OPERATIONS_RUNBOOK.md`
