#include "Doctor.h"
#include "Appointment.h"
#include "MedicalRecord.h"
#include "Prescription.h"
#include "Patient.h"
#include <iostream>
#include "User.h"

// Dummy class definitions (for standalone compilation)
class Appointment {};
class Patient {};
class MedicalRecord {
public:
    MedicalRecord(Patient&, const std::string&, const std::string&) {}
};
class Prescription {
public:
    Prescription(Patient&, const std::string&, const std::string&) {}
};

// Default constructor
Doctor::Doctor()
    : User(), specialty("") {
}

// Main constructor — FIXED
Doctor::Doctor(int userID,
    const std::string& name,
    const std::string& email,
    const std::string& specialty)
    : User(userID, name, email), specialty(specialty) {
}

// Copy constructor — FIXED
Doctor::Doctor(const Doctor& other)
    : User(other), specialty(other.specialty), schedule(other.schedule) {
}

// Destructor
Doctor::~Doctor() {}

bool Doctor::approveAppointment(Appointment& appointment) {
    std::cout << "Appointment approved.\n";
    return true;
}

void Doctor::denyAppointment(Appointment& appointment) {
    std::cout << "Appointment denied.\n";
}

MedicalRecord Doctor::createMedicalRecord(Patient& patient,
    const std::string& diagnosis,
    const std::string& notes) {
    return MedicalRecord(patient, diagnosis, notes);
}

Prescription Doctor::issuePrescription(Patient& patient,
    const std::string& medication,
    const std::string& dosage) {
    return Prescription(patient, medication, dosage);
}

void Doctor::setSpecialty(const std::string& newSpecialty) {
    specialty = newSpecialty;
}

void Doctor::displayInfo() const {
    std::cout << "Doctor Information:\n"
        << "Name: " << getName() << "\n"
        << "Email: " << getEmail() << "\n"
        << "Specialty: " << specialty << "\n";
}