#include "SettlementEngine.h"

#include <algorithm>

bool SettlementEngine::validateClaim(const Policy& policy,
                                     const Claim& claim) const {
    if (!policy.isActive()) {
        return false;
    }

    if (claim.getHospitalBill() <= 0.0) {
        return false;
    }

    if (claim.getPolicyId() != policy.getPolicyId()) {
        return false;
    }

    return true;
}

double SettlementEngine::calculatePayout(const Policy& policy,
                                         const Claim& claim,
                                         double usedCoverage) const {
    double remainingCoverage =
        policy.getCoverageLimit() - usedCoverage;

    if (remainingCoverage <= 0.0) {
        return 0.0;
    }

    double eligibleAmount =
        claim.getHospitalBill() - policy.getDeductible();

    if (eligibleAmount <= 0.0) {
        return 0.0;
    }

    return std::min(eligibleAmount, remainingCoverage);
}

double SettlementEngine::processClaim(Policy& policy,
                                      Claim& claim,
                                      double usedCoverage) const {
    if (!validateClaim(policy, claim)) {
        claim.setStatus("REJECTED");
        claim.setApprovedAmount(0.0);
        return 0.0;
    }

    double payout =
        calculatePayout(policy, claim, usedCoverage);

    if (payout <= 0.0) {
        claim.setStatus("REJECTED");
        claim.setApprovedAmount(0.0);
        return 0.0;
    }

    claim.setApprovedAmount(payout);
    claim.setStatus("APPROVED");

    return payout;
}
