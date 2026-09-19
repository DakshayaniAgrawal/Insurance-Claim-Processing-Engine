# Insurance Claim Processing Engine

A C++/MySQL project that simulates insurance claim settlement with policy-level coverage limits, deductibles, claim validation, FIFO claim processing, and persistent claim/settlement records.

## Features

- Object-oriented C++ design using `Policy`, `Claim`, and `SettlementEngine`
- Policy coverage and deductible handling
- Multiple claims against the same policy
- Automatic tracking of remaining coverage
- Claim validation and rejection for invalid/inactive policies
- FIFO pending-claim processing using `std::queue`
- In-memory policy/claim management using STL containers
- MySQL schema for customers, policies, claims, and settlements
- SQL constraints for financial data integrity
- Unit-style tests for important edge cases
- CMake build configuration

## Example

For a policy with:

- Coverage limit = ₹5,00,000
- Deductible = ₹20,000
- Claim 1 = ₹3,00,000
- Claim 2 = ₹3,00,000

The engine calculates:

```text
Claim 1 payout = ₹2,80,000
Remaining coverage = ₹2,20,000

Claim 2 payout = ₹2,20,000
Remaining coverage = ₹0
```

The second claim is capped by the remaining policy coverage.

## Project Structure

```text
Insurance-Claim-Processing-Engine/
│
├── CMakeLists.txt
├── README.md
├── .gitignore
├── LICENSE
│
├── include/
│   ├── Claim.h
│   ├── Policy.h
│   ├── SettlementEngine.h
│   └── ClaimQueue.h
│
├── src/
│   ├── Claim.cpp
│   ├── Policy.cpp
│   ├── SettlementEngine.cpp
│   ├── ClaimQueue.cpp
│   └── main.cpp
│
├── tests/
│   └── test_engine.cpp
│
├── database/
│   ├── schema.sql
│   └── sample_data.sql
│
└── docs/
    └── DESIGN.md
```

## Requirements

### Core C++ version

- C++17 or newer
- CMake 3.15+
- Any C++17 compiler

### MySQL

- MySQL 8.0+
- The SQL scripts can be executed directly in MySQL Workbench or the MySQL command line.

## Build and Run

### Linux/macOS

```bash
mkdir build
cd build
cmake ..
cmake --build .
./insurance_engine
```

### Windows

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
.\Release\insurance_engine.exe
```

## Run Tests

```bash
cmake --build build --target test_engine
./build/test_engine
```

On Windows:

```powershell
.\build\Debug\test_engine.exe
```

## Database Setup

Start MySQL and run:

```sql
SOURCE database/schema.sql;
SOURCE database/sample_data.sql;
```

Or open both files in MySQL Workbench and execute them in order.

The database contains:

- `customers`
- `policies`
- `claims`
- `settlements`

The C++ settlement logic is intentionally kept independent from the database layer so the core financial rules can be tested without requiring a live database connection.

## Important Settlement Rules

The engine follows these simplified rules:

1. Policy must be active.
2. Hospital bill must be positive.
3. Eligible amount is:

```text
eligible amount = hospital bill - deductible
```

4. Remaining policy coverage is:

```text
remaining coverage = coverage limit - previous approved payouts
```

5. Final payout is:

```text
min(eligible amount, remaining coverage)
```

6. If no coverage remains, the claim is rejected.

This is a simplified educational project. Real insurance systems can include co-pay, exclusions, room-rent limits, waiting periods, network rules, fraud investigation, pre-authorization, sub-limits, tax treatment, and many other policy-specific rules.

## GitHub

After creating the repository:

```bash
git init
git add .
git commit -m "Initial insurance claim processing engine"
git branch -M main
git remote add origin YOUR_GITHUB_REPOSITORY_URL
git push -u origin main
```
