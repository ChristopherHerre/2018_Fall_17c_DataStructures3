/* 
 * File:   main.cpp
 * Author: chris
 *
 * Created on October 20, 2018, 7:29 PM
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <stack>
#include <set>

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Bank.h"

using namespace std;

void handleOptions(Player&, set<string, less<string>>&, Deck&,
        map<char, short>&, deque<Player>&,
        queue<Card>&);
void populateVals(map<char, short>&);
void collectBets(Deck&, deque<Player>&, map<char, short>&,
        queue<Card>&);
void handleDealer(Deck&, Player&, map<char, short>&,
        queue<Card>&);
void handleOutcome(Player& dealer, deque<Player>& players);
void gameLoop(bool&, Deck&, deque<Player>&, deque<Player>&,
        map<char, short>&, queue<Card>&);
void initPlayers(bool&, Deck&, deque<Player>&, deque<Player>&,
        map<char, short>&, queue<Card>&);
void lose(Player&, short, short);
void handleHit(Player&, set<string, less<string>>&, Deck&, 
        map<char, short>&, deque<Player>&, queue<Card>&);
void askDecks(Deck&);

int main(int argc, char** argv) {
    map<char, short> vals;
    // populate a map of face values to score values
    populateVals(vals);
    // create a deck and shuffle
    Deck deck;
    // ask the user how many decks
    // and add to current deck
    askDecks(deck);
    cout << endl << BOLDCYAN << "Reshuffling deck..." << RESET << endl;
    deck.shuffle2();
    cout << endl;
    // the first round or not?
    bool first = true;
    // currently playing
    deque<Player> players;
    // disgarded cards
    queue<Card> burnCards;
    deque<Player> nextRound;
    burnCards.push(deck.getDeck().back());
    // pop the back of the deck
    deck--;
    do {
        gameLoop(first, deck, players, nextRound, vals, burnCards);
        // deck is getting low so recreate it
        while (!burnCards.empty()) {
            deck.getDeck().push_back(burnCards.front());
            burnCards.pop();
        }
        deck.shuffle2();
        cout << BOLDCYAN << "Reshuffling deck..." << RESET << endl;
    } while (true);
    return 0;
}

void askDecks(Deck& deck) {
    cout << "How many decks do you want to play with? ";
    short numDecks;
    cin >> numDecks;
    if (numDecks < 1 || numDecks > 5) {
        cout << "Input error!" << endl;
        exit(0);
    }
    for (short i = 0; i < numDecks; i++) {
        Deck deck2;
        deck.addDeck(deck2);
    }
    deck.prntDeck();
}

void gameLoop(bool& first, Deck& deck, deque<Player>& players,
        deque<Player>& nextRound, map<char, short>& vals,
        queue<Card>& burnCards) {
    for (int i = 0; i < 3; i++) {
        // denotes a new round
        cout << "-------------------" << endl;
        initPlayers(first, deck, players, nextRound, vals, burnCards);
        Player dealer(deck, true, vals, burnCards);
        dealer.setName("Dealer");
        dealer.prntDealer();
        // sort options alphabetically upon insert with a set
        set<string, less<string>> options;
        for (Player& p : players) {
            options.insert("hit");
            options.insert("stay");
            handleOptions(p, options, deck, vals, players, burnCards);
        }
        // dealers turn is last
        handleDealer(deck, dealer, vals, burnCards);
        // decide win, lose, or push
        handleOutcome(dealer, players);
    }
}

void initPlayers(bool& first, Deck& deck, deque<Player>& players,
        deque<Player>& nextRound, map<char, short>& vals,
        queue<Card>& burnCards) {
    if (first) {
        collectBets(deck, players, vals, burnCards);
        nextRound = players;
        first = false;
    } else {
        for (Player &p : nextRound) {
            p.init(deck, false, vals, burnCards);
        }
        players = nextRound;
    }
}

void lose(Player& p3, short pScore, short dScore) {
    cout << MAGENTA << p3.getName() << RESET
            << " loses. Dealer's score of " << dScore
            << " better than " << pScore << "." << endl;
    p3.getBank().subBet(p3.getBet()); 
}

void handleOutcome(Player& dealer, deque<Player>& players) {
    for (Player& p3 : players) {
        short pScore = p3.getScore();
        short dScore = dealer.getScore();
        if (dealer.isBlackjack() && !p3.isBlackjack()) {
            lose(p3, pScore, dScore);
        } else if (p3.isBlackjack() || (pScore > dScore && pScore <= 21) ||
                (dScore > 21 && pScore <= 21)) {
            cout << MAGENTA << p3.getName() << RESET << " is a winner!" << endl;
            p3.getBank().addReward(p3.getBet(), p3.isBlackjack() ? 1 : 2);
        } else if (pScore == dScore && pScore <= 21) {
            cout << "PUSH! " << MAGENTA << p3.getName() << RESET
                    << "'s score is equal to dealers score of "
                    << dScore << endl;
            // player does not lose bet or gain
        } else {
            lose(p3, pScore, dScore);
        }
        Bank bank = p3.getBank();
        cout << "Printing " << MAGENTA << p3.getName() << RESET
                << "'s bank..." << endl;
        p3.getBank().prntBank(bank.getRed(), bank.getBlue(),
                bank.getGreen(), bank.getWhite());
        // reset some variables
        p3.setBlackjack(false);
        p3.setAcesSubbed(0);
    }
}

void handleDealer(Deck& deck, Player& dealer, map<char, short>& vals,
        queue<Card>& burnCards) {
    if (dealer.getScore() < 16) {
        dealer.getHits().push_back(deck.getDeck().back());
        dealer.setScore(dealer.getScore()
            + vals[deck.getDeck().back().getValue()]);
        burnCards.push(deck.getDeck().back());
        deck--;
        // deal with aces having two values, 11 or 1
        int aces = dealer.countAces();
        cout << "aces: " << aces << " p.getScore(): " << dealer.getScore()
                << endl;
        if (aces >= 1 && dealer.getScore() > 21) {
            while (dealer.getScore() > 21 && dealer.getAcesSubbed() != aces) {
                cout << "Subtracting 10 from dealer's score" << endl;
                dealer.setAcesSubbed(dealer.getAcesSubbed() + 1);
                cout << "aces: " << aces<< " acesSubbed: "
                        << dealer.getAcesSubbed() << endl;
                dealer.setScore(dealer.getScore() - 10);
            }
        }
    }
    // print dealer's hand and score
    cout << "Dealer: " << dealer.getCards().first.toString() << " " 
            << dealer.getCards().second.toString() << " ";

    for (Card c : dealer.getHits()) {
        cout << c.toString() << " ";
    }
    cout << dealer.getScore() << endl;
    if (dealer.isBlackjack()) {
        cout << "Dealer has blackjack!" << endl;
    }
}

void collectBets(Deck& deck, deque<Player>& players, map<char, short>& vals,
        queue<Card>& burnCards) {
    for (short i = 0; i < Bank::NUM_PLAYERS; i++) {
        cout << "Enter player " << i + 1 << "'s name: ";
        string input;
        short bet = 0;
        cin >> input;
        if (input == "Dealer") {
            cout << "Input error!" << endl;
            exit(1);
        }
        Player p(deck, false, vals, burnCards);
        p.setName(input);
        Bank bank = p.getBank();
        cout << "Printing " << MAGENTA << p.getName() << RESET
                << "'s bank..." << endl;
        p.getBank().prntBank(bank.getRed(), bank.getBlue(),
                    bank.getGreen(), bank.getWhite());
        cout << "Place your bet 1-" << p.getBank().getTotal() << ": ";
        cin >> bet;
        if (bet < 1 || bet > p.getBank().getTotal()) {
            cout << "Input error!" << endl;
            exit(1);
        }
        p.setBet(bet);
        players.push_back(p);
    }
}

void populateVals(map<char, short>& vals) {
    vals.insert(pair<char, short>('K', 10));
    vals.insert(pair<char, short>('J', 10));
    vals.insert(pair<char, short>('Q', 10));
    vals.insert(pair<char, short>('T', 10));
    vals.insert(pair<char, short>('9', 9));
    vals.insert(pair<char, short>('8', 8));
    vals.insert(pair<char, short>('7', 7));
    vals.insert(pair<char, short>('6', 6));
    vals.insert(pair<char, short>('5', 5));
    vals.insert(pair<char, short>('4', 4));
    vals.insert(pair<char, short>('3', 3));
    vals.insert(pair<char, short>('2', 2));
    vals.insert(pair<char, short>('1', 11));
}

void handleOptions(Player& p, set<string, less<string>>& options, Deck& deck,
        map<char, short>& vals, deque<Player>& players,
        queue<Card>& burnCards) {
    if (p.getHits().size() <= 0) {
        cout << p.getName() << ": " << p.getCards().first.toString() << " "
                << p.getCards().second.toString() << endl;
        if (p.isBlackjack()) {
            cout << p.getName() << " has blackjack!" << endl;
        }
    }
    cout << "Its " << MAGENTA << p.getName() << RESET
            << "'s turn. Here are your options:\n";
    for (string o : options) {
        cout << "'" << o << "' ";
    }
    cout << endl;
    string input;
    cin >> input;
    if (!(options.find(input) != options.end())) {
        cout << "You entered an invalid option!" << endl;
        handleOptions(p, options, deck, vals, players, burnCards);
        return;
    }
    switch (input) {
        case "hit":
            handleHit(p, options, deck, vals, players, burnCards);        
            break;
        case "stay":
            cout << MAGENTA << p.getName() << RESET << " chose to stay."
                    << endl;
            return;
        default:
            cout << "Input error!" << endl;
            exit(1)
    }
    /*if (input == "hit") {
        handleHit(p, options, deck, vals, players, burnCards);
    } else if (input == "stay") {
        cout << MAGENTA << p.getName() << RESET << " chose to stay." << endl;
        return;
    } else {
        cout << "Input error!" << endl;
        exit(1);
    }*/
}

