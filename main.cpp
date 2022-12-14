#include <iostream>
#include <map>
#include <string>
#include "Account.h"

using namespace std;
using std::map;

bool check_account(string &username_input, string &password_input);
void create_account();
void menu_account_options(string& username);

int main() {
    bool program_controller = true;
    int choice;
    while (program_controller){
        system("clear");
        cout << "\n=======================" << endl
             << "Welcome to PassSecurity" << endl
             << "=======================" << endl
             << "\n"
             <<"0. Quit Program \n"
             <<"1. Sign in \n"
             <<"2. Create an account \n"
             <<"Your Choice: ";
        if (!(cin >> choice)) {
            cout << "\nInvalid option. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        switch (choice) {
            case 0: {
                program_controller = false;
                break;
            }
            case 1: {
                string username;
                string password;
                cout << "Username: ";
                getline(cin,username);
                cout << "Password: ";
                getline(cin,password);
                if (check_account(username,password)){
                    system("clear");
                    menu_account_options(username);
                }else{
                    cout << "The account doesn't exist or Username or password are wrong.";
                }
                break;
            }
            case 2: {
                create_account();
                break;
            }
            default: {
                cout << "This isn't a proper option";
                continue;
            }
        }
    }
    return 0;
}

bool check_account(string &username_input, string &password_input = (string &) ""){
    ifstream my_file_input;
    my_file_input.open("credentials.txt");
    string my_text;
    hash<string> create_hash;
    if (password_input.length() != 0){
        while (getline(my_file_input, my_text)) {
            bool username_check = strstr(my_text.c_str(), to_string(create_hash(username_input)).c_str());
            bool password_checker = strstr(my_text.c_str(), to_string(create_hash(password_input)).c_str());
            if (username_check) {
                if (password_checker) {
                    my_file_input.close();
                    return true;
                }
            }
        }
        my_file_input.close();
        return false;
    }else{
        while (getline(my_file_input, my_text)) {
            if (strstr(my_text.c_str(), to_string(create_hash(username_input)).c_str()))
            {
                my_file_input.close();
                return true;
            }
        }
    }
    return false;
}

void create_account(){
    ofstream my_file_out_put;
    string username;
    string password;
    hash<string> create_hash;
    my_file_out_put.open("credentials.txt", ios::app);
    cout << "New username: ";
    getline(cin,username);
    cout<< "New password: ";
    getline(cin, password);
    if (check_account(username)){
        cout << "The account exists";
        my_file_out_put.close();
    }else{
        my_file_out_put << create_hash(username) << " " << create_hash(password) << endl;
        my_file_out_put.close();
        string file_name = to_string(create_hash(username)) + ".txt";
        my_file_out_put.open(file_name, ios::app);
        my_file_out_put.close();
        cout << "Your account has been created";
    }
}

void menu_account_options(string& username){
    bool program_controller = true;
    int choice;
    Account account(username);
    while (program_controller) {
        system("clear");
        cout << "MAIN MENU" << endl
             << "=========" << endl
             << "0. Sign out" << endl
             << "1. Add a password" << endl
             << "2. Search a password" << endl
             << "3. List existing accounts" << endl
             << "4. Edit an account" << endl
             << "5. Delete an account" << endl
             << "Option: ";
        if (!(cin >> choice)) {
            cout << "\nInvalid option. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 0: {
                program_controller = false;
                break;
            }
            case 1: {
                account.add_password();
                cout <<"Press Enter to go back to menu" << endl;
                cin.get();
                break;
            }
            case 2: {
                if (!account.search_account()){
                    cout << "You don't have a password for this account" << endl;
                }
                cout <<"Press Enter to go back to menu" << endl;
                cin.get();
                break;
            }
            case 3: {
                account.list_accounts();
                cout <<"Press Enter to go back to menu" << endl;
                cin.get();
                break;
            }
            case 4: {
                string account_edit,username_edit,password_edit;
                int choice_4;
                bool checker = false;
                cout << "What account do you want to edit? ";
                getline(cin,account_edit);
                cout << "What is the username? ";
                getline(cin,username_edit);
                if(account.check_password(account_edit,username_edit)){
                    while(!checker){
                        cout << "What do you want to edit?" << endl
                             << "1. Username" << endl
                             << "2. Password" << endl
                             << "0. To exit" << endl;
                        if (!(cin >> choice_4)) {
                            cout << "\nInvalid option. Try again." << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (choice_4 == 1){
                            string new_username;
                            cout <<"Enter the new username: ";
                            getline(cin,new_username);
                            account.edit_username(account_edit,username_edit,new_username);
                            checker = true;
                        }else if (choice_4 == 2){
                            account.edit_password(account_edit,username_edit);
                            checker = true;
                        }else if (choice_4 == 0){
                            checker = true;
                        }else{
                            cout << "Invalid option. Try again." << endl;
                        }
                    }
                }else{
                    cout << "This account doesn't exist" << endl;
                }
                cout <<"Press Enter to go back to menu" << endl;
                cin.get();
                break;
            }
            case 5:{
                system("clear");
                string account_input;
                string username_input;
                cout << "Enter account: ";
                getline(cin,account_input);
                cout << "Enter username: ";
                getline(cin,username_input);
                account.delete_password(account_input,username_input);
                cout <<"Press Enter to go back to menu" << endl;
                cin.get();
                break;
            }
            default:{
                cout << "This isn't a proper option" << endl;
                cout <<"Press Enter to go back to menu" << endl;
                cin.get();
                continue;
            }
        }
    }
}
