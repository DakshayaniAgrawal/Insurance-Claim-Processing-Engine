#include "ClaimQueue.h"

void ClaimQueue::addClaim(int claimId) {
    pendingClaims.push(claimId);
}

bool ClaimQueue::empty() const {
    return pendingClaims.empty();
}

int ClaimQueue::nextClaim() {
    if (pendingClaims.empty()) {
        return -1;
    }

    int claimId = pendingClaims.front();
    pendingClaims.pop();

    return claimId;
}

std::size_t ClaimQueue::size() const {
    return pendingClaims.size();
}
