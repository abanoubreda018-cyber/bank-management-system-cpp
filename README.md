# Bank Management System — C++ Console

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20Console-lightgrey.svg)
![Architecture](https://img.shields.io/badge/Architecture-Procedural%20C%2B%2B-success.svg)
![Status](https://img.shields.io/badge/Status-Reviewed%20%26%20Hardened-brightgreen.svg)

A robust, hardened console banking management system built with modern standard **C++17** by **Abanoub Reda**. The system demonstrates procedural software design, structured data modeling, stream-based text file serialization, safe numeric parsing, and defensive input validation.

---

## 📌 Overview

This project simulates a complete core banking terminal application. It enables bank administrators to manage client accounts and perform essential financial transactions (deposits, withdrawals, and balance inquiries) with persistent local storage.

The codebase adheres strictly to **clean procedural design** (`structs`, `vectors`, `enums`, and pure functions), prioritizing code clarity, predictable execution flow, and zero unnecessary overhead.

---

## ✨ Features

- **Client Management (CRUD):**
  - **List Clients:** Tabular display of all registered bank clients with formatted currency output.
  - **Add Client:** Registration with automatic uniqueness verification on account numbers.
  - **Find Client:** Instant search and account card inspection by Account Number.
  - **Update Client:** In-place modification of client name, PIN, and phone details.
  - **Delete Client:** Safe soft/hard record deletion with confirmation prompts.

- **Financial Transactions:**
  - **Deposit:** Increase account balance with positive-amount validation and optional cancellation (`0`).
  - **Withdrawal:** Overdraft protection (cannot exceed balance), zero-balance protection, and optional cancellation (`0`).
  - **Total Balances:** Real-time ledger aggregation displaying sum totals across all registered clients.

- **Storage & Reliability:**
  - **File Persistence:** Automatic storage in `Clients.txt` using record serialization with `#//#` delimiters.
  - **Defensive Error Handling:** Guaranteed exception safety around file streams and numeric conversions.

---

## 🛡️ Robustness & Hardened Improvements

Following a comprehensive code review (documented in [docs/REVIEW_AR.md](docs/REVIEW_AR.md)), the project was reinforced with the following protections:

| Component | Potential Issue | Implemented Solution |
| :--- | :--- | :--- |
| **Numeric Parsing (`stod`)** | Corrupted balance data could trigger unhandled exceptions and crash the application. | Wrapped in `try/catch` with deterministic zero-fallback (`0.0`). |
| **String Tokenizer (`SplitString`)** | Empty fields caused column shifts and data loss upon saving. | Fixed token parsing to preserve empty delimiters and maintain exact column alignment. |
| **Withdrawal Loop** | Accounts with `$0` balance caused an infinite loop in the withdrawal prompt. | Immediate pre-check halts withdrawal if balance is `$0`, plus user cancellation via `0`. |
| **Initial Balance Input** | Accepted negative values and entered infinite fail-states on non-numeric input. | Re-prompt loop validates positive values (`>= 0`) and clears `cin.fail()` streams. |
| **File I/O Verification** | Write errors were ignored while claiming successful operations. | File operations now return `bool`, verifying stream states before reporting success. |
| **Memory Efficiency** | Passing large structs and vectors by value created redundant memory copies. | Replaced with `const &` (const references) across all read-only functions. |
| **Console Cleanup** | `pause>0` wrote stdout to an arbitrary file named `0`. | Corrected to `pause>nul` for clean, silent Windows pauses. |

---

## 📂 Project Structure

```text
bank-management-system-cpp/
├── data/
│   └── Clients.example.txt    # Sample client records for testing
├── docs/
│   ├── REVIEW_AR.md           # Comprehensive architectural & code review (in Arabic)
│   └── demo-output.txt        # Sample console session capture
├── src/
│   └── main.cpp               # Complete hardened application source code
├── .gitignore                 # Configured ignores for binaries, IDE cache, and local data
└── README.md                  # Project documentation
```

---

## 🚀 Build & Run

### Prerequisites
- A modern C++ compiler supporting **C++17** (e.g. GCC/MinGW, Clang, or MSVC).
- **Windows Command Prompt** or **PowerShell**.

### 1. Build from Source

Using **GCC (MinGW)**:
```sh
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bank.exe
```

Using **MSVC**:
```cmd
cl /std:c++17 /EHsc /W4 src/main.cpp /Fe:bank.exe
```

### 2. Run the Application

```powershell
.\bank.exe
```

> [!TIP]
> **Quick Test Data:** To start with pre-populated records, copy the sample file to the working directory:
> ```powershell
> Copy-Item .\data\Clients.example.txt .\Clients.txt
> ```

---

## 🧠 Concepts & Engineering Highlights

- **Procedural Decomposition:** Single-responsibility functions with clear boundary separation between I/O, UI, and business logic.
- **Type Safety & Data Modeling:** Strong modeling using custom `struct stClient` and strongly-scoped `enum` states.
- **Stream I/O & Serialization:** Parsing custom delimited text records with defensive stream verification.
- **Defensive Console UI:** Input sanitization, stream recovery (`cin.clear()`, `cin.ignore()`), and confirmation gates.

---

## 📄 Documentation

For an in-depth breakdown of the code review findings, architectural trade-offs, and verification tests, read the **[Arabic Review Report](docs/REVIEW_AR.md)**.

---

## 👤 Author

**Abanoub Reda**
- **LinkedIn:** [Abanoub Reda](https://www.linkedin.com/in/abanoub-reda-41a633376/)
- **Email:** [abanoubreda018@gmail.com](mailto:abanoubreda018@gmail.com)
