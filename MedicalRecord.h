//
//  MedicalRecord.h
//  MedicalRecordClass
//

#ifndef MedicalRecord_h
#define MedicalRecord_h
#include <string>
using namespace std;
class Patient;
class Doctor;
class MedicalRecord{
private:
    int recordID;
    Patient* patient;
    Doctor* doctor;
    string diagnosis;
    string notes;
    string date;

public:
    MedicalRecord();
    MedicalRecord(int, Patient*, Doctor*, string);
    MedicalRecord(const MedicalRecord &obj);
    void setRecordID(int);
    void setDiagnosis(string);
    void setNotes(string);
    void setDate(string);
    int getRecordId(){
        return recordID;
    }
    string getDiagnosis(){
        return diagnosis;
    }
    string getNotes(){
        return notes;
    }
    string getDate(){
        return date;
    }
    void updateDiagAndNotes(string, string);
    void displayRecord();
};

#endif
