//
// Created by Arã Araújo on 10/15/22.
//

#ifndef UNTITLED_PASSWORD_H
#define UNTITLED_PASSWORD_H
#pragma once
#include <string>
#include <memory>
#include "Dice.h"
#include <map>
#include <fstream>

using namespace std;

class Password
{
private:
    shared_ptr<Dice> dice;
    map<string ,string> dice_ware_dict;

public:
    // Default constructor.
    Password();
    // Import the file password to a map
    void password_map();
    // Automatic password created.
    string auto_generator();
    // Prompt the user for dice values, so it can generate a password
    string manual_generator();
    //Dice checker
    static bool dice_checker(const string& dices);
};

#endif //UNTITLED_PASSWORD_H
