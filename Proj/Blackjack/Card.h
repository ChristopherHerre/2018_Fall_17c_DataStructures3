/* 
 * File:   Card.h
 * Author: chris
 *
 * Created on October 17, 2018, 11:26 PM
 */

#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <string>
#include <sstream>

#include "Colors.h"

using namespace std;

class Card {
private:
    char suit;
    char value;
public:
    Card() { };
    Card(char suite, char value) {
        this->suit = suite;
        this->value = value;
    }
    string toString() {
        stringstream ss;
        string color = suit == 'H' || suit == 'D' ? BOLDRED : BOLDBLACK;
        ss << color << value << suit << RESET;
        return ss.str();
    }
    char getSuit() {
        return suit;
    }
    char getValue() {
        return value;
    }
    bool operator==(Card card) {
        if (this->value == card.value && this->suit == card.suit)
            return true;
        else 
            return false;
    }
    bool operator!=(Card card) {
        if (this->value == card.value && this->suit == card.suit)
            return false;
        else 
            return true;
    }
};

#endif /* CARD_H */

