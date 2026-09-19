#include <iomanip>
#include <iostream>

#include "Claim.h"
#include "ClaimQueue.h"
#include "Policy.h"
#include "SettlementEngine.h"

void printClaimResult(const Claim& claim,
                      double payout,
                      double remainingCoverage) {
    std::cout << "Claim " << claim.getClaimId() << '\n';
    std::cout << "Status: " << claim.getStatus() << '\n';
    std::cout << "Hospital bill: Rs. "
              << claim.getHospitalBill() << '\n';
    std::cout << "Payout: Rs. "
              << payout << '\n';
    std::cout << "Remaining coverage: Rs. "
              << remainingCoverage << "\n\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // Policy:
    // Coverage = Rs. 5,00,000
    // Deductible = Rs. 20,000
    Policy policy(
        101,
        1,
        500000.0,
        20000.0,
        "ACTIVE"
    );

    SettlementEngine engine;

    Claim claim1(1001, 101, 300000.0);
    Claim claim2(1002, 101, 300000.0);
    Claim claim3(1003, 101, 50000.0);

    // FIFO queue for pending claims.
    ClaimQueue pendingClaims;
    pendingClaims.addClaim(claim1.getClaimId());
    pendingClaims.addClaim(claim2.getClaimId());
    pendingClaims.addClaim(claim3.getClaimId());

    std::cout << "Insurance Claim Processing Engine\n";
    std::cout << "================================\n\n";

    double usedCoverage = 0.0;

    // Claims are demonstrated individually here so that the
    // settlement calculation remains easy to follow.
    Claim* claims[] = {&claim1, &claim2, &claim3};

    while (!pendingClaims.empty()) {
        int currentId = pendingClaims.nextClaim();

        Claim* currentClaim = nullptr;

        for (Claim* claim : claims) {
            if (claim->getClaimId() == currentId) {
                currentClaim = claim;
                break;
            }
        }

        if (currentClaim == nullptr) {
            continue;
        }

        double payout =
            engine.processClaim(
                policy,
                *currentClaim,
                usedCoverage
            );

        usedCoverage += payout;

        printClaimResult(
            *currentClaim,
            payout,
            policy.getCoverageLimit() - usedCoverage
        );
    }

    return 0;
}
