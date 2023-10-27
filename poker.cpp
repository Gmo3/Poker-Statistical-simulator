#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

const int NUM_SIMULATIONS = 1000000;

// Function declarations:
void initializeDeck(int deck[]);
void shuffleDeck(int deck[]);
bool isStraight(int R[]);
bool isPair(int R[]);
bool isFlush(int S[]);
bool isThreeOfAKind(int R[]);
bool isFullHouse(int R[]);
bool isFourOfAKind(int R[]);

int main() {
    srand(time(0));
    int deck[52];
    string suitnames[4] = {"spades", "diamonds", "clubs", "hearts"};
    string ranknames[13] = {"ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"};

    int numStraights = 0, numPairs = 0, numFlushes = 0, numThreeOfAKind = 0, numFullHouse = 0, numFourOfAKind = 0;

    for (int sim = 0; sim < NUM_SIMULATIONS; sim++) {
        initializeDeck(deck);
        shuffleDeck(deck);

        int R[5], S[5];
        for (int i = 0; i < 5; i++) {
            R[i] = deck[i] % 13;
            S[i] = deck[i] / 13;
        }

        if (isStraight(R)) numStraights++;
        if (isPair(R)) numPairs++;
        if (isFlush(S)) numFlushes++;
        if (isThreeOfAKind(R)) numThreeOfAKind++;
        if (isFullHouse(R)) numFullHouse++;
        if (isFourOfAKind(R)) numFourOfAKind++;
    }

    cout << "Odds of getting a straight: " << (double)numStraights / NUM_SIMULATIONS << endl;
    cout << "Odds of getting a pair: " << (double)numPairs / NUM_SIMULATIONS << endl;
    cout << "Odds of getting a flush: " << (double)numFlushes / NUM_SIMULATIONS << endl;
    cout << "Odds of getting three of a kind: " << (double)numThreeOfAKind / NUM_SIMULATIONS << endl;
    cout << "Odds of getting a full house: " << (double)numFullHouse / NUM_SIMULATIONS << endl;
    cout << "Odds of getting four of a kind: " << (double)numFourOfAKind / NUM_SIMULATIONS << endl;

    return 0;
}

// Function definitions:

void initializeDeck(int deck[]) {
    for (int i = 0; i < 52; i++) {
        deck[i] = i;
    }
}

void shuffleDeck(int deck[]) {
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52;
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

bool isStraight(int R[]) {
    int sortedR[5];
    for (int i = 0; i < 5; i++) {
        sortedR[i] = R[i];
    }
    
    // Sort the array
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < 4; i++) {
            if (sortedR[i] > sortedR[i + 1]) {
                swap(sortedR[i], sortedR[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);

    // Now check for a straight
    for (int i = 0; i < 4; i++) {
        if (sortedR[i] + 1 != sortedR[i + 1]) {
            // Special case for Ace to 5 straight
            if (i == 0 && sortedR[0] == 0 && sortedR[1] == 1 && sortedR[2] == 2 && sortedR[3] == 3 && sortedR[4] == 12) {
                return true; // This is a straight from Ace to 5
            }
            return false;
        }
    }
    return true;
}


bool isPair(int R[]) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (R[i] == R[j]) return true;
        }
    }
    return false;
}

bool isFlush(int S[]) {
    for (int i = 0; i < 4; i++) {
        if (S[i] != S[i + 1]) return false;
    }
    return true;
}

bool isThreeOfAKind(int R[]) {
    for (int i = 0; i < 3; i++) {
        int count = 1;
        for (int j = i + 1; j < 5; j++) {
            if (R[i] == R[j]) count++;
        }
        if (count == 3) return true;
    }
    return false;
}

bool isFourOfAKind(int R[]) {
    for (int i = 0; i < 2; i++) {
        int count = 1;
        for (int j = i + 1; j < 5; j++) {
            if (R[i] == R[j]) count++;
        }
        if (count == 4) return true;
    }
    return false;
}

bool isFullHouse(int R[]) {
    int sortedR[5];
    for (int i = 0; i < 5; i++) {
        sortedR[i] = R[i];
    }
    
    // Sort the array
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < 4; i++) {
            if (sortedR[i] > sortedR[i + 1]) {
                swap(sortedR[i], sortedR[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);

    // Now check for a full house
    if ((sortedR[0] == sortedR[1] && sortedR[1] == sortedR[2] && sortedR[3] == sortedR[4]) || 
        (sortedR[0] == sortedR[1] && sortedR[2] == sortedR[3] && sortedR[3] == sortedR[4])) {
        return true;
    }
    return false;
}
