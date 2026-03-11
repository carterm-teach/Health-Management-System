#include "HealthcareSystem.h"
#include <iostream>
using namespace std;
HealthcareSystem::HealthcareSystem() {
cout << "Healthcare System initialized." << endl;
}
HealthcareSystem::~HealthcareSystem() {
for (User* user : users) {
delete user;
}
for (Appointment* appt : appointments) {
delete appt;
}
for (MedicalRecord* record : records) {
delete record;
}
cout << "Healthcare System destroyed and memory cleaned." << endl;
}
void HealthcareSystem::registerUser(User* user) {
users.push_back(user);
cout << "User registered." << endl;
}
void HealthcareSystem::scheduleAppointment(Appointment* appointment) {
appointments.push_back(appointment);
cout << "Appointment scheduled." << endl;
}
void HealthcareSystem::addMedicalRecord(MedicalRecord* record) {
records.push_back(record);
cout << "Medical record added." << endl;
}
void HealthcareSystem::manageSystemOperations() {
cout << "Managing system operations..." << endl;
}
void HealthcareSystem::generateReport() const {
cout << "\n===== System Report =====" << endl;
cout << "Total Users: " << users.size() << endl;
cout << "Total Appointments: " << appointments.size() << endl;
cout << "Total Medical Records: " << records.size() << endl;
}
