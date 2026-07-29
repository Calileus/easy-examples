# Documentation Consistency Matrix

## Scope Reviewed

- `README.md`
- `CONTRIBUTING.md`
- `SECURITY.md`
- `docs/RELEASE_CHECKLIST.md`
- `docs/OPERATIONS_RUNBOOK.md`
- `docs/TESTING_STRATEGY.md`
- `docs/ENTERPRISE_READINESS_BASELINE.md`
- `PolimorficSmart/README.md`

## Matrix

| Area | Source of Truth | Files Using It | Status | Action |
|---|---|---|---|---|
| Repository name (`EasyExamples`) | Root folder + root CMake project | All docs | Aligned | Keep |
| Product title (`Easy C++ Examples`) | `README.md` title | Root docs | Aligned | Keep |
| Minimum CMake version (`3.14`) | Root `CMakeLists.txt` | `CONTRIBUTING.md`, `README.md` | Previously inconsistent | Updated README to 3.14 |
| Windows root test command uses `-C Debug` | Windows CI jobs | `README.md`, `CONTRIBUTING.md`, runbook | Aligned | Keep |
| Linux console-only test command without `-C` | Linux CI jobs | `CONTRIBUTING.md`, runbook | Partially represented | Added to README + checklist |
| Discovery baseline (Windows >=7, console-only >=6) | CI workflow guards | `CONTRIBUTING.md`, testing docs, runbook | Partially represented | Added to README + checklist |
| Strict warnings terminology | Root CMake options + CI jobs | `CONTRIBUTING.md`, runbook, testing docs | Aligned | Keep |
| Coverage terminology and optionality | CI `coverage-linux-console` | testing docs, runbook | Aligned | Keep |
| Module naming (`PolimorficSmart`) | Actual folder name | All docs | Inconsistent aliases in prose | Standardized via terminology doc |
| Build instructions for all modules | Root build is preferred | `README.md` | Previously mixed/confusing quick-build loop | Replaced with root canonical commands |

## Contradictions Found and Resolved

1. README prerequisites listed CMake 3.10 while root CMake requires 3.14.
   - Resolution: Updated README to 3.14.
2. Release checklist implied only Windows/multi-config validation.
   - Resolution: Added Linux/macOS console-only build/test checks.
3. Root README lacked explicit single-config CTest command.
   - Resolution: Added Linux/macOS command without `-C`.

## Remaining Documentation Risks

- `PolimorficSmart/README.md` still contains generator-specific run paths and older standalone workflow emphasis.
- Some prose uses conceptual names ("polymorphism") without always pairing module alias `PolimorficSmart`.

## Governance Rule

For future updates, apply this precedence:

1. Code and CI (`CMakeLists.txt`, workflow files)
2. `docs/TERMINOLOGY.md`
3. User-facing docs (`README.md`, module READMEs)
