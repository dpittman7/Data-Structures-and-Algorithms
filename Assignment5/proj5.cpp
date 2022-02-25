#include <iostream>
#include <string>
#include "passserver.h"
#include <utility>

using namespace std;
using namespace cop4530;
void interface(int);

    int main() {
        cout << "input desired size of database ";
        int size;
        cin >> size;
        if (size < 2)
	{std::cout << "size is too small, defaulting to an initial size of 2" << std::endl;
	size = 2;}
        interface(size);
        return 0;
    }

void Menu() {

    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

void interface(int size) {
    PassServer database(size);

    char input;

    Menu();
    cin >> input;
    do{

    switch (input) {
        case 'l': {
            char temp[100];
            cout << "input name of file";
            cin >> temp;
            bool success = database.load(temp);
            if (success)
                cout << "members from file has been loaded." << endl;
            break;
        }
        case 'a': {
            pair<string,string> userpass;
            cout << "insert the username" << endl;
            cin >> userpass.first;
            cout << "insert the associated password" << endl;
            cin >> userpass.second;
            bool success = database.addUser(userpass);
            if (success)
                cout << "member has been inserted" << endl;
            break;
        }
        case 'r': {
            string user;
            cout << "insert the username" << endl;
            cin >> user;
            bool success = database.removeUser(user);
            if (success)
                cout << "member has been removed." << endl;
            else cout << "Unknown. user was not removed.";
            break;
        }
        case 'c': {
            string user;
            string inputpass;
            string newpass;
            cout << "enter username to be changed" << endl;
            cin >> user;
            cout << "enter current password" << endl;
            cin >> inputpass;

            pair<string,string> userpass;
            userpass.first = user;
            userpass.second = inputpass;

            cout << "input desired new password" << endl;
            cin >> newpass;

            bool success = database.changePassword(userpass, newpass);
            if (!success)
		cout << "requested pass was not updated" << endl;
            break;
        }
        case 'f': {
            string user;
            cout << "insert the username" << endl;
            cin >> user;
            bool success = database.find(user);
            if (success)
                cout << "member  " + user + " has been found" << endl;
            else
                cout << "member not located" << endl;
            break;
        }
        case 'd': {
            cout << "dumping data base" << endl;
            database.dump();
            break;
        }
        case 's': {
            int size = database.size();
            cout << "The total members in the hashtable is " << to_string(size) << " ." << endl;
            break;
        }
        case 'w': {
            char temp[100];
            cout << "input filename: ";
            cin >> temp;
            bool success = database.write_to_file(temp);
            if (success)
                cout << " \ndata been placed into file " << temp << endl;
            else cout << "error writing to file" << endl;
            break;
        }
        case 'x': {
            cout << "terminating program" << endl;
            break;

        }
        default: { cout << "insert valid option" << endl;
        }
    }
    if(input != 'x'){
    Menu();
    cin >> input;}
    } while(input != 'x');
}
