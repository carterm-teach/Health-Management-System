// STUB - Placeholder until Taelon's full Billing implementation is ready.
// Do not modify this file — replace it entirely with Billing.h from Taelon.
// The 'amount' and 'status' fields must remain with these exact names and types
// because Insurance::AdjustBilling() accesses them directly as a friend class.
#ifndef BILLING_H
#define BILLING_H

#include <string>

class Insurance;

class Billing {
    friend class Insurance; // Insurance must directly access private members per the spec
private:
    double amount;
    std::string status;
public:
    Billing() : amount(0.0), status("Unpaid") {}
    Billing(double amt) : amount(amt), status("Unpaid") {}
};

#endif
