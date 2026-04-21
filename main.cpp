#include <iostream>
#include <string>
#include "HealthcareSystem.h"
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Insurance.h"
#include "Appointment.h"
#include "MedicalRecord.h"
#include "NotifService.h"
using namespace std;

int main() {
    cout << "=== Healthcare Management System ===" << endl << endl;

    HealthcareSystem system;
    NotifService notif;

    // ------------------------------------------------------------------
    // STEP 1: Create Patient and Doctor objects (update static counters)
    // Each constructor chains to User(), incrementing User::totalUsers.
    // ------------------------------------------------------------------
    Insurance* seedInsurance = new Insurance("BlueCross", "BC-001", 80.0);
    Patient* seedPatient = new Patient(1, "Alice Johnson", "alice@email.com", seedInsurance);
    Doctor*  seedDoctor  = new Doctor(2, "Dr. Smith", "drsmith@email.com", "Cardiology");

    system.registerUser(seedPatient);
    system.registerUser(seedDoctor);

    cout << "Pre-seeded 1 Patient and 1 Doctor." << endl;
    cout << "Total users created so far: " << User::getTotalUsers() << endl << endl;

    // Pre-seed one existing confirmed appointment so the conflict check (Step 5)
    // inside scheduleAppointment has something to compare the new booking against.
    Appointment* existingAppt = new Appointment(1, seedPatient, seedDoctor, "2026-04-25 09:00AM");
    existingAppt->confirmAppointment();
    system.scheduleAppointment(existingAppt);

    // ------------------------------------------------------------------
    // Main session loop
    // ------------------------------------------------------------------
    bool running = true;
    while (running) {

        Patient* activePatient = nullptr;
        Doctor*  activeDoctor  = nullptr;

        int choice;
        cout << "\nWelcome to the Healthcare Management System" << endl;
        cout << "1. I am a new user" << endl;
        cout << "2. I am a returning user" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        // --------------------------------------------------------------
        // NEW USER — register as Patient or Doctor
        // --------------------------------------------------------------
        if (choice == 1) {
            int userType;
            cout << "What type of user are you?" << endl;
            cout << "1. Patient" << endl;
            cout << "2. Doctor" << endl;
            cout << "Enter choice (1 or 2): ";
            cin >> userType;
            cout << endl;

            int id = User::getTotalUsers() + 1;
            string name, email;

            cin.ignore();
            cout << "Enter your full name: ";
            getline(cin, name);
            cout << "Enter your email: ";
            cin >> email;

            if (userType == 1) {
                string provider, policy;
                double coverage;
                cin.ignore();
                cout << "Enter insurance provider name: ";
                getline(cin, provider);
                cout << "Enter policy number: ";
                cin >> policy;
                cout << "Enter coverage percentage (e.g. 80 for 80%): ";
                cin >> coverage;

                Insurance* newInsurance = new Insurance(provider, policy, coverage);
                Patient* newPatient = new Patient(id, name, email, newInsurance);
                system.registerUser(newPatient);

                cout << endl << "Patient registered successfully!" << endl;
                newPatient->DisplayUserInfo();
                cout << "Total users in system now: " << User::getTotalUsers() << endl;

                activePatient = newPatient;

            } else if (userType == 2) {
                string specialty;
                cin.ignore();
                cout << "Enter your specialty: ";
                getline(cin, specialty);

                Doctor* newDoctor = new Doctor(id, name, email, specialty);
                system.registerUser(newDoctor);

                cout << endl << "Doctor registered successfully!" << endl;
                newDoctor->DisplayUserInfo();
                cout << "Total users in system now: " << User::getTotalUsers() << endl;

                activeDoctor = newDoctor;
            }

        // --------------------------------------------------------------
        // RETURNING USER — login then route to Patient or Doctor session
        // --------------------------------------------------------------
        } else if (choice == 2) {
            string searchName;
            cin.ignore();
            cout << "Enter your full name: ";
            getline(cin, searchName);

            User* found = system.findUser(searchName);
            if (found == nullptr) {
                cout << "No user found with that name." << endl;
                continue;
            }

            cout << endl << "User found!" << endl;
            found->Login();

            int role;
            cout << "Are you a:" << endl;
            cout << "1. Patient" << endl;
            cout << "2. Doctor" << endl;
            cout << "Enter choice: ";
            cin >> role;

            found->DisplayUserInfo();

            if (role == 1) {
                activePatient = static_cast<Patient*>(found);
            } else if (role == 2) {
                activeDoctor = static_cast<Doctor*>(found);
            }

        } else if (choice == 3) {
            running = false;
            continue;
        }

        // --------------------------------------------------------------
        // PATIENT SESSION — Steps 2 & 3
        // Runs whether the patient just registered or logged in.
        // --------------------------------------------------------------
        if (activePatient != nullptr) {
            bool patientSession = true;
            while (patientSession) {
                cout << "\n--- Patient Menu ---" << endl;
                cout << "1. Request Appointment" << endl;
                cout << "2. View Medical History" << endl;
                cout << "3. Logout" << endl;
                cout << "Enter choice: ";
                int pc; cin >> pc;

                if (pc == 1) {
                    // STEP 2: Patient requests appointment
                    // STEP 3: HealthcareSystem creates it (conflict check is inside)
                    activePatient->requestAppointment(system, seedDoctor);
                    notif.sendAppointmentReminder(
                        activePatient->getname(), seedDoctor->getname(), "See system for date/time"
                    );
                } else if (pc == 2) {
                    cout << "\n--- Medical History for " << activePatient->getname() << " ---" << endl;
                    activePatient->viewMedicalHistory();
                } else if (pc == 3) {
                    cout << "\n" << activePatient->getname() << " logged out." << endl;
                    activePatient->Logout();
                    patientSession = false;
                }
            }
        }

        // --------------------------------------------------------------
        // DOCTOR SESSION — Steps 4 & 6
        // Runs whether the doctor just registered or logged in.
        // (Step 5 already ran automatically inside scheduleAppointment)
        // --------------------------------------------------------------
        if (activeDoctor != nullptr) {
            bool doctorSession = true;
            while (doctorSession) {
                cout << "\n--- Doctor Menu ---" << endl;
                cout << "1. Approve pending appointment" << endl;
                cout << "2. Create Medical Record" << endl;
                cout << "3. Logout" << endl;
                cout << "Enter choice: ";
                int dc; cin >> dc;

                if (dc == 1) {
                    // STEP 4: Doctor approves appointment
                    const vector<Appointment*>& appts = system.getAppointments();
                    bool found_appt = false;
                    for (Appointment* appt : appts) {
                        if (appt->getStatus() == "Pending") {
                            cout << "\nPending Appointment #" << appt->getAppointmentID()
                                 << " — " << appt->getDateTime() << endl;
                            cout << "Approve? (y/n): ";
                            char c; cin >> c;
                            if (c == 'y' || c == 'Y') {
                                activeDoctor->approveAppointment(*appt);
                                appt->confirmAppointment();
                                notif.sendConfirmation(
                                    "Appointment #" + to_string(appt->getAppointmentID()) + " confirmed."
                                );
                            }
                            found_appt = true;
                            break;
                        }
                    }
                    if (!found_appt) cout << "No pending appointments.\n";

                } else if (dc == 2) {
                    // STEP 6: Doctor creates MedicalRecord after visit
                    cout << "Enter Patient ID: ";
                    int pid; cin >> pid;
                    User* pu = system.findUserById(pid);
                    if (!pu) { cout << "Patient not found.\n"; continue; }
                    Patient* pat = static_cast<Patient*>(pu);

                    string diagnosis, notes;
                    cin.ignore();
                    cout << "Enter diagnosis: ";
                    getline(cin, diagnosis);
                    cout << "Enter notes: ";
                    getline(cin, notes);

                    MedicalRecord rec = activeDoctor->createMedicalRecord(*pat, diagnosis, notes);
                    pat->addMedicalRecord(rec);
                    system.addMedicalRecord(new MedicalRecord(rec));
                    rec.displayRecord();
                    notif.sendConfirmation("Medical record created for " + pat->getname() + ".");

                } else if (dc == 3) {
                    cout << "\n" << activeDoctor->getname() << " logged out." << endl;
                    activeDoctor->Logout();
                    doctorSession = false;
                }
            }
        }
    }

    cout << "\nGoodbye! Shutting down system..." << endl;
    system.generateReport();
    // HealthcareSystem destructor fires here — cleans all allocated memory
    return 0;
}
