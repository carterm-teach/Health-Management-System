#include "User.hpp"
#include <string>
#include <iostream>
using namespace std;
int User::totalUsers = 0;
vector<User> User::users;
User::User()
{
    userID = 0;
    name = " ";
    email = " ";
    totalUsers++;
}
User::User(int uid,string n,string e)
{
    userID = uid;
    name = n;
    email = e;
    totalUsers++;
}
User::~User()
{
}
void User::setuserId(int uid)
{
    userID = uid;
}
void User::setname(string n)
{
    name = n;
}
void User::setemail(string e)
{
    email = e;
}
int User::getuserID()const
{
    return userID;
}
string User::getname()const
{
    return name;
}
string User::getemail()const
{
    return email;
}
int User::getTotalUsers()
{
    return totalUsers;
}
void User::addUser()
{
    cout<<"Adding user "<< userID<<endl;
    users.push_back(*this);
    cout<<"Added successfully"<<endl;
}
void User::Login()const
{
    int enteredID=0;
    bool login = false;
    cout<< ":::User Login:::" <<endl;
    cout << "Enter your ID number: ";
    cin >> enteredID;
    if(enteredID == userID)
    {
        cout<<"Welcome "<<name<<endl;;
        login = true;
    }
    else
    {
        cout<<"Wrong Id #\n unsuccesfull log in attempt\n";
    }
}
void User::Logout()const
{
    
}
void User::DisplayUserInfo()const
{
    cout<<endl;
    cout<<userID<<endl;
    cout<<name<<endl;
    cout<<email<<endl;
}
