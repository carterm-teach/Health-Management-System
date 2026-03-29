#ifndef BILLING_H
#define BILLING_H
#include <string>
#include <iostream>
using namespace std;
class Billing
{
private:
int billID; // Bill identification number
string patient; // Patient name
double amount; // Total bill amount
string status; // Payment status
// Private helper function to initialize a bill
void initializeBill(int id, string patientName, double billAmount, string billStatus)
{
billID = id;
patient = patientName;
amount = billAmount;
status = billStatus;
}
public:
// Default Constructor
Billing();
// Parameterized Constructor
Billing(int billID, string patient, double amount, string status);
// Copy Constructor
Billing(const Billing &other);
// Destructor
~Billing();
// Member Functions
void generateBill(int id, string patientName, double billAmount);
void processPayment(double payment);
void adjustCharges(double adjustment);
// Display Function
void displayBill() const;
};
#endif
