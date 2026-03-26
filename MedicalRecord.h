// STUB - Placeholder until Taureen's full MedicalRecord implementation is ready.
// Do not modify this file — replace it entirely with MedicalRecord.h from Taureen.
#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <string>

class Patient;

class MedicalRecord {
public:
    MedicalRecord() {}
    MedicalRecord(Patient& patient, const std::string& diagnosis, const std::string& notes) {}
    MedicalRecord(const MedicalRecord& other) {}
    void displayRecord() {}
};

#endif
