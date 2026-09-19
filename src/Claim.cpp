#include "Claim.h"

Claim::Claim(int id, int policy, double bill)
    : claimId(id),
      policyId(policy),
      hospitalBill(bill),
      approvedAmount(0.0),
      status("PENDING") {
}

int Claim::getClaimId() const {
    return claimId;
}

int Claim::getPolicyId() const {
    return policyId;
}

double Claim::getHospitalBill() const {
    return hospitalBill;
}

double Claim::getApprovedAmount() const {
    return approvedAmount;
}

const std::string& Claim::getStatus() const {
    return status;
}

void Claim::setApprovedAmount(double amount) {
    approvedAmount = amount;
}

void Claim::setStatus(const std::string& newStatus) {
    status = newStatus;
}
