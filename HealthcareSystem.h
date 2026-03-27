#ifndef HEALTHCARESYSTEM_H
#define HEALTHCARESYSTEM_H
#include <vector>
#include <string>
class User;
class Patient;
class Doctor;
class Appointment;
class MedicalRecord;
class HealthcareSystem {
private:
std::vector<User*> users;
std::vector<Appointment*> appointments;
std::vector<MedicalRecord*> records;
public:
HealthcareSystem(); // constructor
~HealthcareSystem(); // destructor
void registerUser(User* user);
void scheduleAppointment(Appointment* appointment);
void scheduleAppointment(Patient* patient, Doctor* doctor); // called by Patient::requestAppointment
void addMedicalRecord(MedicalRecord* record);
void manageSystemOperations();
void generateReport() const;
User* findUser(const std::string& name) const;
User* findUserById(int id) const;
};
#endif
