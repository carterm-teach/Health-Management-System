#include <iostream>
#include "Appointment.h"
using namespace std;
// Default constructor
Appointment::Appointment()
{
appointmentID = 0;
patient = nullptr;
doctor = nullptr;
dateTime = "";
status = "Pending";
}
// Parameterized constructor
Appointment::Appointment(int id, Patient* p, Doctor* d, string dt)
{
appointmentID = id;
patient = p;
doctor = d;
dateTime = dt;
status = "Pending";
}
// Copy constructor
Appointment::Appointment(const Appointment& other)
{
appointmentID = other.appointmentID;
patient = other.patient;
doctor = other.doctor;
dateTime = other.dateTime;
status = other.status;
}
// Destructor
Appointment::~Appointment()
{
cout << "Appointment " << appointmentID << " destroyed." << endl;
}
// Confirm appointment
void Appointment::confirmAppointment()
{
status = "Confirmed";
}
// Cancel appointment
void Appointment::cancelAppointment()
{
status = "Cancelled";
}
// Update appointment status
void Appointment::updateStatus(string newStatus)
{
status = newStatus;
}
// Operator overload for comparing appointment date/time
bool Appointment::operator<(const Appointment& other) const
{
return dateTime < other.dateTime;
}
// Getter functions
int Appointment::getAppointmentID() const
{
return appointmentID;
}
string Appointment::getDateTime() const
{
return dateTime;
}
string Appointment::getStatus() const
{
return status;
}
Patient* Appointment::getPatient() const
{
    return patient;
}

Doctor* Appointment::getDoctor() const
{
    return doctor;
}

