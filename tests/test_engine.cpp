#include <cassert>
#include <cmath>
#include <iostream>

#include "Claim.h"
#include "ClaimQueue.h"
#include "Policy.h"
#include "SettlementEngine.h"

bool equal(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

void testNormalClaim() {
    Policy policy(101, 1, 500000.0, 20000.0, "ACTIVE");
    Claim claim(1001, 101, 300000.0);

    SettlementEngine engine;

    double payout = engine.processClaim(policy, claim, 0.0);

    assert(equal(payout, 280000.0));
    assert(claim.getStatus() == "APPROVED");
}

void testCoverageLimit() {
    Policy policy(101, 1, 500000.0, 20000.0, "ACTIVE");
    Claim claim1(1001, 101, 300000.0);
    Claim claim2(1002, 101, 300000.0);

    SettlementEngine engine;

    double payout1 = engine.processClaim(policy, claim1, 0.0);
    double payout2 = engine.processClaim(policy, claim2, payout1);

    assert(equal(payout1, 280000.0));
    assert(equal(payout2, 220000.0));
    assert(equal(payout1 + payout2, 500000.0));
}

void testInactivePolicy() {
    Policy policy(101, 1, 500000.0, 20000.0, "INACTIVE");
    Claim claim(1001, 101, 100000.0);

    SettlementEngine engine;

    double payout = engine.processClaim(policy, claim, 0.0);

    assert(equal(payout, 0.0));
    assert(claim.getStatus() == "REJECTED");
}

void testWrongPolicy() {
    Policy policy(101, 1, 500000.0, 20000.0, "ACTIVE");
    Claim claim(1001, 999, 100000.0);

    SettlementEngine engine;

    double payout = engine.processClaim(policy, claim, 0.0);

    assert(equal(payout, 0.0));
    assert(claim.getStatus() == "REJECTED");
}

void testBillBelowDeductible() {
    Policy policy(101, 1, 500000.0, 20000.0, "ACTIVE");
    Claim claim(1001, 101, 15000.0);

    SettlementEngine engine;

    double payout = engine.processClaim(policy, claim, 0.0);

    assert(equal(payout, 0.0));
    assert(claim.getStatus() == "REJECTED");
}

void testNoRemainingCoverage() {
    Policy policy(101, 1, 500000.0, 20000.0, "ACTIVE");
    Claim claim(1001, 101, 100000.0);

    SettlementEngine engine;

    double payout =
        engine.processClaim(policy, claim, 500000.0);

    assert(equal(payout, 0.0));
    assert(claim.getStatus() == "REJECTED");
}

void testInvalidBill() {
    Policy policy(101, 1, 500000.0, 20000.0, "ACTIVE");
    Claim claim(1001, 101, -500.0);

    SettlementEngine engine;

    double payout = engine.processClaim(policy, claim, 0.0);

    assert(equal(payout, 0.0));
    assert(claim.getStatus() == "REJECTED");
}

void testClaimQueue() {
    ClaimQueue queue;

    queue.addClaim(1001);
    queue.addClaim(1002);
    queue.addClaim(1003);

    assert(queue.size() == 3);
    assert(queue.nextClaim() == 1001);
    assert(queue.nextClaim() == 1002);
    assert(queue.nextClaim() == 1003);
    assert(queue.empty());
}

int main() {
    testNormalClaim();
    testCoverageLimit();
    testInactivePolicy();
    testWrongPolicy();
    testBillBelowDeductible();
    testNoRemainingCoverage();
    testInvalidBill();
    testClaimQueue();

    std::cout << "All tests passed.\n";

    return 0;
}
