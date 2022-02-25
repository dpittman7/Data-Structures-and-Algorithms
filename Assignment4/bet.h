#ifndef _bet_H_
#define _bet_H_

#include <string>
#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

class bet
{
    struct BinaryNode
    {
        string element;
        BinaryNode * left;
        BinaryNode * right;
    };
public:
    bet();
    bet(string postfix);
    bet(const bet&);
    ~bet();
    bool buildFromPostfix(string postfix);
    const bet & operator= (const bet &);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();
    vector<string> extract(string);
    bool isoperator(string);
    bool validpostfix(vector<string>);




private:
    BinaryNode * root;
    map<string, int> operators;
    void printInfixExpression(BinaryNode *n);
    void printPostfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);
    string final = "";
    void init();


    friend string inorder_traverse(BinaryNode * &n, int precedence);
    friend string postorder_traverse(BinaryNode * &n);

};

#endif