# Operations Runbook

## Purpose

Provide a repeatable procedure for diagnosing and resolving build and test failures in EasyExamples.

## Owners

- Primary: repository maintainers
- Backup: contributors assigned in CODEOWNERS

## Standard CI Signals

- Workflow: `.github/workflows/ci.yml`
- Failing jobs upload diagnostics artifacts prefixed with `diagnostics-`.
- Key checks:
  - root build matrix (`Debug`, `Release`)
  - Linux console-only build/test (`BUILD_WINDOWS_EXAMPLES=OFF`, default compiler)
  - Linux console-only build/test (`BUILD_WINDOWS_EXAMPLES=OFF`, Clang)
  - strict warnings (`PolimorficSmart` standalone + root-selected + selector isolation)

## Triage Procedure

1. Identify failing job and matrix leg.
2. Download diagnostics artifact from the failed run.
3. Inspect, in order:
   - `build/**/Test.xml`
   - `build/Testing/Temporary/LastTest.log` (or strict equivalents)
   - `build/CMakeFiles/CMakeOutput.log`
   - `build/CMakeFiles/CMakeError.log`
4. Reproduce locally with the exact configure flags from CI.
5. Confirm whether failure is:
   - compile-time (compiler/toolchain)
   - test discovery (`ctest -N` mismatch)
   - runtime test failure
6. Apply a minimal fix and rerun local build + tests before pushing.

## Reproduction Commands

### Root build and tests

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

### Strict warnings (PolimorficSmart)

```bash
cmake -S PolimorficSmart -B build_strict -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON
cmake --build build_strict --config Debug
ctest --test-dir build_strict -C Debug --output-on-failure
```

### Strict warnings (root selected modules)

```bash
cmake -S . -B build_strict_root -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build_strict_root --config Debug
ctest --test-dir build_strict_root -C Debug --output-on-failure
```

## Common Failure Patterns

### Test discovery failure

- Symptom: CI fails in "Validate test discovery" step.
- Typical causes:
  - `add_test(...)` removed or guarded incorrectly
  - executable target renamed without updating tests
  - configure options disable expected modules
- Fix:
  - restore test registration in module `CMakeLists.txt`
  - validate expected minimum test count locally with `ctest -N`

Current expected baselines:

- Root Windows configuration (`BUILD_WINDOWS_EXAMPLES=ON`): at least 7 tests
- Root strict console-only configuration (`BUILD_WINDOWS_EXAMPLES=OFF`): at least 6 tests
- Linux console-only configuration (`BUILD_WINDOWS_EXAMPLES=OFF`, default compiler): at least 6 tests
- Linux console-only configuration (`BUILD_WINDOWS_EXAMPLES=OFF`, Clang): at least 6 tests

### Strict warnings failures

- Symptom: strict warnings job fails compile.
- Typical causes:
  - new warnings promoted to errors (`/WX` or `-Werror`)
- Fix:
  - correct code issue first; avoid suppressions unless justified
  - use selector toggles only for isolation while debugging

### Windows GUI build issues

- Symptom: Win32 target compile/link fail.
- Typical causes:
  - missing Win32 subsystem or library link mismatch (`user32`, `comctl32`, `gdi32`, `gdiplus`)
- Fix:
  - verify module `CMakeLists.txt` target properties and linked libraries

## Rollback Guidance

- Prefer reverting only the offending commit(s).
- If urgent, disable only the smallest scoped CI check necessary and file a follow-up issue/PR to restore guardrails.

## Escalation

Escalate when any of the following occur:

- repeated flaky failures across multiple runs with no deterministic repro
- compiler/toolchain regression on `windows-latest`
- test count unexpectedly drops below CI thresholds

## Post-Incident Checklist

- Root cause documented in PR description
- Reproduction steps captured
- Tests added/updated to prevent recurrence
- Relevant docs (`README`, `CONTRIBUTING`, runbook) updated when process changed
