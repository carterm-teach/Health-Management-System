#include <iostream>
#include "User.h"// used in mac.....use "User.h" with other types

using namespace std;

int main()
{
    cout << "::: User System Test:::\n" << endl;
//create users
    User u1(101, "Mekale","mekale@email.com");
    User u2(102, "Jordan","jordan@email.com");
    User u3(103, "Taylor","taylor@email.com");
//confirm creation
    cout << "Users constructed." << endl;

    // Add users to static list
    cout << "\nAdding users to system..." << endl;

    u1.addUser();
    u2.addUser();
    u3.addUser();

    cout << "Users added successfully." << endl;

    // Show total users created
    cout << "\nTotal Users (objects created): "
         << User::totalUsers << endl;
    //Demo Login
    // Ask for the name
        cout << "Enter a name t osearch: ";
        string name;
        cin >> name;

        bool found = false;

        // Loop over the static vector of users
        for (const User& u : User::users)
        {
            if (u.getname() ==name)
            {
                cout<<"User found... Enter Id number for login: ";
                u.Login();
                u.DisplayUserInfo();
                found = true;
                break;  // stop after first match
                
            }
        }

        if (!found) {
            cout << "User not found" << endl;
        }
    
    return 0;
}
