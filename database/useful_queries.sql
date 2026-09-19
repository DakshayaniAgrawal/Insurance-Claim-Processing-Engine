USE insurance_engine;

-- View policies with customers
SELECT
    p.policy_id,
    c.name,
    p.coverage_limit,
    p.deductible,
    p.status
FROM policies p
JOIN customers c
    ON p.customer_id = c.customer_id;

-- Calculate total approved payout per policy
SELECT
    p.policy_id,
    p.coverage_limit,
    COALESCE(SUM(c.approved_amount), 0) AS total_paid,
    p.coverage_limit - COALESCE(SUM(c.approved_amount), 0)
        AS remaining_coverage
FROM policies p
LEFT JOIN claims c
    ON p.policy_id = c.policy_id
    AND c.claim_status = 'APPROVED'
GROUP BY p.policy_id, p.coverage_limit;

-- Show all claims
SELECT
    claim_id,
    policy_id,
    hospital_bill,
    claim_status,
    approved_amount,
    created_at
FROM claims
ORDER BY created_at;
