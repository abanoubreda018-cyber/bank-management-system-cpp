# Bank Management System — C++ Console

A console learning project by **Abanoub Reda** for managing client records and practicing C++ functions, structures, vectors, menus, and text-file persistence.

**Current snapshot:** the original source is preserved. Core workflows have been checked, and the validation and persistence issues found during review are documented in [the Arabic review](docs/REVIEW_AR.md). This is an educational simulation.

## Features

- List, add, find, update, and delete clients.
- Check for an existing account number before adding a client.
- Deposit funds and withdraw within the available balance.
- Reject non-positive deposit and withdrawal amounts.
- Display individual and total account balances.
- Store records in a local text file using the `#//#` separator.

Client records contain an account number, PIN field, name, phone number, and balance. The PIN field is stored and displayed; it is not an authentication mechanism.

## Versions and files

| Path | Purpose |
| --- | --- |
| `src/main.cpp` | Latest supplied version, originally `53-BankProject.cpp`; includes transactions. |
| `legacy/52-BankProject.cpp` | Earlier standalone version with client management. |
| `data/Clients.example.txt` | Two fictional records for a local demonstration. |
| `docs/REVIEW_AR.md` | Findings, evidence, and a suggested improvement order, in Arabic. |
| `docs/demo-output.txt` | Console output captured from the latest version using the sample records. |

The two `.cpp` files are separate programs, each with its own `main`. Compile only one version at a time.

## Build and run

The console commands in the original source (`cls` and `pause`) target Windows.

From the repository root, with a C++ compiler available on your PATH:

```sh
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bank.exe
```

Run in Windows PowerShell:

```powershell
.\bank.exe
```

The application reads and writes `Clients.txt` in its current working directory. You can start without that file and add a client through the menu. For the sample demonstration, copy `data/Clients.example.txt` to a new `Clients.txt` in the repository root. Keep any existing data file separately before using the sample.

## Concepts practiced

- Procedural decomposition using functions.
- Structures, enumerations, strings, and vectors.
- File streams and record serialization.
- Menu navigation and confirmation prompts.
- Basic input validation and formatted console output.

## Verification and next improvements

Both supplied versions compiled with GCC 13 in C++17 mode. Nine functional checks covered the latest version's main workflows and a basic check of the earlier version. Eight additional probes reproduced the issues described in the review; those are findings to fix, not claims that the application is defect-free.

Functional checks ran on Linux with temporary stand-ins for the Windows-only `cls` and `pause` commands. Native Windows console behavior was not verified.

The next improvements are consistent input validation, safe handling of invalid records, checked file writes, and an exit path when a client with zero balance enters the withdrawal screen.

## Author

**Abanoub Reda** · [LinkedIn](https://www.linkedin.com/in/abanoub-reda-41a633376/) · [Email](mailto:abanoubreda018@gmail.com)
