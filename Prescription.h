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

    // Default Constructor
    Prescription()
    {
        prescriptionID = 0;
        patient = nullptr;
        doctor = nullptr;
        medication = "Not Assigned";
        dosage = "Not Assigned";
        cout << "Default Prescription created." << endl;
    }

    // Parameterized Constructor
    Prescription(int id, Patient* p, Doctor* d, string med, string dose)
    {
        prescriptionID = id;
        patient = p;
        doctor = d;
        medication = med;
        dosage = dose;
        cout << "Prescription created successfully." << endl;
    }

    // Copy Constructor
    Prescription(const Prescription& other)
    {
        prescriptionID = other.prescriptionID;
        patient = other.patient;
        doctor = other.doctor;
        medication = other.medication;
        dosage = other.dosage;
        cout << "Prescription copied." << endl;
    }

    // Generate Summary
    string generateSummary()
    {
        return "Prescription ID: " + to_string(prescriptionID) +
               "\nMedication: " + medication +
               "\nDosage: " + dosage;
    }

    // Display Details
    void displayDetails()
    {
        cout << "----- Prescription Details -----" << endl;
        cout << "ID: " << prescriptionID << endl;
        cout << "Medication: " << medication << endl;
        cout << "Dosage: " << dosage << endl;
        cout << "--------------------------------" << endl;
    }

    // Destructor
    ~Prescription()
    {
        cout << "Prescription ID " << prescriptionID
             << " is being destroyed." << endl;
    }
};

#endif
