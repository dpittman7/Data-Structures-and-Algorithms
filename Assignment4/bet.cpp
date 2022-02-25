//
// Created by deant on 3/11/2021.
//

#include "bet.h"


// *******************************************************************************************************
// * Function Name: bet::bet()                                                                           *
// * Description:                                                                                        *
// *                                                                                                     *
// *                                                                                                     *
// * Parameter Description: iList: initialization list of type T. Used to get values of nodes elements.  *
// * Date:  03/09/2021                                                                                   *
// * Author: Deanta Pittman                                                                              *
// * Referenes:                                                                                          *
// *******************************************************************************************************
bet::bet() {

    init();
}

// *******************************************************************************************************
// * Function Name: bet::bet(const postfix)                                                              *
// * Description:                                                                                        *
// *                                                                                                     *
// *                                                                                                     *
// * Parameter                                                                                           *
// * Date:  03/09/2021                                                                                   *
// * Author: Deanta Pittman                                                                              *
// * Referenes:                                                                                          *
// *******************************************************************************************************

bet::bet(const string postfix) {
    bool success = true;
    init();
    vector<string> a = extract(postfix);
    success = this->buildFromPostfix(postfix);
    if(!success)
        makeEmpty(root);
}


bet::~bet() {

    makeEmpty(root);
}







// *******************************************************************************************************
// * Function Name: bool bet::buildFromPostfix(const string postfix)                                     *
// * Description:                                                                                        *
// *                                                                                                     *
// *                                                                                                     *
// * Parameter Description: iList: initialization list of type T. Used to get values of nodes elements.  *
// * Date:  03/09/2021                                                                                   *
// * Author: Deanta Pittman                                                                              *
// * Referenes: Data Structures and Algorithms in C++, page 129                                          *
// *****************************************************************


bool bet::buildFromPostfix(const string postfix) {
    bool error = false;
    vector<string> expression = extract(postfix);
    stack<BinaryNode *> tree_constructor;

    error = validpostfix(expression);
    int i = 0;
    int range = expression.size();

    //We read our expression one symbol at a time.
     while(i < range && !error) {
         //if the symbol is an operand,
        if (!isoperator(expression[i]))
        {
            //we create a one-node tree
            BinaryNode* onenode = new BinaryNode;
            onenode->element = expression[i++];
            onenode->left = nullptr;
            onenode->right = nullptr;
            //and push a pointer to it onto a stack.
            tree_constructor.push(onenode);

        }

        //if the symbol is an operator, we pop the pointers to two trees T1 and T2 from the stack.
        // need to test if there is a minimum of two on stack else error case.
        else {
            if(tree_constructor.size() < 2){
                makeEmpty(root);
                error = true;
            }else {
                //form a new tree whose root is the operator
                root = new BinaryNode;
                root->element = expression[i++]; //assigns current operator and increments expression transversal
                //and left/right is T1 and T2
                root->right = tree_constructor.top();
                tree_constructor.pop();
                root->left = tree_constructor.top();
                tree_constructor.pop();
                // push new pointer onto stack.
                tree_constructor.push(root);
            }
        }
     }
     if(!error) {
         //What the algorithm yield is a BinaryNode pointer to the root node of the Expression Tree
         root = tree_constructor.top();
         tree_constructor.pop();

         // --- End Algorithm -- //

         //If stack is not clear by the end of algorithm, then error case.
         if (!tree_constructor.empty()) {
             makeEmpty(root);
             error = true;

         }
     }

    return !error;
}

// *************************************************************************************************************
// * Function Name: bool isoperator(string token)                                                              *
// * Description: Test to see if parameter string is an key in the map object.                                 *
// *         if value is not found, find() returns location of end() itr. uses this test to determine presence.*
// *                                                                                                           *
// * Parameter Description: string token: passed string value from tokenized postfix expression.               *                                                      *
// * Date:  03/11/2021                                                                                         *
// * Author: Deanta Pittman                                                                                    *
// * Referenes:https://www.geeksforgeeks.org/map-find-function-in-c-stl/#:~:text=The%20map::find%20()%20is%20a%20built-in%20function%20in,constant%20iterator%20which%20refers%20to%20map.end%20()%20.                                                                                       *
// *****************************************************************

