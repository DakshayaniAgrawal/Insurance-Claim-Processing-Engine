#pragma once

#include <string>

class Policy {
private:
    int policyId;
    int customerId;
    double coverageLimit;
    double deductible;
    std::string status;

public:
    Policy(int id,
           int customer,
           double limit,
           double ded,
           const std::string& stat);

    int getPolicyId() const;
    int getCustomerId() const;
    double getCoverageLimit() const;
    double getDeductible() const;
    const std::string& getStatus() const;

    bool isActive() const;
};
