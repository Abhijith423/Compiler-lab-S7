//Experiment-4

#include <iostream>
#include <string.h>
using namespace std;

char grammar[8][10] = {
    "E->TX",
    "X->+TX",
    "X->1",
    "T->FY",
    "Y->*FY",
    "Y->1",
    "F->(E)",
    "F->1"
};

char nonterminals[] = {'E', 'X', 'T', 'Y', 'F'};
char terminals[] = {'+', '*', '(', ')', '1'};

char FIRST[10], FOLLOW[10];
int fi = 0, fo = 0;

bool isTerminal(char a) {
    for (int i = 0; i < strlen(terminals); i++)
        if (terminals[i] == a)
            return true;
    return false;
}

void first(char x) {
    for (int i = 0; i < 8; i++) {
        if (grammar[i][0] == x) {
            if (isTerminal(grammar[i][3])) {
                FIRST[fi++] = grammar[i][3];
            } else if (grammar[i][3] != x) {
                first(grammar[i][3]);
            }
        }
    }
}

void follow(char x) {
    if (x == 'E') {
        FOLLOW[fo++] = '$';  // end marker
    }

    for (int i = 0; i < 8; i++) {
        int len = strlen(grammar[i]);
        for (int j = 3; j < len; j++) {
            if (grammar[i][j] == x) {
                if (j + 1 < len) {
                    if (isTerminal(grammar[i][j + 1])) {
                        FOLLOW[fo++] = grammar[i][j + 1];
                    } else {
                        fi = 0;
                        first(grammar[i][j + 1]);
                        for (int k = 0; k < fi; k++) {
                            if (FIRST[k] != '1')  // assuming '1' is epsilon
                                FOLLOW[fo++] = FIRST[k];
                        }
                    }
                } else if (grammar[i][0] != x) {
                    follow(grammar[i][0]);
                }
            }
        }
    }
}

int main() {
    cout << "\n\n\t\tGRAMMAR\n\t\t--------\n";
    for (int i = 0; i < 8; i++)
        cout << "\t\t" << grammar[i] << endl;

    cout << "\n\n\t\tFIRST SETS\n\t\t----------\n";
    for (int i = 0; i < sizeof(nonterminals); i++) {
        fi = 0;
        memset(FIRST, 0, sizeof(FIRST));
        first(nonterminals[i]);
        cout << "\tFIRST(" << nonterminals[i] << ") = { ";
        for (int j = 0; j < fi; j++)
            cout << FIRST[j] << " ";
        cout << "}" << endl;
    }

    cout << "\n\n\t\tFOLLOW SETS\n\t\t-----------\n";
    for (int i = 0; i < sizeof(nonterminals); i++) {
        fo = 0;
        memset(FOLLOW, 0, sizeof(FOLLOW));
        follow(nonterminals[i]);
        cout << "\tFOLLOW(" << nonterminals[i] << ") = { ";
        for (int j = 0; j < fo; j++)
            cout << FOLLOW[j] << " ";
        cout << "}" << endl;
    }

    return 0;
}
