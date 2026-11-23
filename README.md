# Factures & Devis – projet C++ ISTILE 2026-2027

État : jalon R1 – module du montant en lettres (CT-02) + squelette CMake.

## Compiler et tester

```bash
cmake -S . -B build -DISTILE_SANITIZERS=ON   # OFF sous MinGW/Windows
cmake --build build
ctest --test-dir build --output-on-failure
```

Prérequis : g++ >= 11 (ou clang++ >= 14), CMake >= 3.16.
Le framework de tests (doctest 2.4.11) est fourni dans `tests/third_party/`.

## Arborescence

- `src/metier/` : couche métier (aucun SQL, aucun cin/cout)
- `src/persistance/`, `src/presentation/` : à venir
- `tests/` : tests unitaires doctest
- `sql/` : scripts 01 à 05
- `docs/` : UML, rapports, Doxygen
