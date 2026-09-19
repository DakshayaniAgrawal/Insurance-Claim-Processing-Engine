#pragma once

#include <string>

class Claim {
private:
    int claimId;
    int policyId;
    double hospitalBill;
    double approvedAmount;
    std::string status;

public:
    Claim(int id, int policy, double bill);

    int getClaimId() const;
    int getPolicyId() const;
    double getHospitalBill() const;
    double getApprovedAmount() const;
    const std::string& getStatus() const;

    void setApprovedAmount(double amount);
    void setStatus(const std::string& newStatus);
};
