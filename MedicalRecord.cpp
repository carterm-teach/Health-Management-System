//
//  MedicalRecord.cpp
//  MedicalRecordClass
//
//

#include "MedicalRecord.h"
#include "Patient.h"
#include "Doctor.h"
#include <iostream>
#include <string>
using namespace std;

MedicalRecord::MedicalRecord(){
    recordID = 0;
    diagnosis = "";
    notes = "";
    date = "";
}

MedicalRecord::MedicalRecord(int id, Patient p, Doctor doc, string dt){
    recordID = id;
    patient = p;
    doctor = doc;
    date = dt;
    diagnosis = "";
    notes = "";
}

MedicalRecord::MedicalRecord(const MedicalRecord &obj){
    recordID = obj.recordID;
    patient = obj.patient;
    doctor = obj.doctor;
    diagnosis = obj.diagnosis;
    notes = obj.notes;
    date = obj.date;
}

void MedicalRecord::setRecordID(int id){
    recordID = id;
}
void MedicalRecord::setDiagnosis(string diag){
    diagnosis = diag;
}
void MedicalRecord::setNotes(string n){
    notes = n;
}
void MedicalRecord::setDate(string dt){
    date = dt;
}
void MedicalRecord::updateDiagAndNotes(string diag, string n){
    diagnosis = diag;
    notes = n;
}
void MedicalRecord::displayRecord(){
    cout << "-----------------------\n";
    cout << "# " << recordID;
    cout << "\n" << date;
    cout << "\nPatient: " << patient.name;
    cout << "\nDoctor: " << doctor.name;
    cout << "\nDiagnosis: " << diagnosis;
    cout << "\nNotes: " << notes;
    cout << "\n-----------------------\n";
}
