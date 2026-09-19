DROP DATABASE IF EXISTS insurance_engine;

CREATE DATABASE insurance_engine;

USE insurance_engine;

CREATE TABLE customers (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE
);

CREATE TABLE policies (
    policy_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT NOT NULL,
    coverage_limit DECIMAL(12,2) NOT NULL,
    deductible DECIMAL(12,2) NOT NULL DEFAULT 0.00,
    status ENUM('ACTIVE', 'INACTIVE', 'EXPIRED') NOT NULL DEFAULT 'ACTIVE',

    CONSTRAINT fk_policy_customer
        FOREIGN KEY (customer_id)
        REFERENCES customers(customer_id),

    CONSTRAINT chk_policy_coverage
        CHECK (coverage_limit > 0),

    CONSTRAINT chk_policy_deductible
        CHECK (deductible >= 0 AND deductible <= coverage_limit)
);

CREATE TABLE claims (
    claim_id INT PRIMARY KEY AUTO_INCREMENT,
    policy_id INT NOT NULL,
    hospital_bill DECIMAL(12,2) NOT NULL,
    claim_status ENUM('PENDING', 'APPROVED', 'REJECTED') NOT NULL DEFAULT 'PENDING',
    approved_amount DECIMAL(12,2) NOT NULL DEFAULT 0.00,
    created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_claim_policy
        FOREIGN KEY (policy_id)
        REFERENCES policies(policy_id),

    CONSTRAINT chk_claim_bill
        CHECK (hospital_bill > 0),

    CONSTRAINT chk_claim_approved_amount
        CHECK (approved_amount >= 0)
);

CREATE TABLE settlements (
    settlement_id INT PRIMARY KEY AUTO_INCREMENT,
    claim_id INT NOT NULL UNIQUE,
    payout DECIMAL(12,2) NOT NULL,
    settlement_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_settlement_claim
        FOREIGN KEY (claim_id)
        REFERENCES claims(claim_id),

    CONSTRAINT chk_settlement_payout
        CHECK (payout >= 0)
);

CREATE INDEX idx_policies_customer
    ON policies(customer_id);

CREATE INDEX idx_claims_policy
    ON claims(policy_id);

CREATE INDEX idx_claims_status
    ON claims(claim_status);
