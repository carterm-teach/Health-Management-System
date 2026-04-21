#include "HealthcareSystem.h"
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "MedicalRecord.h"
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
void HealthcareSystem::scheduleAppointment(Patient* patient, Doctor* doctor) {
    // STEP 2 & 3: Patient requests appointment → HealthcareSystem creates Appointment
    // Collect the preferred date/time from the user
    string dateTime;
    cout << "Enter preferred date and time (e.g. 2026-04-15 10:00AM): ";
    cin.ignore();
    getline(cin, dateTime);

    // Auto-assign appointment ID based on how many appointments already exist
    int apptId = appointments.size() + 1;

    // Create the Appointment using Landon's class — status starts as "Pending" automatically
    Appointment* newAppt = new Appointment(apptId, patient, doctor, dateTime);
    appointments.push_back(newAppt);

    cout << "\nAppointment requested successfully!" << endl;
    cout << "Appointment ID : " << newAppt->getAppointmentID() << endl;
    cout << "Patient        : " << patient->getname() << endl;
    cout << "Doctor         : " << doctor->getname() << endl;
    cout << "Date/Time      : " << newAppt->getDateTime() << endl;
    cout << "Status         : " << newAppt->getStatus() << endl;
}
User* HealthcareSystem::findUser(const string& name) const {
for (User* user : users) {
    if (user->getname() == name) {
        return user;
    }
}
return nullptr;
}
const vector<Appointment*>& HealthcareSystem::getAppointments() const {
return appointments;
}
User* HealthcareSystem::findUserById(int id) const {
for (User* user : users) {
    if (user->getuserID() == id) {
        return user;
    }
}
return nullptr;
}
