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

    // Create the central controller — this is Demi's HealthcareSystem class.
    // Every user, appointment, and record flows through this object.
    HealthcareSystem system;

    // ------------------------------------------------------------------
    // STEP 1A: PRE-SEEDED DATA
    // We silently create one Patient and one Doctor at startup.
    // Their constructors chain up to User(), which increments totalUsers.
    // This satisfies the requirement: "Create Patient and Doctor objects (update static counters)".
    // ------------------------------------------------------------------

    // Create a real Insurance object using Abel's class (provider, policy number, coverage %)
    Insurance* seedInsurance = new Insurance("BlueCross", "BC-001", 80.0);
    Patient* seedPatient = new Patient(1, "Alice Johnson", "alice@email.com", seedInsurance);

    // NOTE: Doctor's parameterized constructor has a bug in Doctor.cpp (Damien needs to fix it):
    //   - It calls User(userID, email) but User requires User(int, string, string) — 3 args, not 2
    //   - It passes userID as a string but User stores it as an int
    // Workaround: I'm using the default constructor, then use inherited setters to set the fields.
    Doctor* seedDoctor = new Doctor();
    seedDoctor->setuserId(2);
    seedDoctor->setname("Dr. Smith");
    seedDoctor->setemail("drsmith@email.com");

    // Register both with the HealthcareSystem (adds them to the system's internal users list)
    system.registerUser(seedPatient);
    system.registerUser(seedDoctor);

    cout << "Pre-seeded 1 Patient and 1 Doctor." << endl;
    cout << "Total users created so far: " << User::getTotalUsers() << endl;

    cout << endl;

    // ------------------------------------------------------------------
    // STEP 1B: INTERACTIVE FLOW — New or Returning User
    // ------------------------------------------------------------------

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

        // Collect info common to both Patient and Doctor
        // ID is auto-assigned based on how many users already exist in the system
        int id = User::getTotalUsers() + 1;
        string name, email;

        cin.ignore();

        cout << "Enter your full name: ";
        getline(cin, name); 

        cout << "Enter your email: ";
        cin >> email;

        if (userType == 1) {
            // Collect insurance info for the new patient using Abel's Insurance class
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

        } else if (userType == 2) {
            string specialty;
            cout << "Enter your specialty: ";
            getline(cin, specialty);

            // Same workaround as the pre-seeded doctor above — using default constructor + setters.
            // NOTE for Damien: Doctor needs a working parameterized constructor and a setSpecialty() method before specialty can be stored here.
            Doctor* newDoctor = new Doctor();
            newDoctor->setuserId(id);
            newDoctor->setname(name);
            newDoctor->setemail(email); // specialty can't be set until Damien adds setSpecialty()
            system.registerUser(newDoctor);

            cout << endl << "Doctor registered successfully!" << endl;
            newDoctor->DisplayUserInfo();
        }

        cout << "\nTotal users in system now: " << User::getTotalUsers() << endl;

    } else if (choice == 2) {
        // ---- RETURNING USER ----
        string searchName;
        cin.ignore();
        cout << "Enter your full name: ";
        getline(cin, searchName);

        // findUser() is our method on HealthcareSystem — searches the registered users by name.
        User* found = system.findUser(searchName);

        if (found != nullptr) {
            cout << endl << "User found!" << endl;
            found->Login();           // Login() — prompts for ID and validates it
            found->DisplayUserInfo(); // DisplayUserInfo() — prints ID, name, email
        } else {
            cout << "No user found with that name." << endl;
        }
    }

    return 0;
}
