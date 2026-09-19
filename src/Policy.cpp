#include "Policy.h"

Policy::Policy(int id,
               int customer,
               double limit,
               double ded,
               const std::string& stat)
    : policyId(id),
      customerId(customer),
      coverageLimit(limit),
      deductible(ded),
      status(stat) {
}

int Policy::getPolicyId() const {
    return policyId;
}

int Policy::getCustomerId() const {
    return customerId;
}

double Policy::getCoverageLimit() const {
    return coverageLimit;
}

double Policy::getDeductible() const {
    return deductible;
}

const std::string& Policy::getStatus() const {
    return status;
}

bool Policy::isActive() const {
    return status == "ACTIVE";
}
