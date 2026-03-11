#include "insurance.h"
#include "Billing.h" // Billing must declare: friend class Insurance;
// Default Constructor
Insurance::Insurance()
{
providerName = "Unknown Provider";
policyNumber = "N/A";
coveragePercent = 0.0;
}
// Parameterized Constructor
Insurance::Insurance(string provider, string policy, double coverage)
{
providerName = provider;
policyNumber = policy;
coveragePercent = coverage;
}
// Destructor - logs which object is being destroyed
Insurance::~Insurance()
{
cout << "Insurance object destroyed - Provider: "
<< providerName << " | Policy: " << policyNumber << endl;
}
// Validate claim
bool Insurance::ValidateClaim(double billAmount) const
{
return (billAmount > 0 && coveragePercent > 0);
}
// Must directly modify Billing's private data
void Insurance::AdjustBilling(Billing &bill)
{
if (!ValidateClaim(bill.amount))
return;
bill.amount -= (coveragePercent / 100.0) * bill.amount;
bill.status = "Adjusted by Insurance";
}
