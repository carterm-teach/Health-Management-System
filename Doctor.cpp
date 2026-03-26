#include "Doctor.h"
#include <iostream>
#include "User.h"

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

Doctor::Doctor()
    : User(), name(""), specialty("") {
}

Doctor::Doctor(int userID,
    const std::string& name,
    const std::string& email,
    const std::string& specialty)
    : User(userID, name, email), name(name), specialty(specialty) {
}

Doctor::Doctor(const Doctor& other)
    : User(other.userID, other.name, other.email),
    name(other.name),
    specialty(other.specialty),
    schedule(other.schedule) {
}

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

void Doctor::displayInfo() const {
    std::cout << "Doctor Name: " << name << "\n"
        << "Specialty: " << specialty << "\n"
        << "Email: " << email << "\n";
}

// int main() {
//     Doctor d("D001", "Dr. Burkins", "drBurkins@email.com", "Cardiology");
//     d.displayInfo();
//     return 0;
// }
