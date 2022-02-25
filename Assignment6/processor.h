//
// Created by deant on 4/9/2021.
//

#ifndef ASSIGNMENT6_PROCESSOR_H
#define ASSIGNMENT6_PROCESSOR_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class processor {
public:
    processor();  //Trivial Construtor
    void start_parse(); // Starts the parsing algorithm Uses insert helper func.

    void topword(); 
    void topdigits();
    void topcharacters();


private:
    map<string, int> wordlist;
    map<string, int> charlist;
    map<string, int> digitlist;

    void insertword(string);
    void insertchar(char);
    void insertdigit(string);
    };

#endif //ASSIGNMENT6_PROCESSOR_H
