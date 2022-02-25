

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::HashTable(size_t)                *
// * Description: Default constructor for the hashtable object  .                     *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description: Constructs a hashtable of size primebelow(size)           *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes:                                                                       *
// *****************************************************************

template<typename K, typename V>
cop4530::HashTable<K, V>::HashTable(size_t size) {

    hashsize = prime_below(size);
    hashtable.resize(hashsize); // constructs the hashtable vector
                                 // with size elements all initialized to nullptr.
    totalelements = 0;


}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::myhash(const K &k)               *
// * Description: hashvalue generator for the passed key. Converts type to string.    *
// *              function fails if key object is not convertible to string type.     *
// *                                                                                  *
// * Parameter Description:                                                           *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes: Data Structures and Algorithms in C++ pg.195                          *
// *****************************************************************
//Dev notes:
//Hash function method: To scan the object for each character and scale it to then
//modulate it to fit in the hash space of the situation.
//Using string hash function as preferred data type. pg.195
//May be source of error if generic datatype is not string.
template<typename K, typename V>
size_t cop4530::HashTable<K, V>::myhash(const K &k) {


    unsigned int hashval = 19;

    std::string evaluate = std::string(k);

    for(char ch: evaluate)
        hashval = 7 * hashval + ch;

    return hashval % hashsize;
}

// *************************************************************************************
// * Function Name: bool cop4530::HashTable<K, V>::contains(const K &k)               *
// * Description: Determines if the parameter object is within the hashtable          *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description:                                                           *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes:                                                                       *
// *****************************************************************

template<typename K, typename V>
bool cop4530::HashTable<K, V>::contains(const K &k) {
    //see if there are any values in the index value of key.
    int searchindex = myhash(k);
   // if (hashtable[searchindex] == nullptr)
   //     return false;
    auto itr = hashtable[searchindex].begin();
    auto end = hashtable[searchindex].end();

    //traverse the hash index list object for the key value.
    //If found, return true, else if iteration fails, return false.
    while(itr != end){
        if(std::get<0>(*itr++) == k )
            return true;
    }

    return false;
}

// *************************************************************************************
// * Function Name: bool cop4530::HashTable<K, V>::match(const std::pair<K, V> &kv)   *
// * Description: Determines if the parameter pair object is in the hashindex of key  *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description:                                                           *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes:                                                                       *
// *****************************************************************

template<typename K, typename V>
bool cop4530::HashTable<K, V>::match(const std::pair<K, V> &kv) {
    if(contains(std::get<0>(kv))) {
        int searchindex = myhash(std::get<0>(kv));
        auto itr = hashtable[searchindex].begin();
        auto end = hashtable[searchindex].end();
        while (itr != end) {
            if ((std::get<0>(*itr) == std::get<0>(kv)) and (std::get<1>(*itr) == std::get<1>(kv)))
                return true;
            else itr++;
        }
    }
    return false;
}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::insert(const pair<K,V> &kv)      *
// * Description: Inserts the passed pair value into the hashtable                    *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description: key value pair user passes in to be inserted              *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes:                                                                       *
// *****************************************************************
template<typename K, typename V>
bool cop4530::HashTable<K, V>::insert( const std::pair<K, V> &kv) {
    if(match(kv))
    {
        std::cout << "The pair already exist" << std::endl;
        return false;
    }
    // case: if key value is already present then access the list object at hash and scan for / swap for updated pair.
    else if(contains(std::get<0>(kv)))
    {
        int index = myhash(std::get<0>(kv));
        auto itr = hashtable[index].begin();
        auto end = hashtable[index].end();
	bool success = false;
        while(itr != end && !success){
            if(std::get<0>(*itr) == std::get<0>(kv) ) {
                (*itr).first = kv.first;
                (*itr).second = kv.second;
                std::cout << "The key value pair has been updated" << std::endl;
                success =  true;} else itr++;

    } return success;
    }
    //case: if pair is new, then rehash -> pushback into hashtable.
    else{
        if(totalelements == hashsize)
            rehash();
        int index = myhash(std::get<0>(kv));
        hashtable[index].push_back(kv);
        totalelements++;
        return true;
        }
}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::insert(const pair<K,V> &&kv)     *
// * Description: Inserts the passed pair value into the hashtable  (move version)    *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description: key value pair user passes in to be inserted              *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes:                                                                       *
// *****************************************************************

template<typename K, typename V>
bool cop4530::HashTable<K, V>::insert(const std::pair<K, V> &&kv) {
    if(match(kv(0)))
    {
        std::cout << "The pair already exist" << std::endl;
        return false;
    }
    else if(contains(kv(0)))
    {
        int index = myhash(kv(0));
        if (hashtable[index] == nullptr)
            return false;
        auto itr = hashtable[index].begin();
        auto end = hashtable[index].end();

        while(itr != end){
            if(std::get<0>(*itr) == kv ) {
                (*itr).first = kv.first;
                std::string crypt_pass = encrypt(kv.second);
		(*itr).second = crypt_pass;
                std::cout << "The key value pair has been updated" << std::endl;
                return true;}
             else itr++;}
        
    }
    else{
        if(totalelements == hashsize)
            rehash();
        int index = myhash(kv(0));
        hashtable[index].push_back(kv);
        totalelements++;
        return true;
    }
}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::clear()                           *
// * Description: Calls the helper function to clear all entries in hash table.        *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************
template<typename K, typename V>
void cop4530::HashTable<K, V>::clear() {
    makeEmpty();
}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::makeEmpty()                       *
// * Description: Transverse the list vector and clears all elements.                  *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
void cop4530::HashTable<K, V>::makeEmpty() {
    auto itr = hashtable.begin();
    auto end = hashtable.end();
    while(itr != end)
    {
        (*itr).clear();
        itr++;
    }
}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::rehash()                          *
// * Description: Resizes the hash table and assigns all entries to new hash values.   *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
void cop4530::HashTable<K, V>::rehash() {
//determine new capacity
    int newcapacity = hashsize;
    int i = 2;
    while(newcapacity == hashsize)
        newcapacity = prime_below(hashsize * i++ + 1);

//initialize new Hashtable
    HashTable *newHash = new HashTable(newcapacity);
    newHash->hashsize = newcapacity;
//scan old hashtable for all elements.
    int size = hashtable.capacity();

    for( i = 0; i < size; i++)
    {
            auto itr = hashtable[i].begin();
            auto end = hashtable[i].end();

            while(itr != end)
            {
                auto pair = std::make_pair(std::get<0>(*itr), std::get<1>(*itr));
                newHash->insert(pair);
                itr++;
            }

    }

//Assign newly populated hashtable as object hashstable.
    this->hashtable = newHash->hashtable;
    this->hashsize = newHash->hashsize;

}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long cop4530::HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void cop4530::HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

