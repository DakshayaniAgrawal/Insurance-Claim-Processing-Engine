#pragma once

#include <queue>

class ClaimQueue {
private:
    std::queue<int> pendingClaims;

public:
    void addClaim(int claimId);
    bool empty() const;
    int nextClaim();
    std::size_t size() const;
};
