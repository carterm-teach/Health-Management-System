#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <iostream>
#include <string>
using namespace std;

// Forward declaration
class Patient;
class Doctor;

class Prescription
{
private:
    int prescriptionID;
    Patient* patient;   // Aggregation
    Doctor* doctor;     // Aggregation
    string medication;
    string dosage;

public:

    Prescription();
    Prescription(int id, Patient* p, Doctor* d, string med, string dose);
    Prescription(const Prescription& other);
    ~Prescription();
    string generateSummary();
    void displayDetails();
};

#endif
