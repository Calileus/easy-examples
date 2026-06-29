# Release Checklist

## 1. Build Validation

- [ ] `cmake -S . -B build -DBUILD_TESTING=ON`
- [ ] `cmake --build build --config Debug`
- [ ] `cmake --build build --config Release`

## 2. Test Validation

- [ ] `ctest --test-dir build -C Debug --output-on-failure`
- [ ] `ctest --test-dir build -C Release --output-on-failure`

## 3. Documentation Validation

- [ ] README build and run instructions are accurate.
- [ ] New modules/files are listed where appropriate.
- [ ] Troubleshooting notes updated if behavior changed.

## 4. Repository Hygiene

- [ ] No generated build folders committed.
- [ ] No local machine paths in committed files.
- [ ] No debug-only temporary code left behind.

## 5. Governance Validation

- [ ] CODEOWNERS mappings are up to date.
- [ ] SECURITY policy remains valid.
- [ ] License text reflects intended distribution policy.
