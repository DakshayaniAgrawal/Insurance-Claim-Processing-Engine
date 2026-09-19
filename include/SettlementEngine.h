#pragma once

#include "Claim.h"
#include "Policy.h"

class SettlementEngine {
public:
    bool validateClaim(const Policy& policy, const Claim& claim) const;

    double calculatePayout(const Policy& policy,
                           const Claim& claim,
                           double usedCoverage) const;

    double processClaim(Policy& policy,
                        Claim& claim,
                        double usedCoverage) const;
};
