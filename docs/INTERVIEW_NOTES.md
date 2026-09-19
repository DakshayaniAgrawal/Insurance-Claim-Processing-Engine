# Interview Notes

## Why C++?

C++ was used for the settlement engine because it provides strong object-oriented design, efficient data structures, and explicit control over the processing logic.

## Why MySQL?

MySQL is used to persist customers, policies, claims, and settlements while foreign keys and SQL constraints protect data integrity.

## How is the payout calculated?

First, the deductible is removed from the hospital bill.

```text
eligible = bill - deductible
```

Then the engine calculates how much policy coverage remains.

```text
remaining = coverage limit - previous payouts
```

Finally:

```text
payout = min(eligible, remaining)
```

## How are multiple claims handled?

The engine tracks the total approved amount already paid under a policy. Every new claim is capped by the remaining policy coverage.

## Why use a queue?

Pending claims are processed in FIFO order using `std::queue`, which is appropriate for a simple claim-processing workflow.

## Why foreign keys?

A claim should not exist for a policy that does not exist. Foreign keys enforce this relationship at the database level.

## What edge cases were considered?

- Policy inactive/expired
- Bill <= 0
- Bill <= deductible
- Wrong policy ID
- Coverage fully exhausted
- Claim exceeding remaining coverage

## What would you add next?

Possible extensions:

- Co-pay percentage
- Policy exclusions
- Hospital network rules
- Fraud-risk scoring
- Claim priority
- Audit logs
- REST API
- Authentication and authorization
- Database transaction handling
- MySQL connector integration
- Decimal/integer minor-unit money handling
