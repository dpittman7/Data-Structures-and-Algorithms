//
// Created by deant on 3/26/2021.
//


#include "passserver.h"

// *************************************************************************************
// * Function Name: cop4530::PassServer::PassServer(size_t size)                       *
// * Description: Default constructor for the PassServer object.                       *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description: Constructs a passserver of size primebelow(size)           *
// *                       Ensure that size > 0 or else find() has failcase.           *
// * Date:  03/25/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************
cop4530::PassServer::PassServer(size_t size) {
    passserver = new HashTable<std::string, std::string>(size);

}

// *************************************************************************************
// * Function Name: cop4530::PassServer::PassServer(size_t size)                       *
// * Description: load function of the adapter class PassServer. Calls Adaptee class   *
// *              HashTable load function                                              *
// *                                                                                   *
// * Parameter Description: the name of the file to draw entries from                  *
// * Date:  03/25/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

bool cop4530::PassServer::load(const char *filename) {
    return passserver->load(filename);
}


// ******************************************************************************************
// * Function Name: std::string cop4530::PassServer::encrypt(const std::string &str)        *
// * Description: Uses the unix native crypt funciton to encrypt the passwords inside server*
// *              HashTable load function                                                   *
// *                                                                                        *
// * Parameter Description: The string to be encrypted                                      *
// * Date:  4/1/2021                                                                        *
// * Author: Deanta Pittman                                                                 *
// * Referenes: scrypt.cpp, Gaitros Office Hours 3/29/2021
// *
// *****************************************************************

std::string cop4530::PassServer::encrypt(const std::string &str) {
	//initiate char[] and pointers to store 
    char salt[] = "$1$########";
    char * cryptpass = new char [100];
	
    //call unix crypt function return char[] *note: <crypt.h> and -lcrypt needed.
    cryptpass = crypt(str.c_str(), salt);

	//convert char[] to string by constructor
    std::string raw_encrypt(cryptpass);
   // std::cout << "encryptedpass value" << raw_encrypt << std::endl;

	//trim salt off raw_encrypt ->index of 3rd 'S' (assumes encrypted substr will never have '$')
    int trim_index = raw_encrypt.find_last_of('$'); 
   // std::cout << "trim_index value" << trim_index << std::endl;

	//retreive/return ecrypted substr
    std::string encrypted = raw_encrypt.substr((trim_index+1));
    return encrypted;
}

// *************************************************************************************
// * Function Name:bool cop4530::PassServer::addUser(std::pair<std::string, std::string> &kv)                       *
// * Description: insert function of the adapter class PassServer.
// *              Preps user passsed data and calls Adaptee class insert function to execute *
// *              HashTable  function                                                        *
// *                                                                                         *
// * Parameter Description: kv-> user/pass pair to be evaluated and inserted.                *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************

bool cop4530::PassServer::addUser(std::pair<std::string, std::string> &kv) {
  std::string plaintext = kv.second;
 //std::cout << "addUser passstring " << plaintext << std::endl;
   std::string ecryptedpass = encrypt(plaintext);
  //std::cout << "encryptedpass value post encrypt() " << ecryptedpass << std::endl;
   std::string finalpass = ecryptedpass.substr(12); //$1$#######$ + finalpass
   kv.second = finalpass;
    return passserver->insert(kv);
}

// *************************************************************************************
// * Function Name:bool cop4530::PassServer::addUser(std::pair<std::string, std::string> &kv)                       *
// * Description: insert function of the adapter class PassServer.
// *              Preps user passsed data and calls Adaptee class insert function to execute *
// *              HashTable  function. Move version.                                         *
// *                                                                                         *
// * Parameter Description: kv-> user/pass pair to be evaluated and inserted.                *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************

bool cop4530::PassServer::addUser(std::pair<std::string, std::string> &&kv) {
    std::string plaintext = kv.second;
    std::string ecryptedpass = encrypt(plaintext);
    std::string finalpass = ecryptedpass.substr(12); //$1$#######$ + finalpass
    kv.second = ecryptedpass;
    return passserver->insert(kv);
}

// *******************************************************************************************
// * Function Name:bool cop4530::PassServer::removeUser(const std::string &k)                *
// * Description: remove function of the adapter class PassServer.
// *               Calls adaptee function remove with the passed parameter k                 *
// *                                                                                         *
// *                                                                                         *
// * Parameter Description: k -> username to be removed                                      *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************

bool cop4530::PassServer::removeUser(const std::string &k) {
    return passserver->remove(k);
}

bool cop4530::PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword) {
    std::string raw_ogpass = encrypt(p.second);
    std::string encrypt_ogpass = raw_ogpass.substr(12); //$1$#######$ + finalpass
    std::pair<std::string,std::string> temp = p;
    temp.second = encrypt_ogpass;
    if(passserver->match(temp) && (p.second != newpassword)) {
       temp.second = encrypt(newpassword);;
       return  passserver->insert(temp);
    } else return false;

}

// *******************************************************************************************
// * Function Name:bool cop4530::PassServer::find(const std::string &user)                   *
// * Description: contain function of the adapter class PassServer.
// *               Calls adaptee function contains with the passed parameter user            *
// *                                                                                         *
// *                                                                                         *
// * Parameter Description: k -> username to be searched                                     *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************
bool cop4530::PassServer::find(const std::string &user) {
    return passserver->contains(user);
}

// *******************************************************************************************
// * Function Name:void cop4530::PassServer::dump()                                          *
// * Description: dump function of the adapter class PassServer.
// *               Calls adaptee function dump().                                            *
// *                                                                                         *
// *                                                                                         *
// * Parameter Description:                                                                  *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************
void cop4530::PassServer::dump() {
    passserver->dump();
}

// *******************************************************************************************
// * Function Name:void cop4530::PassServer::size()                                          *
// * Description: size function of the adapter class PassServer.
// *               Calls adaptee function getSize().                                            *
// *                                                                                         *
// *                                                                                         *
// * Parameter Description:                                                                  *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************

size_t cop4530::PassServer::size() {
    return passserver->getSize();
}

// *******************************************************************************************
// * Function Name:bool cop4530::PassServer::write_to_file(const char *filename)             *
// * Description: Adapter function of the write_to_file funciton
// *               Calls adaptee function write_to_file() with passed parameter.                                            *
// *                                                                                         *
// *                                                                                         *
// * Parameter Description: filename -> the name of the source file.                         *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************

bool cop4530::PassServer::write_to_file(const char *filename) {
    return passserver->write_to_file(filename);
}

// *******************************************************************************************
// * Function Name:cop4530::PassServer::~PassServer()                                        *
// * Description: default destructor.
// *              reallocates the memory of the passserver object. Destructor is in base class                           *
// *                                                                                         *
// *                                                                                         *
// * Parameter Description:                                                                  *
// * Date:  03/25/2021                                                                       *
// * Author: Deanta Pittman                                                                  *
// * Referenes:                                                                              *
// *****************************************************************

cop4530::PassServer::~PassServer(){
delete passserver;
}

