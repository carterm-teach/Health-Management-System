#include "Doctor.h"

#include "Appointment.h"

#include "MedicalRecord.h"

#include "Prescription.h"

#include "Patient.h"

#include <iostream>



using namespace std;





Doctor::Doctor()

  : User(), name("Unknown"), specialty("General") {}



Doctor::Doctor(const string& userID,

        const string& name,

        const string& email,

        const string& specialty)

  : User(userID, name, email),

   name(name),

   specialty(specialty) {}



Doctor::Doctor(const Doctor& other)

  : User(other),

   name(other.name),

   specialty(other.specialty),

   schedule(other.schedule) {} 



Doctor::~Doctor() {

  cout << "Destroying Doctor object: " << name << endl;

  schedule.clear(); 

}





bool Doctor::approveAppointment(Appointment& appointment) {

  for (auto* existing : schedule) {

    if (*existing == appointment) {  

      appointment.updateStatus("Denied");

      cout << "Conflict detected. Appointment denied.\n";

      return false;

    }

  }



  appointment.updateStatus("Approved");

  schedule.push_back(&appointment);

  cout << "Appointment approved by Dr. " << name << endl;

  return true;

}



void Doctor::denyAppointment(Appointment& appointment) {

  appointment.updateStatus("Denied");

  cout << "Appointment denied by Dr. " << name << endl;

}





MedicalRecord Doctor::createMedicalRecord(Patient& patient,

                     const string& diagnosis,

                     const string& notes) {

  MedicalRecord record(

    patient.getUserID(),

    patient,

    *this,

    diagnosis,

    notes

  );



  cout << "Medical record created for patient: "

     << patient.getName() << endl;



  return record;  

}



Prescription Doctor::issuePrescription(Patient& patient,

                    const string& medication,

                    const string& dosage) {

  Prescription rx(

    patient.getUserID(),

    patient,

    *this,

    medication,

    dosage

  );



  cout << "Prescription issued for " << medication

     << " to patient " << patient.getName() << endl;



  return rx;

}





void Doctor::displayInfo() const {

  cout << "Doctor: " << name

     << "\nSpecialty: " << specialty

     << "\nEmail: " << email

     << endl;

}
