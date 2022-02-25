#include <iostream>
#include "Stack.h"
#include <cmath>
#include <string>


using namespace std;
using namespace cop4530;


vector<string> infixConversion(vector<string> expression);
float postfixEvaluation(vector<string> postfix_string);
int precedence(basic_string<char> a);
bool validinfixExpression(vector<string> expression);
bool validoperators(vector<string> expression);

int main() {

    const string key = "stop";
    const string trigger = "end";
    string read_value, terminate = " ";
    vector<string> infix;

    while(terminate != trigger) {
        infix.clear();
        cout << " Insert your expressions, a space between each term \n";

        cin >> read_value;

        while (read_value != key) // Function will continue to read values until stop is read
            //Each entry must be seperated by a space in order to properly function
        {
            infix.push_back(read_value);
            cin >> read_value;
        }

        bool validparenthesis = validinfixExpression(infix);
        bool validoperator = validoperators(infix);
        bool validinfix = (validoperator && validparenthesis);

        if (validinfix) {
            vector<string> postfix = infixConversion(infix);
            auto itr = postfix.begin();
            int endrange = postfix.size();
            int iteration = 0;
            while (iteration != endrange) {
                cout << *itr++ << " ";
                iteration++;
            }

            float result = postfixEvaluation(postfix);

            if (result == 0)
                cout << "Can not calculate expressions" << endl;
            else
                cout << "The value of the expression is " << result << endl;
        } else {
            if (!validparenthesis)
                cout << "ERROR: UNBALANCED PARENTHESIS";
            if (!validoperator)
                cout << "ERROR: INVALID EXPRESSION";
        }

        cout << " Type in end to stop script, else enter any key" << endl;

        cin >> terminate;
    }

    return 0;
}

// ************************************************************************************
// * Function Name: int precedence(char a)                                            *
// * Description: Returns a integer that indicates the precedence of the passed operator
// *               Uses the index of the operator in the string to determine.         *
// * Parameter Description:char c -> the passed in operator to be evaluated.          *
// * Date:  02/20/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes:                                                                       *
// ************************************************************************************
int precedence(string a)
{
    string precedenceOrder = "^*/+- ( )";

    int place = precedenceOrder.find(a[0]);

    return place;
}

// ***************************************************************************************
// * Function Name: vector<string> infixConversion(vector<string> e)                     *                    *
// * Description: An implementation of the shunting Yard Algorithm described in the      *
//                reference provided.                                                    *
// *                                                                                     *
// * Parameter Description: vector<string> e : a string vector where each element is     *
//                                           a term in the standard expression.          *
//                                    Capitalize on the iteration property of the vector *
//                                    STL in order to transverse the items.              *
// * Date:  02/20/2021                                                                   *
// * Author: Deanta Pittman                                                              *
// * Referenes: http://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/     *                                                                 *
// ***************************************************************************************
    vector<string> infixConversion(vector<string> expression)
    {
        vector<string> result;
        Stack<string> operators;
        int prevPrecedence = 300;
        //Scan the infix expression from left to right.

        auto itr = expression.begin(); //Initialize an iterator to transverse string.
        int endrange = expression.size();
        int iteration = 0;
        while(iteration != endrange)
        {
            char test = *itr->c_str();
            //Test to see of scanned character is an operand
            if(isalnum(test))
            {
                result.push_back(*itr);
                itr++;
                iteration++;
            }
            else
            {
                //Determine precedence of operators

                int precedenceValue = ceil((double)precedence((itr[0])) / 2);
                if(!operators.empty())
                     prevPrecedence = ceil((double)precedence(operators.top()) / 2);
                if(precedenceValue == 3) // if itr value is '('
                {
                    operators.push(itr[0]);
                    itr++;
                    iteration++;
                }
                else if(precedenceValue == 4)
                {
                    while(operators.top() != "(") //Pop until top value is '('
                    {
                        result.push_back(operators.top());
                        operators.pop();
                    }

                    operators.pop(); //Discard top '('
                    itr++;
                    iteration++;
                }

                else if(precedenceValue < prevPrecedence || operators.empty()) //Lower value, greater precedence.
                {
                    operators.push(*itr);
                    itr++;
                    iteration++;
                } else{
                    while(precedenceValue >= prevPrecedence && !operators.empty())
                    {
                        result.push_back(operators.top());
                        operators.pop();
                        if(!operators.empty())
                            prevPrecedence = ceil((double)precedence(operators.top()) / 2);
                    }
                    operators.push(*itr);
                    itr++;
                    iteration++;
                }

            }
        }
        while(!operators.empty()) {
            result.push_back(operators.top());
            operators.pop();
        }
        return result;
    }

