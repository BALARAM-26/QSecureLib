# C++ Library for Quantum Safe Encryption (QSecureLib)

## Overview

QSecureLib is a modular C++ library developed as part of a research internship to provide **Quantum-Safe File Encryption** using the Open Quantum Safe (liboqs) library.

The library combines:

- AES-256-GCM for fast symmetric file encryption
- Post-Quantum Key Encapsulation Mechanisms (ML-KEM and other liboqs KEMs)
- Post-Quantum Digital Signatures
- Hybrid Encryption
- Qt-based GUI
- Benchmarking
- Cross-compilation support

The objective is to encrypt and decrypt any type of file (PDF, images, videos, ZIP files, documents, etc.) securely against both classical and quantum computer attacks.

---

# Features

- AES-256-GCM File Encryption
- Hybrid Encryption (AES + ML-KEM)
- Quantum-Safe Key Generation
- Digital Signature Generation
- Signature Verification
- File Integrity Verification
- Secure Key Protection
- Binary File Handling
- Benchmarking Module
- Qt GUI
- Cross Platform Support

---

# Project Structure

```
QSecureLib/
│
├── include/
├── src/
├── examples/
├── gui/
├── build/
├── docs/
├── CMakeLists.txt
└── README.md
```

---

# Prerequisites

Before building the project, install the following software.

## Operating System

- Ubuntu 24.04 LTS (Native or WSL)

## Compiler

- GCC
- G++

## Build Tools

- CMake
- Make

## Libraries

- OpenSSL
- liboqs
- Qt6

## Development Tools

- Git
- pkg-config
- Visual Studio Code (Recommended)

---

# Installing Dependencies

Update Ubuntu

```bash
sudo apt update
sudo apt upgrade
```

Install development tools

```bash
sudo apt install \
build-essential \
cmake \
git \
pkg-config \
libssl-dev \
qt6-base-dev \
qt6-tools-dev \
qt6-tools-dev-tools
```

---

# Install liboqs

Clone liboqs

```bash
git clone https://github.com/open-quantum-safe/liboqs.git
```

Build liboqs

```bash
cd liboqs

mkdir build

cd build

cmake -DCMAKE_INSTALL_PREFIX=$HOME/_oqs ..

make

make install
```

---

# Clone QSecureLib

```bash
git clone https://github.com/<YOUR_GITHUB_USERNAME>/QSecureLib.git

cd QSecureLib
```

---

# Build the Project

```bash
mkdir build

cd build

cmake ..

make
```

If compilation is successful, the following executables will be generated:

- encrypt_test
- mlkem_test
- hybrid_test
- signature_test
- key_test
- key_protect_test
- file_signature_test
- container_test
- benchmark
- qsecure_gui

---

# Running the Examples

## ML-KEM

```bash
./mlkem_test
```

Generates

- Public Key
- Secret Key
- Ciphertext
- Shared Secret

---

## Encryption Test

```bash
./encrypt_test
```

Tests

- AES Encryption
- AES Decryption

---

## Hybrid Encryption

```bash
./hybrid_test
```

Tests

- ML-KEM
- AES
- Hybrid Encryption

---

## Signature Test

```bash
./signature_test
```

Tests

- Signature Generation
- Signature Verification

---

## Key Management

```bash
./key_test
```

Tests

- Generate Keys
- Save Keys
- Load Keys

---

## File Signature

```bash
./file_signature_test
```

Signs any file and verifies the signature.

---

## Key Protection

```bash
./key_protect_test
```

Encrypts private keys before storing them.

---

## Container Test

```bash
./container_test
```

Tests secure encrypted container creation.

---

## Benchmark

```bash
./benchmark
```

Measures

- Key Generation Time
- Encryption Time
- Decryption Time
- Signature Time

Benchmark results are saved in

```
benchmark_results.txt
```

---

# Running the GUI

If using WSL:

```bash
export QT_QPA_PLATFORM=xcb
```

Run

```bash
./qsecure_gui
```

---

# Supported Algorithms

## Key Encapsulation Mechanisms

- ML-KEM-512
- ML-KEM-768
- ML-KEM-1024
- BIKE
- HQC
- FrodoKEM
- Classic McEliece
- NTRU
- sntrup761

---

## Digital Signatures

- ML-DSA
- Falcon
- SPHINCS+
- MAYO
- CROSS
- UOV

---

# Usage

## Generate Keys

Generate

- Public Key
- Private Key

---

## Encrypt

Input

```
document.pdf
```

Output

```
document.qsec
```

---

## Decrypt

Input

```
document.qsec
```

Output

```
document.pdf
```

---

## Sign File

Input

```
document.pdf
```

Output

```
document.sig
```

---

## Verify Signature

Input

```
document.pdf
document.sig
```

Output

```
Signature Valid
```

or

```
Signature Invalid
```

---

# Tamper Detection Test

Generate a signature

```bash
./file_signature_test
```

Open another terminal

```bash
nano sample.txt
```

Modify one character.

Save the file.

Verify again.

Expected output

```
Signature Invalid
```

This demonstrates file integrity protection.

---

# Development Environment

| Component | Version |
|-----------|----------|
| Ubuntu | 24.04 |
| GCC | Latest |
| CMake | Latest |
| OpenSSL | 3.x |
| liboqs | Latest |
| Qt | 6 |
| VS Code | Latest |

---

# Future Work

- Support every liboqs KEM algorithm
- Support every liboqs Signature algorithm
- Android Cross Compilation
- Windows Installer
- Secure File Container
- Hardware Security Module Support
- GPU Acceleration
- Cloud Storage Integration

---

# References

1. Open Quantum Safe (liboqs)

https://openquantumsafe.org/liboqs/

2. liboqs GitHub

https://github.com/open-quantum-safe/liboqs

3. OpenSSL

https://www.openssl.org/

4. Qt Framework

https://doc.qt.io/

---

**
