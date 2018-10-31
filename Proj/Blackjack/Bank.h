/* 
 * File:   Bank.h
 * Author: chris
 *
 * Created on October 18, 2018, 6:46 AM
 */

#ifndef BANK_H
#define BANK_H

#include <cstdlib>
#include <iostream>
#include <stack>

#include "Player.h"
#include "Colors.h"

using namespace std;

class Bank {
private:
    // STL stacks used as poker chips
    stack<char> green; // 25
    stack<char> blue;  // 10
    stack<char> red;   // 5
    stack<char> white; // 1
    int total;
public:
    
    const static short NUM_PLAYERS = 2;
    
    Bank() {
        for (int i = 0; i < 8 / NUM_PLAYERS; i++)
            green.push('G');//25
        for (int i = 0; i < 16 / NUM_PLAYERS; i++)
            blue.push('B'); //10
        for (int i = 0; i < 32 / NUM_PLAYERS; i++)
            red.push('R');  //5
        for (int i = 0; i < 64 / NUM_PLAYERS; i++)
            white.push('W');//1
        total = (green.size() * 25) + (blue.size() * 10)
                + (red.size() * 5) + white.size();
    }
    void subBet(short bet) {
        while (!green.empty() && bet / 25 > 0) {
            green.pop();
            bet-=25;
            total-=25;
        }
        while (!blue.empty() && bet / 10 > 0) {
            blue.pop();
            bet-=10;
            total-=10;
        }
        while (!red.empty() && bet / 5 > 0) {
            red.pop();
            bet-=5;
            total-=5;
        }
        while (!white.empty() && bet / 1 > 0) {
            white.pop();
            bet--;
            total--;
        }
    }
    void addReward(short bet, short type) {
        short modBet = bet;
        if (type == 1) { // normal
            modBet = bet * 1.5;
        } else if (type == 2) { // blackjack
            modBet = bet;
        }
        bet = modBet;
        cout << "modBet: " << modBet << endl;
        while (!green.empty() && bet / 25 > 0) {
            green.push('G');
            bet-=25;
            total+=25;
        }
        while (!blue.empty() && bet / 10 > 0) {
            blue.push('B');
            bet-=10;
            total+=10;
        }
        while (!red.empty() && bet / 5 > 0) {
            red.push('R');
            bet-=5;
            total+=5;
        }
        while (!white.empty() && bet / 1 > 0) {
            white.push('W');
            bet--;
            total++;
        }
    }
    // not passed by reference!
    void prntBank(stack<char> r, stack<char> b, stack<char> g, stack<char> w) {
        int i;
        for (i = 0; !g.empty(); i++) {
            if (!g.empty()) {
                cout << BOLDGREEN << g.top() << RESET;
                g.pop();
            }
        }
        cout << " " << i << endl;
        for (i = 0; !b.empty(); i++) {
            if (!b.empty()) {
                cout << BOLDBLUE << b.top() << RESET;
                b.pop();
            }
        }
        cout << " " <<  i << endl;
        for (i = 0; !r.empty(); i++) {
            if (!r.empty()) {
                cout << BOLDRED << r.top() << RESET;
                r.pop();
            }
        }
        cout << " " <<  i << endl;
        for (i = 0; !w.empty(); i++) {
            if (!w.empty()) {
                cout << BGBLACK << BOLDWHITE << w.top() << RESET;
                w.pop();
            }
        }
        cout << " " <<  i << endl;
        cout << "Total: " << total << endl;
    }
    stack<char>& getRed() {
        return red;
    }
    stack<char>& getWhite() {
        return white;
    }
    stack<char>& getGreen() {
        return green;
    }
    stack<char>& getBlue() {
        return blue;
    }
    short getTotal() {
        return total;
    }
};

#endif /* BANK_H */

