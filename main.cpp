#include <iostream>
#include <string>
#include "HealthcareSystem.h"
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Insurance.h"

using namespace std;

int main() {
    cout << "=== Healthcare Management System ===" << endl << endl;

    // Create the central controller — Demi's HealthcareSystem class.
    HealthcareSystem system;

    // ------------------------------------------------------------------
    // STEP 1A: PRE-SEEDED DATA
    // Creates one Patient and one Doctor at startup.
    // Their constructors chain up to User(), incrementing totalUsers.
    // This satisfies: "Create Patient and Doctor objects (update static counters)".
    // ------------------------------------------------------------------

    Insurance* seedInsurance = new Insurance("BlueCross", "BC-001", 80.0);
    Patient* seedPatient = new Patient(1, "Alice Johnson", "alice@email.com", seedInsurance);

    // Doctor constructor is now fixed — using parameterized constructor directly
    Doctor* seedDoctor = new Doctor(2, "Dr. Smith", "drsmith@email.com", "Cardiology");

    system.registerUser(seedPatient);
    system.registerUser(seedDoctor);

    cout << "Pre-seeded 1 Patient and 1 Doctor." << endl;
    cout << "Total users created so far: " << User::getTotalUsers() << endl << endl;

    // ------------------------------------------------------------------
    // STEP 1B: INTERACTIVE FLOW — New or Returning User
    // activePatient tracks whoever just logged in/registered as a Patient,
    // so we can use them for the appointment request in Step 2.
    // ------------------------------------------------------------------

    Patient* activePatient = nullptr; // will be set if the active user is a Patient

    int choice;
    cout << "Welcome to the Healthcare Management System" << endl;
    cout << "1. I am a new user" << endl;
    cout << "2. I am a returning user" << endl;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;
    cout << endl;

    if (choice == 1) {
        // ---- NEW USER ----
        int userType;
        cout << "What type of user are you?" << endl;
        cout << "1. Patient" << endl;
        cout << "2. Doctor" << endl;
        cout << "Enter choice (1 or 2): ";
        cin >> userType;
        cout << endl;

        // Auto-assign ID based on how many users already exist
        int id = User::getTotalUsers() + 1;
        string name, email;

        cin.ignore();
        cout << "Enter your full name: ";
        getline(cin, name);

        cout << "Enter your email: ";
        cin >> email;

        if (userType == 1) {
            // Collect insurance info using Abel's Insurance class
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

            activePatient = newPatient; // this user is now the active patient for Step 2

        } else if (userType == 2) {
            string specialty;
            cin.ignore();
            cout << "Enter your specialty: ";
            getline(cin, specialty);

            // NOTE for Damien: setSpecialty() needed to store specialty here
            Doctor* newDoctor = new Doctor(id, name, email, specialty);
            system.registerUser(newDoctor);

            cout << endl << "Doctor registered successfully!" << endl;
            newDoctor->DisplayUserInfo();
            // activePatient stays nullptr — doctors don't request appointments
        }

        cout << "\nTotal users in system now: " << User::getTotalUsers() << endl;

    } else if (choice == 2) {
        // ---- RETURNING USER ----
        string searchName;
        cin.ignore();
        cout << "Enter your full name: ";
        getline(cin, searchName);

        User* found = system.findUser(searchName);

        if (found != nullptr) {
            cout << endl << "User found!" << endl;
            found->Login(); // Login() — prompts for ID and validates

            // Ask role so we know whether to treat them as Patient or Doctor
            int role;
            cout << "Are you a:" << endl;
            cout << "1. Patient" << endl;
            cout << "2. Doctor" << endl;
            cout << "Enter choice: ";
            cin >> role;

            found->DisplayUserInfo();

            if (role == 1) {
                // static_cast is safe here because we trust the user knows their own role
                // (dynamic_cast would be safer but requires virtual functions on User)
                activePatient = static_cast<Patient*>(found);
            }
            // role == 2 (Doctor) will be used in Step 4 — approve appointment
        } else {
            cout << "No user found with that name." << endl;
        }
    }

    // ------------------------------------------------------------------
    // STEP 2: Patient requests appointment
    // Works for both the pre-seeded Alice and any newly registered patient.
    // The call goes: activePatient->requestAppointment()
    //             → Patient.cpp calls system.scheduleAppointment(patient, doctor)
    //             → HealthcareSystem creates and stores the Appointment object
    // ------------------------------------------------------------------

    if (activePatient != nullptr) {
        int apptChoice;
        cout << endl << "Would you like to request an appointment?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Enter choice: ";
        cin >> apptChoice;

        if (apptChoice == 1) {
            // Use the pre-seeded Dr. Smith for the appointment.
            // Tochi's requestAppointment() calls system.scheduleAppointment(patient, doctor),
            // which is where HealthcareSystem takes over and creates the Appointment.
            activePatient->requestAppointment(system, seedDoctor);
        }
    }

    return 0;
}
