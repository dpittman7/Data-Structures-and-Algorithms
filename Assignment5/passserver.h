//
// Created by deant on 3/26/2021.
//

#ifndef ASSIGNMENT5_PASSSERVER_H
#define ASSIGNMENT5_PASSSERVER_H

#include "hashtable.h"
#include <cstdlib>
#include <string>
#include <crypt.h>


namespace cop4530 {
class PassServer: private HashTable<std::string,std::string> {

    public:
        explicit PassServer(size_t size = 101);
        ~PassServer();


        bool load(const char *filename);
        bool addUser(std::pair<std::string, std::string> &kv);
        bool addUser(std::pair<std::string, std::string> &&kv);
        bool removeUser(const std::string & k);
        bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword);
        bool find(const std::string & user);
        void dump();
        size_t size();
        bool write_to_file(const char *filename);

    private:
        std::string encrypt(const std::string & str);
        HashTable<std::string,std::string> *passserver;



    };

}



#endif //ASSIGNMENT5_PASSSERVER_H
