//
// Created by Arã Araújo on 10/15/22.
//
#include "Password.h"
#include <map>
#include <iostream>
#include <string>

using namespace std;

// Default constructor
Password::Password() : dice(nullptr)
{
    password_map();
}
void Password::password_map() {
    ifstream my_file;
    my_file.open("dicewarelist.txt");
    string my_text;
    while (getline(my_file, my_text)){
        string key = my_text.substr(0, 5);
        string value = my_text.substr(6);
        dice_ware_dict[key] = value;
    }
    my_file.close();
}
string Password::auto_generator() {
    string password;
    dice = make_shared<Dice>();
    map<string,string>:: iterator it;
    for (int i = 0; i < 6; i++){
        dice -> multi_rolls(5);
        it = dice_ware_dict.find(dice->get_multi_dices());
        password += it -> second;
        dice ->set_multi_dices("");
    }
    return password;
}
string Password::manual_generator(){
    string input;
    string password;
    map<string,string>:: iterator it;
    int dices = 0;
    cout << "You will be prompted for a 5 digit value 6 times.\n"
            "The digits must be between 1 and 6 as a dice to represent dices." << endl;
    while (dices < 6){
        cout << "Input value: ";
        getline(cin,input);
        if (dice_checker(input)){
            it = dice_ware_dict.find(input);
            password += it -> second;
            dices++;
        }
        else{
            cout << "This is not a valid input. Try again." << endl;
        }
    }
    return password;
}

bool Password::dice_checker(const string& dices) {
    bool checker = true;
    int number;
    string input;
    if (dices.length() != 5){
        checker = false;
        return checker;
    }
    for (char dice : dices) {
        input = dice;
        number = stoi(input);
        if (number < 1 or number > 6){
            checker = false;
            return checker;
        }
    }
    return checker;
}