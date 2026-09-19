USE insurance_engine;

INSERT INTO customers (name, email)
VALUES
    ('Rahul Sharma', 'rahul@example.com'),
    ('Ananya Mehta', 'ananya@example.com');

INSERT INTO policies
    (customer_id, coverage_limit, deductible, status)
VALUES
    (1, 500000.00, 20000.00, 'ACTIVE'),
    (2, 300000.00, 10000.00, 'ACTIVE');

INSERT INTO claims
    (policy_id, hospital_bill, claim_status, approved_amount)
VALUES
    (1, 300000.00, 'APPROVED', 280000.00),
    (1, 300000.00, 'APPROVED', 220000.00),
    (2, 50000.00, 'PENDING', 0.00);

INSERT INTO settlements
    (claim_id, payout)
VALUES
    (1, 280000.00),
    (2, 220000.00);
