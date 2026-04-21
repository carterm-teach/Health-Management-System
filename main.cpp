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
    // ------------------------------------------------------------------
    Insurance* seedInsurance = new Insurance("BlueCross", "BC-001", 80.0);
    Patient* seedPatient = new Patient(1, "Alice Johnson", "alice@email.com", seedInsurance);
    Doctor*  seedDoctor  = new Doctor(2, "Dr. Smith", "drsmith@email.com", "Cardiology");

    system.registerUser(seedPatient);
    system.registerUser(seedDoctor);

    cout << "Pre-seeded 1 Patient and 1 Doctor." << endl;
    cout << "Total users created so far: " << User::getTotalUsers() << endl << endl;

    // Pre-seed a confirmed appointment so Step 5 has something to compare against
    Patient* bob = new Patient(3, "Bob Williams", "bob@email.com", nullptr);
    system.registerUser(bob);
    Appointment* bobAppt = new Appointment(1, bob, seedDoctor, "2026-04-25 09:00AM");
    bobAppt->confirmAppointment();
    system.scheduleAppointment(bobAppt);

    // ------------------------------------------------------------------
    // Main session loop
    // ------------------------------------------------------------------
    bool running = true;
    while (running) {

        Patient* activePatient = nullptr;

        int choice;
        cout << "Welcome to the Healthcare Management System" << endl;
        cout << "1. I am a new user" << endl;
        cout << "2. I am a returning user" << endl;
        cout << "3. Login as Doctor" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        // --------------------------------------------------------------
        // NEW USER
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
            }

            cout << "\nTotal users in system now: " << User::getTotalUsers() << endl;

        // --------------------------------------------------------------
        // RETURNING USER (Patient)
        // --------------------------------------------------------------
        } else if (choice == 2) {
            string searchName;
            cin.ignore();
            cout << "Enter your full name: ";
            getline(cin, searchName);

            User* found = system.findUser(searchName);
            if (found != nullptr) {
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
                }
            } else {
                cout << "No user found with that name." << endl;
            }

        // --------------------------------------------------------------
        // DOCTOR SESSION — Steps 4, 5, 6
        // --------------------------------------------------------------
        } else if (choice == 3) {
            string searchName;
            cin.ignore();
            cout << "Enter your full name: ";
            getline(cin, searchName);

            User* found = system.findUser(searchName);
            if (!found) { cout << "No user found with that name.\n"; continue; }

            found->Login();
            Doctor* d = static_cast<Doctor*>(found);

            bool doctorSession = true;
            while (doctorSession) {
                cout << "\n--- Doctor Menu ---" << endl;
                cout << "1. Approve pending appointment" << endl;
                cout << "2. Compare appointments (conflict check)" << endl;
                cout << "3. Create Medical Record" << endl;
                cout << "4. Logout" << endl;
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
                                d->approveAppointment(*appt);
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
                    // STEP 5: Compare appointments using operator< to check for conflicts
                    const vector<Appointment*>& appts = system.getAppointments();
                    if ((int)appts.size() < 2) {
                        cout << "Need at least 2 appointments to compare.\n";
                        continue;
                    }
                    cout << "\n=== Appointment Conflict Check ===" << endl;
                    bool conflict = false;
                    for (int i = 0; i < (int)appts.size(); i++) {
                        for (int j = i + 1; j < (int)appts.size(); j++) {
                            cout << "Appt #" << appts[i]->getAppointmentID()
                                 << " (" << appts[i]->getDateTime() << ")"
                                 << " vs Appt #" << appts[j]->getAppointmentID()
                                 << " (" << appts[j]->getDateTime() << "): ";
                            if (*appts[i] < *appts[j]) {
                                cout << "Appt #" << appts[i]->getAppointmentID()
                                     << " is earlier — no conflict." << endl;
                            } else if (*appts[j] < *appts[i]) {
                                cout << "Appt #" << appts[j]->getAppointmentID()
                                     << " is earlier — no conflict." << endl;
                            } else {
                                cout << "CONFLICT — same time slot!" << endl;
                                conflict = true;
                            }
                        }
                    }
                    if (!conflict) cout << "All appointments clear of conflicts." << endl;

                } else if (dc == 3) {
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

                    MedicalRecord rec = d->createMedicalRecord(*pat, diagnosis, notes);
                    pat->addMedicalRecord(rec);
                    system.addMedicalRecord(new MedicalRecord(rec));
                    rec.displayRecord();
                    notif.sendConfirmation("Medical record created for " + pat->getname() + ".");

                } else if (dc == 4) {
                    cout << "\n" << d->getname() << " logged out." << endl;
                    d->Logout();
                    doctorSession = false;
                }
            }
            continue; // skip patient appointment block below

        } else if (choice == 4) {
            running = false;
            continue;
        }

        // --------------------------------------------------------------
        // STEP 2 & 3: Patient requests appointment
        // (runs after new-user or returning-user patient login)
        // --------------------------------------------------------------
        if (activePatient != nullptr) {
            int apptChoice;
            cout << endl << "Would you like to request an appointment?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Enter choice: ";
            cin >> apptChoice;

            if (apptChoice == 1) {
                activePatient->requestAppointment(system, seedDoctor);
                notif.sendAppointmentReminder(
                    activePatient->getname(), seedDoctor->getname(), "See system for date/time"
                );
            }

            cout << "\n" << activePatient->getname() << " logged out." << endl;
            activePatient->Logout();
        }
    }

    cout << "\nGoodbye! Shutting down system..." << endl;
    system.generateReport();
    // HealthcareSystem destructor fires here — cleans all allocated memory
    return 0;
}
