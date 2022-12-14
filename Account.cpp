//
// Created by Arã Araújo on 10/19/22.
//
#include "Account.h"
#include <iostream>
#include <utility>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;

Account::Account()= default;

Account::Account(string username_input){
    set_filename(username_input);
}

//Set filename
void Account::set_filename(string &username) {
    hash<string> create_hash;
    file_name = to_string(create_hash(username)) + ".txt";
}
//Add a password
bool Account::add_password() {
    system("clear");
    string account,username,password;
    int input;
    bool checker = false;
    while (!checker) {
        cout << "Leave the account or password blank to quit. " << endl;
        cout << "Account: ";
        getline(cin,account);
        cout << "Username: ";
        getline(cin,username);
        if (account.empty() or username.empty()){
            return false;
        }else if (!check_password(account, username)){
            checker = true;
        }
    }
    cout << "Do you want to type your own password or would you like to\n"
         <<"use our password generator?\n"
         <<"Our system uses the DiceWare method which use the assistance of dices\n"
         <<"to increase the password entropy. We can randomly roll the dices for you\n"
         <<"or you can roll your own dices and input the values.\n"
         <<"Options: \n"
         <<"1. Input my own password\n"
         <<"2. Use the password generator with random dices\n"
         <<"3. Use the password generator with my own dice input\n"
         <<"Option: ";
    if (!(cin >> input)) {
        cout << "\nInvalid option. Try again." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (input) {
        case 1: {
            cout << "Password: ";
            getline(cin,password);
            break;
        }
        case 2: {
            password = password_creator.auto_generator();
            break;
        }
        case 3:{
            password = password_creator.manual_generator();
            break;
        }
        default:{
            cout << "\nInvalid option. Try again." << endl;
            break;
        }
    }
    ofstream my_file_out_put;
    my_file_out_put.open(file_name, ios::app);
    my_file_out_put << account << "," << username << "," << password << "," << endl;
    my_file_out_put.close();
    return true;
}

//Split file line
vector<string> Account::split(const string& str){
    string temp;
    vector<string> line;
    char del = ',';
    for(char i : str){
        if(i != del){
            temp += i;
        }
        else{
            line.emplace_back(temp);
            temp = "";
        }
    }
    return line;
}

//Search a password
bool Account::search_account() {
    string input,account,username,password;
    bool result = false;
    cout << "What Account: ";
    getline(cin,input);
    ifstream my_file;
    string my_text;
    vector<string> line;
    my_file.open(file_name);
    while (getline(my_file, my_text)){
        if(strstr(my_text.c_str(), input.c_str())){
            line = split(my_text);
//            auto it = line.begin();
            account = line[0];
//            it++;
            username = line[1];
//            it++;
            password = line[2];
            cout << "Account: " << account << "\n"
            << "Username: " << username << "\n"
            << "Password: " << password << endl;
            result = true;
        }
    }
    my_file.close();
    return result;
}
//List accounts
void Account::list_accounts() {
    ifstream my_file;
    string my_text;
    vector<string> line;
    my_file.open(file_name);
    while (getline(my_file, my_text)) {
        line = split(my_text);
        cout << "Account: "<< line[0];
        cout << "\tUsername: " << line[1] << endl;
    }
    my_file.close();
}

bool Account::check_password(const string &account_input, const string& username_input) {
    ifstream my_file;
    my_file.open(file_name);
    string my_text;
    if (account_input.empty() or username_input.empty()){
        return false;
    }
    while (getline(my_file, my_text)) {
        if(strstr(my_text.c_str(), account_input.c_str()) and strstr(my_text.c_str(), username_input.c_str())){
            cout << "This account exists." << endl;
            return true;
        }
    }
    my_file.close();
    return false;
}

void Account::delete_password(const string& account_input, const string& username_input) {
    string my_text;
    ifstream original_file;
    original_file.open(file_name);
    ofstream new_file;
    bool exist = false;
    new_file.open("temp.txt",ofstream::app);
    while (getline(original_file,my_text)){
        if (strstr(my_text.c_str(), account_input.c_str()) and strstr(my_text.c_str(), username_input.c_str())) {
            exist = true;
        }else{
            new_file << my_text << endl;
        }
    }
    original_file.close();
    new_file.close();
    const char * file = file_name.c_str();
    remove(file);
    rename("temp.txt", file);
    if(exist){
        cout << "Account deleted" << endl;
    }else{
        cout << "Account doesn't exist" << endl;
    }
}

void Account::edit_username(const string& account_edit, const string& old_username, const string& new_username) {
    string my_text;
    ifstream original_file;
    original_file.open(file_name);
    ofstream new_file;
    bool exist = false;
    vector<string> line;
    new_file.open("temp.txt",ofstream::app);
    while (getline(original_file,my_text)){
        if (strstr(my_text.c_str(), account_edit.c_str()) and strstr(my_text.c_str(), old_username.c_str())) {
            exist = true;
            line = split(my_text);
            replace(line.begin(),line.end(),old_username,new_username);
            auto account = line[0];
            auto username = line[1];
            auto password = line[2];
            new_file << account << "," << username << "," << password << "," << endl;
        }else{
            new_file << my_text << endl;
        }
    }
    original_file.close();
    new_file.close();
    const char * file = file_name.c_str();
    remove(file);
    rename("temp.txt", file);
    if(exist){
        cout << "Username changed" << endl;
    }else{
        cout << "Account doesn't exist" << endl;
    }
}

void Account::edit_password(const string& account_edit, const string& username_edit) {
    int choice;
    bool checker = false;
    string new_password;
    while(!checker){
        cout <<"1. Input my own password\n"
             <<"2. Use the password generator with random dices\n"
             <<"3. Use the password generator with my own dice input\n"
             <<"Option: ";
        if (!(cin >> choice)) {
            cout << "\nInvalid option. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 1){
            cout <<"Enter the new password: ";
            getline(cin,new_password);
            checker = true;
        }else if (choice == 2){
            new_password = password_creator.auto_generator();
            checker = true;
        }else if (choice == 3){
            new_password = password_creator.manual_generator();
            checker = true;
        }else{
            cout << "Invalid option. Try again." << endl;
        }
    }
    string my_text;
    ifstream original_file;
    original_file.open(file_name);
    ofstream new_file;
    bool exist = false;
    vector<string> line;
    new_file.open("temp.txt",ofstream::app);
    while (getline(original_file,my_text)){
        if (strstr(my_text.c_str(), account_edit.c_str()) and strstr(my_text.c_str(), username_edit.c_str())) {
            exist = true;
            line = split(my_text);
            auto account = line[0];
            auto username = line[1];
            auto old_password = line[2];
            replace(line.begin(),line.end(),old_password,new_password);
            auto password = line[2];
            new_file << account << "," << username << "," << password << "," << endl;
        }else{
            new_file << my_text << endl;
        }
    }
    original_file.close();
    new_file.close();
    const char * file = file_name.c_str();
    remove(file);
    rename("temp.txt", file);
    if(exist){
        cout << "Password changed" << endl;
    }else{
        cout << "Account doesn't exist" << endl;
    }
}
