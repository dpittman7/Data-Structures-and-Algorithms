//
// Created by deant on 4/9/2021.
//
#include <map>
#include <string>
#include "processor.h"
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

//Default constructor.
processor::processor() {
}

//////////////////////////////////////////////////////////////
// void processor::insertword(string key)
//
// Function: creates a name/frequency pair to be inserted into the 
//           associated map object. [WORD]
//
// Psudocode: Create ki pair
//            Test to see if key has already appeared
//            If so, increment the value of the present key.
//
// References: https://www.cplusplus.com/reference/map/map/insert/
//
// Author: Deanta Pittman
//
////////////////////////////////////////////////////////////////


void processor::insertword(string key) {

    pair<string, int> ki;
    ki.first = key;
    ki.second = 1;
    pair<std::map<string, int>::iterator, bool> ret; //return object of 
    ret = wordlist.insert(ki);
    if (!ret.second) {
        ret.first->second += 1;
    }
}

//////////////////////////////////////////////////////////////
// void processor::insertchar(string key)
//
// Function: creates a name/frequency pair to be inserted into the 
//           associated map object. [CHAR]
//
// Psudocode: Create ki pair
//            Test to see if key has already appeared
//            If so, increment the value of the present key.
//
// References: https://www.cplusplus.com/reference/map/map/insert/
//
// Author: Deanta Pittman
//
////////////////////////////////////////////////////////////////


void processor::insertchar(char key) {

    pair<string,int> ki;

    string temp(1, key);
    ki.first = temp;
    ki.second = 1;
    std::pair<std::map<string,int>::iterator,bool> ret;
    ret = charlist.insert(ki);
    if (!ret.second) {
        ret.first->second += 1;
    }

}

//////////////////////////////////////////////////////////////
// void processor::insertdigit(string key)
//
// Function: creates a name/frequency pair to be inserted into the 
//           associated map object. [WORD]
//
// Psudocode: Create ki pair
//            Test to see if key has already appeared
//            If so, increment the value of the present key.
//
// References: https://www.cplusplus.com/reference/map/map/insert/
//
// Author: Deanta Pittman
//
//
////////////////////////////////////////////////////////////////


void processor::insertdigit(string key) {

    pair<string,int> ki;
    ki.first = key;
    ki.second = 1;
    std::pair<std::map<string,int>::iterator,bool> ret;
    ret = digitlist.insert(ki);
    if (!ret.second) {
        ret.first->second += 1;
    }

}
//////////////////////////////////////////////////////////////
// void processor::analyze_string()
//
// Function: Acts as the central parsign algorithm.
// 
// Psudocode: WHILE input
//            FOR i != input.size()
//            Iterate through input string.
//            Test if current iteration is al/num
//            If so, extract substring of consecutive values.
//            inject into designated MAP.
//            jump to extraction endpoint.
//
// Author: Deanta Pittman 
//
// Reference: cplusplus.com <string>
// ///////////////////////////////////////////////////////////////

void processor::start_parse() {

    //reading from standard input
    cout << "Starting reading in input" << endl;
    string x = "";
    while(cin >> x)
    {	  
            int size = x.size();
            for(int i = 0; i < size;) {
                string extract = " ";
                int type = tolower(x[i]);
                char a;
                a = static_cast<char>(type);

                //Case 1: Word Insert

                if (isalpha(type)) {
                    size_t found = x.find_first_not_of("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ",i);
                    if(found == string::npos){
                       extract = x.substr(i);
                       i = size;}
                    else {int diff = found - i; extract = x.substr(i,diff); i = found;}

                    if(extract.size() > 1){
                        transform(extract.begin(),extract.end(),extract.begin(), ::tolower);
                        insertword(extract);
                        //store each letter as well.
                        for(string::iterator itr = extract.begin(); itr!=extract.end(); ++itr)
                          { char character = *itr; insertchar(character);}

                    } else {insertchar(a); i++;}

                // Case 2: Digit Insert

                }else if(isdigit(type)) {
                    size_t found = x.find_first_not_of("0123456789",i);
                    if(found == string::npos){ // remaining substring is all digits
                         extract = x.substr(i);
                         i = size;}
                    else{ int diff = found - i; extract = x.substr(i,diff); i = found;}

                    if(extract.size() > 1) {
                        insertdigit(extract);
                        for(string::iterator itr = extract.begin(); itr!=extract.end(); ++itr)
                           { char character = *itr; insertchar(character);}

                    } else {insertchar(a); i++;}

               //Default Case: char insert
                } else {insertchar(a); i++;}
            }



    }

cout << "Finished reading input" << endl;
}
/////////////////////////////////////////////////////////////////////////////
// 
// Function: void processor::topword()
//
// Purpose: To retreive the top 10 that is in the associated heap 
//          based off appearence value. [WORD]
//          uses function defined in <algorithm> library.
// 
// PsudoCode: FOR 10 iterations or until empty
//            retreive max element
//            print out retreivedpair object
//            delete from list.
//
// Author: Deanta Pittman
// Date: 4/9/2021
// Reference: https://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map/9371137#9371137
//////////////////////////////////////////////////////////////////////////////

void processor::topword() {

    //time complexity is 10 O(n)
    int i = 0;
    int range = 10;
    while(i < range && !wordlist.empty()) {
        auto best = max_element(wordlist.begin(), wordlist.end(),
                                [](const std::pair<string, int> &a, const std::pair<string, int> &b) -> bool {
                                    return a.second < b.second;
                                });
        cout << best->first << " , " << best->second << "\n";
        wordlist.erase(best);
        i++;
    }

}

/////////////////////////////////////////////////////////////////////////////
// 
// Function: void processor::topdigits()
//
// Purpose: To retreive the top 10 that is in the associated heap 
//          based off appearence value. [DIGITS]
//          uses function defined in <algorithm> library.
// 
// PsudoCode: FOR 10 iterations or until empty
//            retreive max element
//            print out retreivedpair object
//            delete from list.
//
// Author: Deanta Pittman
// Date: 4/9/2021
// Reference: https://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map/9371137#9371137
//////////////////////////////////////////////////////////////////////////////



void processor::topdigits() {

    //time complexity is 10 O(n)
    int i = 0;
    int range = 10;
    while(i < range && !digitlist.empty()) {
        auto best = max_element(digitlist.begin(), digitlist.end(),
                                [](const std::pair<string, int> &a, const std::pair<string, int> &b) -> bool {
                                    return a.second < b.second;
                                });
        cout << best->first << " , " << best->second << "\n";
        digitlist.erase(best);
        i++;
    }
}

/////////////////////////////////////////////////////////////////////////////
// 
// Function: void processor::topcharacters()
//
// Purpose: To retreive the top 10 that is in the associated heap 
//          based off appearence value. [CHAR]
//          uses function defined in <algorithm> library.
//
/// PsudoCode: FOR 10 iterations or until empty
//            retreive max element
//            print out retreivedpair object
//            delete from list.
//
//  Author: Deanta Pittman
//  Date: 4/9/2021
//  Reference: https://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map/9371137#9371137
//////////////////////////////////////////////////////////////////////////////


void processor::topcharacters(){

    //time complexity is 10 O(n)
    int i = 0;
    int range = 10;
    while(i < range && !charlist.empty()) {
        auto best = max_element(charlist.begin(), charlist.end(),
                                [](const std::pair<string, int> &a, const std::pair<string, int> &b) -> bool {
                                    return a.second < b.second;
                                });

        string ascii = best->first;
        cout << ascii << " , " << best->second << "\n";
        charlist.erase(best);
        i++;
    }
}
