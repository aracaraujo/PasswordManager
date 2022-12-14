//
// Created by Arã Araújo on 10/15/22.
//

#ifndef UNTITLED_DICE_H
#define UNTITLED_DICE_H
#pragma once
#include <iostream>
#include <random>
using namespace std;

class Dice
{
private:
    int number;
    string multi_dices;
public:
    //Default constructor
    Dice();
    //Returns the multi_dices string
    string get_multi_dices()const;
    // Set multi_dices to a given value
    void set_multi_dices(string value);
    //Rolls the dice and updates the dice number
    void roll_dice();
    // Roll dice x number of times
    void multi_rolls(int rolls);
};

#endif //UNTITLED_DICE_H