bool bet::isoperator(string token) {
    auto itr = operators.find(token);
    bool equal = itr == operators.end();
    return !equal;
}



// *******************************************************************************************************
// * Function Name: void init()                                                                          *
// * Description: Default initalization of the class data members.                                                                                        *
// *         Set the root to nullptr and set the operator map object to key/pair values.                *
// *                                                                                                    *
// * Parameter Description:                             *                                               *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:                                                                                         *
// *****************************************************************


void bet::init()
{
    root = nullptr;
    operators["("] = 3;
    operators[")"] = 3;
    operators["/"] = 2;
    operators["*"] = 2;
    operators["+"] = 1;
    operators["-"] = 1;
}

// *******************************************************************************************************
// * Function Name: vector<string> extract(postfix)                                                     *
// * Description:  takes the space seperated postfix expression and stores it into a string vector.     *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                             *                                               *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.geeksforgeeks.org/tokenizing-a-string-cpp/                                                                                         *
// *****************************************************************
vector<string> bet::extract(string postfix){
    vector<string> extract;
    stringstream check1(postfix);
    string intermediate;
    //extract index value of string and store it in vector
    while(getline(check1, intermediate, ' '))
    {
        extract.push_back(intermediate);
    }

    return extract;
}

// *******************************************************************************************************
// * void bet::printInfixExpression(bet::BinaryNode *n)                                                     *
// * Description: Uses inorder transversal to store elements in node in string and prints result        *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                             *                                               *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:                                                                                         *
// *****************************************************************

// Strategy: Transverse to lowest depth of tree. Transversing left side.
// Need to test, need to implement parenthesis portion.
void bet::printInfixExpression(bet::BinaryNode *n) {
    //origninally had the inorder traverse algorithm within this expression
    //however the bug occured that once the traversal reached the leaf node, the parent call
    //would begin there resulting in segmentation error. Implementing an transversal function keeps the initial value of
    // n relevant to the initial function call
    //solving that problem.
   if(!empty())
   {
       final = inorder_traverse(n,operators[n->element]);
       cout << final << endl;
   }
}

// *******************************************************************************************************
// * void bet::makeEmpty(bet::BinaryNode *&t)                                                                  *
// * Description: Uses a recursive definition to transverse the tree accessing and deleting nodes until empty  *
// *                                                                                                           *
// *                                                                                                           *
// * Parameter Description:                                                                                    *
// * Date:  03/11/2021                                                                                         *
// * Author: Deanta Pittman                                                                                    *
// * Referenes:                                                                                                *
// *****************************************************************
void bet::makeEmpty(bet::BinaryNode *&t) {

    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr; // when case arises, t will be at root.


}

// *******************************************************************************************************
// * Function Name: bool bet::empty()                                                                     *
// * Description: Checks for an empty list by testing node.                                               *
// *                                                                                                      *
// *                                                                                                      *
// * Parameter Description                                                                                *
// * Date:  03/11/2021                                                                                    *
// * Author: Deanta Pittman                                                                               *
// * Referenes:                                                                                         *
// *****************************************************************


bool bet::empty() {
    return (root==nullptr);
}

// *******************************************************************************************************
// * void bet::printInfixExpression()                                                                   *
// * Description: Prints the infixExpression of the expression tree.                                    *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.includehelp.com/data-structure-tutorial/level-order-traversal-on-a-binary-tree.aspx                                                                    *
// *****************************************************************
void bet::printInfixExpression() {

     printInfixExpression(root);


}

