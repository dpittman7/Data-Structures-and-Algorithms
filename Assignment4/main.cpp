#include <iostream>
#include <string>
#include "bet.h"

using namespace std;

int main() {
    string postfix;

    // get a postfix expression
    cout << "Enter the first postfix expression: ";
    getline(cin, postfix);

    // create a binary expression tree
    bet bet1(postfix);
    if (!bet1.empty()) {
        cout << "Infix expression: ";
        bet1.printInfixExpression();
    }

        cout << "Postfix expression: ";
        bet1.printPostfixExpression();

        cout << "Number of nodes: ";
        cout << bet1.size() << endl;

        cout << "Number of leaf nodes: ";
        cout << bet1.leaf_nodes() << endl;

        // test copy constructor
        bet bet2(bet1);
        cout << "Testing copy constructor: ";
        bet2.printInfixExpression();
        // test assignment operator
        bet bet3;
        bet3 = bet1;
        cout << "Testing assignment operator: ";
        bet3.printInfixExpression();


    cout << "Enter a postfix expression (or \"quit\" to quit): " << endl;
    while (getline(cin, postfix)) {
        if (postfix == "quit") {
            break;
        }
        if (bet1.buildFromPostfix(postfix)) {
            cout << "Infix expression: ";
            bet1.printInfixExpression();

            cout << "Postfix expression: ";
            bet1.printPostfixExpression();

            cout << "Number of nodes: ";
            cout << bet1.size() << endl;

            cout << "Number of leaf nodes: ";
            cout << bet1.leaf_nodes() << endl;
        }
        cout << "Enter a postfix expression (or \"quit\" to quit): ";
    }

    return 0;
}