void handleHit(Player& p, set<string, less<string>>& options, Deck& deck,
        map<char, short>& vals, deque<Player>& players,
        queue<Card>& burnCards) {
    p.setScore(p.getScore() + vals[deck.getDeck().back().getValue()]);
    p.getHits().push_back(deck.getDeck().back());
    burnCards.push(deck.getDeck().back());
    deck--;
    cout << p.getCards().first.toString() << " "
            << (p.getName() == "Dealer" ? "**"
            : p.getCards().second.toString()) << " ";
    for (Card c : p.getHits()) {
        cout << c.toString() << " ";
    }
    cout << endl;
    int aces = p.countAces();
    cout << "aces: " << aces << " p.getScore(): " << p.getScore() << endl;
    if (aces >= 1 && p.getScore() > 21) {
        while (p.getScore() > 21 && p.getAcesSubbed() != aces) {
            cout << "Subtracting 10 from score" << endl;
            p.setAcesSubbed(p.getAcesSubbed() + 1);
            cout << "aces: " << aces<< " acesSubbed: " << p.getAcesSubbed()
                    << endl;
            p.setScore(p.getScore() - 10);
        }
    }
    if (p.getScore() > 21) {
        cout << "BUST! Your score is " << p.getScore() << ". You're out!"
                << endl;
        p.getBank().subBet(p.getBet());
        cout << "Printing " << MAGENTA << p.getName() << RESET
            << "'s bank..." << endl;
        Bank bank = p.getBank();
        p.getBank().prntBank(bank.getRed(), bank.getBlue(),
                bank.getGreen(), bank.getWhite());
        // remove player from playing list if bust
        // iterators used here
        auto it = players.begin();
        for (short i = 0; i < players.size(); i++) {
            Player& p2 = players[i];
            if (p2.getName() == p.getName()) break;
            it++;
        }
        players.erase(it);
    } else {
        handleOptions(p, options, deck, vals, players, burnCards);
    }
}