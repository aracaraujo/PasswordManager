//
// Created by Arã Araújo on 10/19/22.
//

#ifndef UNTITLED_ACCOUNT_H
#define UNTITLED_ACCOUNT_H
#pragma once
#include <string>
#include "Password.h"
#include <fstream>
#include <list>

using namespace std;

class Account{
private:
    Password password_creator;
    string file_name;
public:
    // Default constructor.
    Account();
    // Non-default constructor.
    explicit Account(string username_input);
    //Set filename according to the user.
    void set_filename(string &username);
    //Add an account,username, and a password.
    bool add_password();
    //Search for the account information.
    bool search_account();
    //Convert the file line in a list.
    static vector<string> split(const string& str);
    //List existing accounts.
    void list_accounts();
    //Check if the account has be added already
    bool check_password(const string &account_input, const string& username_input);
    //Delete an account,username, and password from the list.
    void delete_password(const string& account_input, const string& username_input);
    //Edit username
    void edit_username(const string& account_edit,const string& old_username,const string& new_username);
    //Edit a password
    void edit_password(const string& account_edit, const string& username_edit);

};



#endif //UNTITLED_ACCOUNT_H