// *************************************************************************************
// * Function Name: bool cop4530::HashTable<K, V>::remove(const K &k)                  *
// * Description: removes pair object that holds passed key value                      *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
bool cop4530::HashTable<K, V>::remove(const K &k) {
    bool success = false;
    if (contains(k)) {
        int searchindex = myhash(k);
        auto itr = hashtable[searchindex].begin();
        auto end = hashtable[searchindex].end();
        while (itr != end) {
            if (std::get<0>(*itr++) == k) { //postfix increment. itr transverses list in hash element for
                                            // pair obj. test if first value is equal. increments itr.
                hashtable[searchindex].erase(--itr);
                totalelements--;
                success =  true;
            }
        } 
    }
   return success;
}

// *************************************************************************************
// * Function Name: void cop4530::HashTable<K, V>::dump()                              *
// * Description: prints all entries of the hash table into the terminal.              *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
void cop4530::HashTable<K, V>::dump() {
    auto itr = hashtable.begin();
    auto end = hashtable.end();
    int count = 0;
    while(itr != end)
    {
        std::cout << "hash [ " + std::to_string(count) + " ]";

        {
            auto list_itr = (*itr).begin();
            auto list_end = (*itr).end();
            while(list_itr != list_end)
            {
                std::cout << " | " << std::get<0>(*list_itr) << " " << std::get<1>(*list_itr) << " |";
                list_itr++;
            }
            std::cout << std::endl;
            count++;
            itr++;

        }
    }


}

// *************************************************************************************
// * Function Name: bool cop4530::HashTable<K, V>::load(const char* filename)         *
// * Description: Loads the hashtable with the data inside the passed file            *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description:                                                           *
// * Date:  03/17/2021                                                                *
// * Author: Deanta Pittman                                                           *
// * Referenes: https://www.cplusplus.com/reference/istream/istream/getline/          *
// *****************************************************************
//
template<typename K, typename V>
bool cop4530::HashTable<K, V>::load(const char *filename) {
    std::fstream myfile(filename, std::fstream::in);
    K key;
    V value;
//each line has key and value pair seperated by white space and /n
    if(myfile)
    {
        while(myfile.good())
        {

            //file format: key" "value\r\n

            getline(myfile,key, ' ');
            getline(myfile,value, '\n');
            std::pair<K,V> storage = std::make_pair(key,value);
            insert(storage);
        }
	return true;;
    } else {std::cout << "Error opening file!"; return false;}
}

// *************************************************************************************
// * Function Name: cop4530::HashTable<K, V>::~HashTable()                             *
// * Description: Default destructor for the hashtable function. Calls the makeempty() *
// *               function to clear vector before deleting. No delete is needed       *
// *                as no memory is explicitly allocated in this class.                *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
cop4530::HashTable<K, V>::~HashTable() {
    makeEmpty();
}

// *************************************************************************************
// * Function Name: size_t cop4530::HashTable<K, V>::getSize()                         *
// * Description: returns the total elements in the hashtable.                         *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description:                                                            *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
size_t cop4530::HashTable<K, V>::getSize() {
    return totalelements;
}

// *************************************************************************************
// * Function Name: bool cop4530::HashTable<K, V>::write_to_file(const char *filename) *
// * Description: dumps the entries of the hashtable to the file passed in the param   *
// *                                                                                   *
// *                                                                                   *
// * Parameter Description: name of the file to store the value of the hashtable       *
// * Date:  03/17/2021                                                                 *
// * Author: Deanta Pittman                                                            *
// * Referenes:                                                                        *
// *****************************************************************

template<typename K, typename V>
bool cop4530::HashTable<K, V>::write_to_file(const char *filename) {

    std::ofstream myfile;
    myfile.open(filename);
    std::string buffer = " ";


    auto itr = hashtable.begin();
    auto end = hashtable.end();
    int count = 0;

    if(myfile.good()){
    while(itr != end)
    {
        myfile << "hash [ " + std::to_string(count) + " ]";

            auto list_itr = (*itr).begin();
            auto list_end = (*itr).end();
            while(list_itr != list_end)
            {
                buffer = std::get<0>(*list_itr) + " " + std::get<1>(*list_itr) + " ";
                myfile << buffer;
                list_itr++;
            }
            buffer = "\n";
            myfile << buffer;
            count++;
            itr++;
    }
} else { std::cout << "Error with file opening"; return false;}

    return true;
    }




















