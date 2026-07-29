# Release Checklist

## 1. Build Validation

- [ ] Windows root configure: `cmake -S . -B build -DBUILD_TESTING=ON`
- [ ] Windows root build (Debug): `cmake --build build --config Debug`
- [ ] Windows root build (Release): `cmake --build build --config Release`
- [ ] Linux/macOS console-only configure: `cmake -S . -B build_linux -DBUILD_TESTING=ON -DBUILD_WINDOWS_EXAMPLES=OFF`
- [ ] Linux/macOS console-only build: `cmake --build build_linux`

## 2. Test Validation

- [ ] Windows root tests (Debug): `ctest --test-dir build -C Debug --output-on-failure`
- [ ] Windows root tests (Release): `ctest --test-dir build -C Release --output-on-failure`
- [ ] Linux/macOS console-only tests: `ctest --test-dir build_linux --output-on-failure`
- [ ] Discovery baseline verified (Windows >=7, console-only >=6)

## 3. Documentation Validation

- [ ] README build and run instructions are accurate.
- [ ] New modules/files are listed where appropriate.
- [ ] Troubleshooting notes updated if behavior changed.
- [ ] Terminology/commands align with `docs/TERMINOLOGY.md`.

## 4. Repository Hygiene

- [ ] No generated build folders committed.
- [ ] No local machine paths in committed files.
- [ ] No debug-only temporary code left behind.

## 5. Governance Validation

- [ ] CODEOWNERS mappings are up to date.
- [ ] SECURITY policy remains valid.
- [ ] License text reflects intended distribution policy.
