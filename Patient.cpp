
Fit Page



Drawing



Image







Line





#include "User.h"
#include "Insurance.h"
#include "MedicalRecord.h"
#include "Patient.h"
#include "Doctor.h"
#include "HealthcareSystem.h"
#include <iostream>
using namespace std;
Patient::Patient() : User(), insurance(nullptr) {}
Patient::Patient(int id, string name, string email, Insurance* ins)
: User(id, name, email) {
insurance = ins;
}
Patient::Patient(const Patient& other) 
: User(other) {
insurance = other.insurance; 
for (auto record : other.medicalHistory) {
medicalHistory.push_back(new MedicalRecord(*record));
}
}
Patient::~Patient() {
for (auto record : medicalHistory) {
delete record;
}
medicalHistory.clear();
}
void Patient::requestAppointment(HealthcareSystem& system, Doctor* doctor)
{
system.scheduleAppointment(this, doctor);
}
void Patient::viewMedicalHistory() {
for (auto record : medicalHistory) {
record->displayRecord();
}
}
void Patient::addMedicalRecord(const MedicalRecord& record) {
medicalHistory.push_back(new MedicalRecord(record));