// *******************************************************************************************************
// * void bet::printPostfixExpression(bet::BinaryNode *n)                                                *
// * Description: Prints the postfix expression expressed by expression tree                             *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.includehelp.com/data-structure-tutorial/level-order-traversal-on-a-binary-tree.aspx                                                                    *
// *****************************************************************
void bet::printPostfixExpression(bet::BinaryNode *n) {

    if(!empty())
    {
        final = postorder_traverse(n);
        cout << final << endl;
    }

}

// *******************************************************************************************************
// * bool bet::validpostfix(vector<string> postfix)                                                      *
// * Description: Evaluates the string to see oif its a proper postfix. valid = operand - operators      *
// *                                                                                                     *
// *                                                                                                     *
// * Parameter Description: string postfix: the user passed postfix string to be evaluated.               *
// * Date:  03/11/2021                                                                                   *
// * Author: Deanta Pittman                                                                              *
// * Referenes:                                                                   *
// *****************************************************************

bool bet::validpostfix(vector<string> postfix){

    map<string, int> operators;
    operators["("] = 3;
    operators[")"] = 3;
    operators["/"] = 2;
    operators["*"] = 2;
    operators["+"] = 1;
    operators["-"] = 1;

    auto itr = postfix.begin();
    auto itr2 = postfix.end();
    stack<string> evaluate;
    string token_value;
    bool error = false;

    while((itr != itr2) and !error) {
        token_value = *itr;
        if (operators[token_value] < 1 || operators[token_value] > 3)
            evaluate.push(*itr++);
        else if (evaluate.empty()) {
            cout << " too many operators" << endl;
            error = true;
        } else {
            evaluate.pop();
            itr++;
        }
    }

    if (evaluate.size() > 1){
        cout << "too many operands" << endl;
        error = true;
    }

    return error;






}


// *******************************************************************************************************
// * string traverse(bet::BinaryNode *&n, int precedence)                                                     *
// * Description: Uses a recursive definition to transverse the tree accessing and deleting nodes until empty     *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.tutorialspoint.com/cplusplus-program-to-perform-inorder-recursive-traversal-of-a-given-binary-tree#:~:text=C++%20Programming%20Server%20Side%20Programming%20Tree%20traversal%20is,the%20tree%20in%20the%20order%20(Left,%20Root,%20Right).                                                                                         *
// *****************************************************************

string inorder_traverse(bet::BinaryNode *&n, int precedence) {
    //Function is outside class, threfore, doesnt have access to this private data member
    map<string, int> operators;
    operators["("] = 3;
    operators[")"] = 3;
    operators["/"] = 2;
    operators["*"] = 2;
    operators["+"] = 1;
    operators["-"] = 1;
    string ans;

    string infix;
    if (n != nullptr) {
        if (operators.count(n->element) < 1) {
            return n->element;
        } else {
            //Inorder traversal
            if (n->left == nullptr) {} else infix += inorder_traverse(n->left, operators[n->element]);
            infix += " " + n->element + " ";
            if (n->right == nullptr) {} else infix += inorder_traverse(n->right, operators[n->element]);

            if (operators[n->element] <= precedence)
                infix = "( " + infix + " )";
        }


    }
    return infix;
}

// *******************************************************************************************************
// * string postorder_traverse(bet::BinaryNode *&n)                                                     *
// * Description: Uses a recursive definition to transverse the tree in preorder fashion.               *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.krivalar.com/data-structures-expression-tree                                                                    *
// *****************************************************************

string postorder_traverse(bet::BinaryNode *&n) {
    //Function is outside class, threfore, doesnt have access to this private data member
    map<string, int> operators;
    operators["("] = 3;
    operators[")"] = 3;
    operators["/"] = 2;
    operators["*"] = 2;
    operators["+"] = 1;
    operators["-"] = 1;
    string ans;

    string postfix;
    if (n != nullptr) {
        if (operators.count(n->element) < 1) {
            return n->element;
        } else {
            //Postorder traversal
            if (n->left == nullptr) {} else postfix += postorder_traverse(n->left);
            if (n->right == nullptr) {} else postfix += postorder_traverse(n->right);
            postfix += " " + n->element + " ";
        }


    }
    return postfix;
}

