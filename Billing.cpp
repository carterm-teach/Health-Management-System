#include <iostream>
#include "Billing.h"
using namespace std;
// Default constructor
Billing::Billing()
{
billID = 0;
patient = "Unknown";
amount = 0.0;
status = "Unpaid";
}
// Parameterized constructor
Billing::Billing(int id, string patientName, double amt, string stat)
{
billID = id;
patient = patientName;
amount = amt;
status = stat;
}
// Copy constructor
Billing::Billing(const Billing &other)
{
billID = other.billID;
patient = other.patient;
amount = other.amount;
status = other.status;
}
// Destructor
Billing::~Billing()
{
cout << "Destroying Billing Record -> "
<< "BillID: " << billID
<< ", Patient: " << patient
<< ", Amount: $" << amount
<< ", Status: " << status
<< endl;
}
// Generate a new bill
void Billing::generateBill(int id, string patientName, double billAmount)
{
billID = id;
patient = patientName;
amount = billAmount;
status = "Unpaid";
}
// Process a payment
void Billing::processPayment(double payment)
{
if (payment <= 0)
{
cout << "Invalid payment amount!" << endl;
return;
}
if (payment >= amount)
{
amount = 0.0;
status = "Paid";
cout << "Payment complete. Bill is now paid." << endl;
}
else
{
amount -= payment;
cout << "Partial payment applied. Remaining balance: $" << amount << endl;
}
}
// Adjust charges
void Billing::adjustCharges(double adjustment)
{
amount += adjustment;
cout << "Charges adjusted. New amount: $" << amount << endl;
}

// Combine two bills — returns a new bill with summed amounts
Billing Billing::operator+(const Billing& other) const
{
static int combinedID = 1000;
return Billing(combinedID++, patient + " & " + other.patient, amount + other.amount, "Unpaid");
}
// Convert billing amount to double for numeric reporting
Billing::operator double() const
{
return amount;
}
// Display bill details
void Billing::displayBill() const
{
cout << "\n----- BILL DETAILS -----" << endl;
cout << "Bill ID: " << billID << endl;
cout << "Patient: " << patient << endl;
cout << "Amount: $" << amount << endl;
cout << "Status: " << status << endl;
cout << "------------------------" << endl;
return;
}
//Getters
int Billing::getBillID() const
{
    return billID;
}
double Billing::getAmount() const
{
    return amount;
}
string Billing::getStatus() const
{
    return status;
}
string Billing::getPatient() const
{
    return patient;
}
