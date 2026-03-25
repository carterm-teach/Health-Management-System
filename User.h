#ifndef User_h
#define User_h

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
class User{

public:
    int userID;
    string name;
    string email;
    static int totalUsers;
    static vector <User> users;
    
    User();
    User(int,string,string);
    ~User();
    
    void setuserId(int);
    void setname(string);
    void setemail(string);
    int getuserID()const;
    string getname()const;
    string getemail()const;
    
    static int getTotalUsers();
    
    void addUser();
    //void deleteUser();
    
    void Login()const;
    void Logout()const;
    void DisplayUserInfo()const;
    
};
#endif /* User_hpp */