// *******************************************************************************************************
// * void bet::printPostfixExpression()                                                                  *
// * Description: base expression for the print function node.                                          *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:                                                                 *
// *****************************************************************
void bet::printPostfixExpression() {

    printPostfixExpression(root);

}

// *******************************************************************************************************
// * size_t bet::size()                                                                                 *
// * Description: Base function for determining size of root.                                           *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/                                                                    *
// *****************************************************************

size_t bet::size() {

    if(empty())
        return 0;
    else {
     return size(root);

    }

}

// *******************************************************************************************************
// * size_t bet::size(bet::BinaryNode *t)                                                               *
// * Description: Uses a recursive definition to transverse tree to determine size.                     *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/                                                                    *
// *****************************************************************
size_t bet::size(bet::BinaryNode *t) {

size_t size1 = 0;
    if(empty())
        return 0;
    else {
        if (t->left == nullptr){} else size1 += size(t->right);
        if (t->right == nullptr){} else size1 += size(t->left);
        size1++;
        return size1;

    }
}

// *******************************************************************************************************
// * size_t bet::leaf_nodes(bet::BinaryNode *t)                                                         *
// * Description: Uses a recursive definition to transverse tree to determine leaf nodes.               *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.includehelp.com/data-structure-tutorial/level-order-traversal-on-a-binary-tree.aspx                                                                    *
// *****************************************************************

size_t bet::leaf_nodes(bet::BinaryNode *t) {
    size_t leaf = 0;
    queue<BinaryNode*> q;
    BinaryNode* temp;
    q.push(t);
    while(!q.empty()) {
        temp = q.front();
        q.pop();
        if (!empty()) {
            if (temp->left == nullptr and temp->right == nullptr)
                leaf++;
            else {
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
        }
    }

        return leaf;

    }

// *******************************************************************************************************
// * size_t bet::leaf_nodes(bet::BinaryNode *t)                                                         *
// * Description: Uses a recursive definition to transverse tree to determine leaf nodes.               *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.includehelp.com/data-structure-tutorial/level-order-traversal-on-a-binary-tree.aspx                                                                    *
// *****************************************************************
size_t bet::leaf_nodes() {
    return leaf_nodes(root);
}

// *******************************************************************************************************
// * bet::BinaryNode * bet::clone(bet::BinaryNode *t)                                                   *
// * Description: Creates a copy node and initiatizes a new tree using levelorder transversal           *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://www.includehelp.com/data-structure-tutorial/level-order-traversal-on-a-binary-tree.aspx                                                                    *
// *****************************************************************
bet::BinaryNode * bet::clone(bet::BinaryNode *t) {
    if(t == NULL)
    {
         return nullptr;
    }
    else
    {
        BinaryNode *node = new BinaryNode();
        node->element = t->element;
        node->left = clone(t->left);
        node->right = clone(t->right);
        return node;
    }
}

// *******************************************************************************************************
// * const bet& bet::operator=(const bet & a )                                                          *
// * Description: operator overload to initiaite the clone function for the rhs.                        *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:                                                                   *
// *****************************************************************

const bet& bet::operator=(const bet & a ) {
    makeEmpty(root);
    root = clone(a.root);
    return *this;
}

// *******************************************************************************************************
// * bet::bet(const bet & a)                                                                            *
// * Description: the copy constructor that calls the clone function using the parameter bet object.    *
// *                                                                                                    *
// *                                                                                                    *
// * Parameter Description:                                                                             *
// * Date:  03/11/2021                                                                                  *
// * Author: Deanta Pittman                                                                             *
// * Referenes:https://stackoverflow.com/questions/10481982/deep-copy-constructor-for-binary-tree                                                                   *
// *****************************************************************

bet::bet(const bet & a) {
    root = clone(a.root);
}




