// *********************************************************************************************
// * Function Name: float postfixEvaluation(vector<string> postfix)                            *
// * Description: Explicit Implementation of the algorithm described in the reference material *
// *                                                                                           *
// * Parameter Description:string<vector> postfix: passes in an expression in postfix          *
// *                                        form to be evaluated.                              *
// * Date:  02/20/2021                                                                         *
// * Author: Deanta Pittman                                                                    *
// * Resource: https://www.tutorialspoint.com/program-to-evaluate-postfix-notation-in-cplusplus*                                                                    *
// *********************************************************************************************
//
float postfixEvaluation(vector<string> postfix_string)
{
    Stack<double> operand;
    auto itr = postfix_string.begin();
    auto endvalue = postfix_string.at(postfix_string.size() - 1);
    bool alphaFlag, errorflag = false;
    float a,b;
    int endrange = postfix_string.size();
    int iteration = 0;
    while(iteration != endrange && !errorflag)
    {
        char test = *itr->c_str();
        if(isalnum(test)){ //test to see if term is not operand.
            if(isalpha(test)) { // Test to see if term is a letter. If so, no need to calculate the rest.
                alphaFlag = true;
                break;
            }
            double value = std::stof(*itr);
            operand.push(reinterpret_cast<double &&>(value));
            itr++;
            iteration++;
        } else{
            switch(test)
            {
                case '^': {
                    a = operand.top();
                    operand.pop();
                    b = operand.top();
                    operand.pop();
                    float result = pow(b,a);
                    operand.push(result);
                    itr++;
                    iteration++;
                    break;
                }
                case '*' : {
                    a = operand.top();
                    operand.pop();
                    b = operand.top();
                    operand.pop();
                    float result = b * a;
                    operand.push(result);
                    itr++;
                    iteration++;
                    break;
                }
                case '/' : {
                    a = operand.top();
                    operand.pop();
                    b = operand.top();
                    operand.pop();
                    float result = b / a;
                    operand.push(result);
                    itr++;
                    iteration++;
                    break;
                }
                case '+' : {
                    a = operand.top();
                    operand.pop();
                    b = operand.top();
                    operand.pop();
                    float result = b + a;
                    operand.push(result);
                    itr++;
                    iteration++;
                    break;
                }
                case '-' : {
                    a = operand.top();
                    operand.pop();
                    b = operand.top();
                    operand.pop();
                    float result = b - a;
                    operand.push(result);
                    itr++;
                    iteration++;
                    break;
                }
                default:{
                    errorflag = true;
                    }
            }
        }
    }
    return !alphaFlag ? operand.top() : 0;
}

// *********************************************************************************************
// * Function Name: bool validinfixExpression(vector<string> expression)                       *
// * Behavior: Test to see if infix parenthesis is balanced by pairing push() pop()            *
// *           returns true if final parenthesis is final and a segmentation flag isnt raised. *
// * Parameter Description:string<vector> expression: Stores the series of inputs of user to   *
// *                                        be evaluated.                                      *
// * Date:  02/20/2021                                                                         *
// * Author: Deanta Pittman                                                                    *
// * RESOURCE: http://pages.cs.wisc.edu/~siff/CS367/Notes/stacks.html                          *
// *********************************************************************************************


bool validinfixExpression(vector<string> expression)
{
    Stack<string> parenthesis;
    auto itr = expression.begin();
    bool errorFlag = false;
    int endrange = expression.size();
    int iteration = 0;
    while(iteration != endrange  && !errorFlag)
    {
        if(*itr == "(") {
            parenthesis.push(*itr++);
            iteration++;
        }
        else if(*itr == ")") {
            if (!parenthesis.empty()) {
                parenthesis.pop();
                itr++;
                iteration++;
            } else
                errorFlag = true;
        } else {itr++; iteration++;}
    }
    return (parenthesis.empty() && !errorFlag);
    }

// *********************************************************************************************
// * Function Name: bool validoperators(vector<string> expression)                                *
// * Behavior: The difference of total terms and operators in valid standard expression will be 1 *
// *           Evalutes number of operators/operands and test if difference is true.              *
// * Parameter Description:string<vector> expression: Stores the series of inputs of user to      *
// *                                        be evaluated.                                         *
// * Date:  02/20/2021                                                                            *
// * Author: Deanta Pittman                                                                       *
// * RESOURCE: http://pages.cs.wisc.edu/~siff/CS367/Notes/stacks.html                             *
// *********************************************************************************************

bool validoperators(vector<string> expression)
{
    int operands = 0, operators = 0;
    auto itr = expression.begin();
    int endrange = expression.size();
    int iteration = 0;
    while(iteration != endrange)
    {
        char test = *itr->c_str();
        if(*itr == ")" || *itr == "(") {
            itr++;
            iteration++;
        }
        else if(isalnum(test)) {
            operands++;
            iteration++;
            itr++;
        }
        else
        {
            operators++;
            iteration++;
            itr++;
        }
    }
 //   isalnum(*itr->c_str()) ? operands++ : operators++;
    int difference = operands - operators;
    return (difference == 1);
    }



