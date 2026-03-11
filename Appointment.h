#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
using namespace std;
// Forward declarations (aggregation relationship)
class Patient;
class Doctor;
class Appointment
{
private:
int appointmentID;
Patient* patient;
Doctor* doctor;
string dateTime;
string status;
public:
// Constructors
Appointment();
Appointment(int id, Patient* p, Doctor* d, string dt);
Appointment(const Appointment& other);
// Destructor
~Appointment();
// Member functions
void confirmAppointment();
void cancelAppointment();
void updateStatus(string newStatus);
// Operator overload for comparing appointments by date/time
bool operator<(const Appointment& other) const;
// Optional getters
int getAppointmentID() const;
string getDateTime() const;
string getStatus() const;
