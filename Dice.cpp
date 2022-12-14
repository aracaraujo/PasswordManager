//
// Created by Arã Araújo on 10/15/22.
//

#include "Dice.h"
#include <random>
#include <utility>

namespace {
    std::random_device rd;
    std::mt19937 gen(rd());}

//Default constructor
Dice::Dice(): number(0)
{
}
string Dice::get_multi_dices() const{
    return multi_dices;
}
void Dice::set_multi_dices(string value) {
    multi_dices = std::move(value);
}
void Dice::roll_dice() {
    uniform_int_distribution<> dist(1,6);
    number = dist(gen);
}
void Dice::multi_rolls(int rolls) {
    for (int i = 0; i < rolls; i++ ){
        roll_dice();
        multi_dices += to_string(number);
    }
}