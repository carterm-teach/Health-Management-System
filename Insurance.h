#ifndef INSURANCE_H
#define INSURANCE_H
#include <iostream>
#include <string>
using namespace std;
// Forward declaration so we can reference Billing
class Billing;
class Insurance
{
private:
string providerName;
string policyNumber;
double coveragePercent;
public:
// Default Constructor
Insurance();
// Parameterized Constructor
Insurance(string provider, string policy, double coverage);
// Destructor - logs which object is being destroyed
~Insurance();
// Validate claim
bool ValidateClaim(double billAmount) const;
// Must directly modify Billing's private data
void AdjustBilling(Billing &bill);
};
#endif
