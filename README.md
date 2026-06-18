# QSecureLib

Post-Quantum Secure File Encryption Library built using:

- ML-KEM-768 (Kyber)
- ML-DSA-65 (Dilithium)
- AES-256-GCM
- Argon2 Password Protection
- Qt GUI

## Features

- Hybrid File Encryption
- Digital Signatures
- Tamper Detection
- Password Protected Private Keys
- Secure Container Format
- GUI Application

## Build

mkdir build
cd build

cmake ..
cmake --build . -j$(nproc)

## Run

./qsecure_gui

## Algorithms

### ML-KEM-768
Used for key encapsulation.

### ML-DSA-65
Used for digital signatures.

### AES-256-GCM
Used for file encryption.

### Argon2id
Used for password-based key derivation.