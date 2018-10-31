/* 
 * File:   Deck.h
 * Author: chris
 *
 * Created on October 17, 2018, 11:52 PM
 */

#ifndef DECK_H
#define DECK_H

#include <cstdlib>
#include <vector>
#include <algorithm>

#include "Card.h"

class Deck {
private:
    const short SUITES = 4;
    const short VALUES = 13;
    vector<Card> deck;
public:
    Deck() {
        const char suites[SUITES] = {'H','S','C','D'};
        const char values[VALUES] = {'1','2','3','4','5','6','7','8','9',
                                 'T','J','K','Q'};
        for (int s = 0; s < SUITES; s++) {
            for (int v = 0; v < VALUES; v++) {
                Card card(suites[s], values[v]);
                this->deck.push_back(card);
            }
        }
        shuffle2();
    }
    void shuffle2() {
        default_random_engine dr;
        dr.seed(static_cast<double>(time(0)));
        for (short i = 0; i < 3; i++)
            shuffle(this->deck.begin(), this->deck.end(), dr);
    }
    void addDeck(Deck deck2) {
        for (short i = 0; i < 52; i++) {
            deck.push_back(deck2[i]);
        }
        
    }
    void prntDeck() {
        for (int i = 0; i < deck.size(); i++) {
            if (i > 0 && i % 10 == 0) cout << endl;
            cout << this->getDeck()[i].toString() << " ";
        }
    }
    Card& operator[] (short index) {
        return this->deck[index];
    }
    vector<Card>& operator--(int i) {
        vector<Card>& d2 = deck;
        d2.pop_back();
        return d2;
    }
    vector<Card>& getDeck() {
        return deck;
    }
};

#endif /* DECK_H */

