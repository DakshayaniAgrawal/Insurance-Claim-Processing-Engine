# System Design

## 1. Main Objects

### Policy

Stores:

- Policy ID
- Customer ID
- Coverage limit
- Deductible
- Policy status

### Claim

Stores:

- Claim ID
- Policy ID
- Hospital bill
- Approved payout
- Claim status

### SettlementEngine

Responsible for:

- Claim validation
- Eligible amount calculation
- Remaining coverage calculation
- Final payout calculation
- Claim status update

### ClaimQueue

Uses `std::queue<int>` to process pending claims in FIFO order.

## 2. Settlement Formula

```text
Eligible Amount =
    Hospital Bill - Deductible

Remaining Coverage =
    Coverage Limit - Previous Approved Payouts

Final Payout =
    min(Eligible Amount, Remaining Coverage)
```

## 3. Example

```text
Coverage limit = Rs. 5,00,000
Deductible = Rs. 20,000

Claim 1 = Rs. 3,00,000
Claim 1 eligible amount = Rs. 2,80,000
Claim 1 payout = Rs. 2,80,000

Remaining coverage = Rs. 2,20,000

Claim 2 = Rs. 3,00,000
Claim 2 eligible amount = Rs. 2,80,000
Claim 2 payout = Rs. 2,20,000

Remaining coverage = Rs. 0
```

## 4. Edge Cases

The engine handles:

- Inactive/expired policies
- Negative or zero hospital bills
- Claim belonging to another policy
- Hospital bill below deductible
- No remaining coverage
- Claim amount exceeding remaining coverage

## 5. Complexity

For the core settlement calculation:

```text
validateClaim()    O(1)
calculatePayout()  O(1)
processClaim()     O(1)
```

The queue operations are:

```text
push()  O(1)
pop()   O(1)
front() O(1)
```

The demonstration program uses a small array search to locate a claim by ID. A production implementation could use `std::unordered_map<int, Claim>` for average O(1) lookup.

## 6. Database Design

```text
customers
    |
    | 1 : many
    v
policies
    |
    | 1 : many
    v
claims
    |
    | 1 : 1
    v
settlements
```

Foreign keys maintain referential integrity.

Financial columns use `DECIMAL(12,2)` rather than floating-point SQL types.

For a production financial system, the C++ monetary representation should also preferably use integer minor units (for example, paise) or a decimal-money library rather than binary floating-point values.
