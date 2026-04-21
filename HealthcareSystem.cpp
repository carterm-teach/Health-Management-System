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
    string dateTime;
    cout << "Enter preferred date and time (e.g. 2026-04-25 10:00AM): ";
    cin.ignore();
    getline(cin, dateTime);

    int apptId = appointments.size() + 1;
    Appointment* newAppt = new Appointment(apptId, patient, doctor, dateTime);

    // STEP 5: Compare new appointment against all existing ones using operator<
    // If neither is earlier than the other, they share the same time slot — conflict.
    cout << "\nChecking for scheduling conflicts..." << endl;
    bool conflict = false;
    for (Appointment* existing : appointments) {
        if (!(*existing < *newAppt) && !(*newAppt < *existing)) {
            cout << "CONFLICT: time slot already taken by Appointment #"
                 << existing->getAppointmentID()
                 << " (" << existing->getDateTime() << ")." << endl;
            conflict = true;
        }
    }

    if (conflict) {
        cout << "Appointment NOT scheduled — please choose a different time." << endl;
        delete newAppt;
        return;
    }

    appointments.push_back(newAppt);
    cout << "\nNo conflicts found. Appointment scheduled!" << endl;
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
