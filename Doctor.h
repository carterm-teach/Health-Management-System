#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include "User.h"
#include "Doctor.h"

class Appointment;
class MedicalRecord;
class Prescription;
class Patient;

class Doctor : public User {
private:
    std::string name;
    std::string specialty;
    std::vector<Appointment*> schedule;

public:
    Doctor();
    Doctor(int userID,
        const std::string& name,
        const std::string& email,
        const std::string& specialty);
    Doctor(const Doctor& other);
    ~Doctor();

    bool approveAppointment(Appointment& appointment);
    void denyAppointment(Appointment& appointment);

    MedicalRecord createMedicalRecord(Patient& patient,
        const std::string& diagnosis,
        const std::string& notes);

    Prescription issuePrescription(Patient& patient,
        const std::string& medication,
        const std::string& dosage);

    void displayInfo() const;
};

#endif
