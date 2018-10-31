/* 
 * File:   Player.h
 * Author: rcc
 *
 * Created on October 17, 2018, 6:13 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <list>

#include "Bank.h"
#include "Deck.h"

using namespace std;

class Player {
private:
    string name;
    Bank bank;
    pair<Card, Card> cards;
    list<Card> hits;
    bool blackjack = false;
    short score = 0, bet = 0, acesSubbed = 0;
public:
    Player(Deck& deck, bool dealer, map<char, short>& vals,
        queue<Card>& burnCards) {
        init(deck, dealer, vals, burnCards);
    }
    void init(Deck& deck, bool dealer, map<char, short>& vals,
        queue<Card>& burnCards) {
        hits.clear();
        blackjack = false;
        acesSubbed = 0;
        score = 0;
        // treat the back as the front
        burnCards.push(deck.getDeck().back());
        cards.first = deck.getDeck().back();
        deck--;
        burnCards.push(deck.getDeck().back());
        cards.second = deck.getDeck().back();
        deck--;
        score += vals[cards.first.getValue()];
        score += vals[cards.second.getValue()];
        int aces = countAces();
        if (aces > 1 && acesSubbed <= aces) {
            acesSubbed++;
            cout << "aces: " << aces<< " acesSubbed: " << acesSubbed << endl;
            cout << "Subtracting 10 from score" << endl;
            setScore(getScore() - 10);
            
        }
        if ((cards.first.getValue() == '1'
                && vals[cards.second.getValue()] == 10)
                    || (cards.second.getValue() == '1'
                        && vals[cards.first.getValue()] == 10)) {
            score = 21;
            blackjack = true;
        }
    }
    int countAces() {
        list<Card> aces;
        Card first = cards.first;
        Card second = cards.second;
        if (first.getValue() == '1')
            aces.push_back(first);
        if (second.getValue() == '1')
            aces.push_back(second);
        for (Card c : hits) {
            if (c.getValue() == '1') {
                aces.push_back(c);
            }
        }
        return aces.size();
    }
    void prntDealer() {
        cout << "Dealer: " << cards.first.toString() << " **" << endl;
    }
    string getName() {
        return name;
    }
    void setName(string name) {
        this->name = name;
    }
    Bank& getBank() {
        return bank;
    }
    pair<Card, Card>& getCards() {
        return cards;
    }
    list<Card>& getHits() {
        return hits;
    }
    short getScore() {
        return score;
    }
    void setScore(short score) {
        this->score = score;
    }
    short getBet() {
        return bet;
    }
    void setBet(short bet) {
        this->bet = bet;
    }
    bool isBlackjack() {
        return blackjack;
    }
    void setBlackjack(bool blackjack) {
        this->blackjack = blackjack;
    }
    short getAcesSubbed() {
        return acesSubbed;
    }
    void setAcesSubbed(short acesSubbed) {
        this->acesSubbed = acesSubbed;
    }
};

#endif /* PLAYER_H */

