#ifndef PATIENT_H
#define PATIENT_H
#include "User.h"
#include "Insurance.h"
#include "MedicalRecord.h"
#include "Patient.h"
#include "Doctor.h"
#include "HealthcareSystem.h"
#include <vector>
#include <string>
class Patient : public User {
private:
Insurance* insurance; 
std::vector<MedicalRecord*> medicalHistory; 
public:
Patient();
Patient(int id, std::string name, std::string email, Insurance* insurance);
Patient(const Patient& other);
~Patient();
void requestAppointment(HealthcareSystem& system, Doctor* doctor);
void viewMedicalHistory();
void addMedicalRecord(const MedicalRecord& record);
};
#end
