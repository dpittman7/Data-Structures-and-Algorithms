#include "List.h"


 // -------- CONST ITERATOR FUNCTIONS START -------------------------


 template<typename T>
 List<T>::const_iterator::const_iterator() {
    current = nullptr;
 }

 template<typename T>
 typename List<T>::const_iterator &List<T>::const_iterator::operator--() {
     this->current = this->current->prev;
     return *this;
 }

 template<typename T>
 T &List<T>::const_iterator::retrieve() const {
     return this->current->data;
 }

 template<typename T>
 bool List<T>::const_iterator::operator!=(const List::const_iterator &rhs) const {
     return (this->current != rhs.current);
 }

 template<typename T>
 const T &List<T>::const_iterator::operator*() const {
     return this->retrieve();
 }

 template<typename T>
 typename List<T>::const_iterator &List<T>::const_iterator::operator++() {
     this->current = this->current->next;
     return *this;
 }

 template<typename T>
 typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
     const_iterator old = *this;
     ++(*this);
     return old;
 }

 template<typename T>
 typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
     const_iterator old = *this;
     --(*this);
     return old;
 }

 template<typename T>
 bool List<T>::const_iterator::operator==(const List::const_iterator &rhs) const {
     return (this->current == rhs.current);
 }

 template<typename T>
 List<T>::const_iterator::const_iterator(List::Node *p) {
    this->current = p;
 }


 // ---------------- Const ITERATOR FUNCTION END -------------------
 //---------------- ITERATORS FUNCTIONS START ----------------------

 template<typename T>
 List<T>::iterator::iterator() {

 }


 template<typename T>
 T &List<T>::iterator::operator*() {
     return const_iterator::retrieve();
 }

 template<typename T>
 const T &List<T>::iterator::operator*() const {
     return const_iterator::retrieve();
 }

 template<typename T>
 typename List<T>::iterator &List<T>::iterator::operator++() {
     this->current = this->current->next;
     return *this;
 }

 template<typename T>
 typename List<T>::iterator List<T>::iterator::operator++(int) {
     iterator old = *this;
     ++(*this);
     return old;
 }

 template<typename T>
 typename List<T>::iterator &List<T>::iterator::operator--() {
     this->current = this->current->prev;
     return *this;
 }

 template<typename T>
 typename List<T>::iterator List<T>::iterator::operator--(int) {
     iterator old = *this;
     --(*this);
     return old;
 }

 template<typename T>
 List<T>::iterator::iterator(List::Node *p):const_iterator(p) {
     this->current = p;
 }

 // ----------------List Template Functions Start ------------------



 template<typename T>
 List<T>::List() {
    init();
 }

 template<typename T>
 List<T>::List(const List &rhs) {
    init();
    if(!rhs.empty()) {
        int copy_range = rhs.size();
        iterator itr = rhs.begin();
        for (int i = 0; i < copy_range; i++)
            this->push_back(*(itr)++); //Gets the element pointed to by the iterator.
    }
 }

 template<typename T>
 List<T>::List(List &&rhs) {
     init();
     if(!rhs.empty()) {
         int move_range = rhs.size();
         iterator itr = rhs.begin();
         for (int i = 0; i < move_range; i++)
             this->push_back((*itr)++); //Gets the element pointed to by the iterator.
     }

 }

 template<typename T>
 List<T>::List(std::initializer_list<T> iList) {
     init();
     auto itr_begin = iList.begin();
     auto itr_end = iList.end();

     while(itr_begin != itr_end){
         this->push_back(*itr_begin++);
     }

 }

 template<typename T>
 List<T>::List(int num, const T &val) {
    init();
    for(int i = 0; i < num; i++){
        this->push_back(val);
    }
 }

 template<typename T>
 List<T>::List(List::const_iterator start, List::const_iterator end) {

    init();
    while(start != end){
        this->push_back(*start);
        start++;
    }


 }

 template<typename T>
 List<T>::~List() {
     this->clear();
 }



 // ************************************************************************************
 // * Function Name: const typename List<T>::List& List<T>::operator=(const List &rhs)      *              *
 // * Description:  Assignment operator the the List object. Step by step anaysis in funct.                            *
 // *                                                                                  *
 // *                                                                                  *
 // * Parameter Description:                                                           *
 // * Date:  04/25/2020                                             *
 // * Author: Deanta Pittman                                        *
 // * Referenes:https://stackoverflow.com/questions/9187194/template-class-in-c-trouble-writing-begin-for-linked-list                                                    *
 // *****************************************************************


 template<typename T>
 const typename List<T>::List& List<T>::operator=(const List &rhs) {
     iterator ritr = rhs.front();
     iterator itr = begin();

     if(this != &rhs)
     {
         clear();
         for(; ritr != NULL; ritr++, itr++)
             insert(ritr.retrieve(), itr);
     }
     return *this;
 }

 template<typename T>
 typename List<T>::List& List<T>::operator=(List &&rhs) {
     iterator ritr = rhs.front();
     iterator itr = begin();

     if(this != &rhs)
     {
         clear();
         for(; ritr != NULL; ritr++, itr++)
             insert(ritr.retrieve(), itr);
     }
     return *this;
 }

 template<typename T>
 typename List<T>::List& List<T>::operator=(std::initializer_list<T> iList) {
     auto ilist = iList.begin();

     clear();
     for(; ilist != iList.end(); ilist++)
     {
         this->push_back(*ilist);
     }

     return *this;
 }
 template<typename T>
 int List<T>::size() const {
     return this->theSize;
 }

 template<typename T>
 bool List<T>::empty() const {
     return theSize == 0;
 }

 // ************************************************************************************
// * Function Name: void List<T>::clear()     *              *
// * Description:  Assignment operator the the List object. Step by step anaysis in funct.                            *
// *                                                                                  *
// *                                                                                  *
// * Parameter Description:                                                           *
// * Date:  04/25/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes:https://stackoverflow.com/questions/9187194/template-class-in-c-trouble-writing-begin-for-linked-list                                                    *
// *****************************************************************
 template<typename T>
 void List<T>::clear() {

     while(!empty())
         erase(begin());
 }



 template<typename T>
 void List<T>::reverse() {

    auto itr = begin();
    auto itr2 = --end();
    int range = theSize / 2;
     for(int i = 0; i < range; i++) // loop: i to size/2. n/2 time complexity
     {
         T frontdata = itr.retrieve(); // Assignment + return = 2 time complexity
         T backdata = itr2.retrieve(); // Assignment + return = 2 time complexity

         itr.current->data = backdata; //Assignment = 1 time complexity
         itr2.current->data = frontdata; // Assignment = 1 time complexity

         itr++; //Assignment + return = 2 time complexity
         itr2--; // Assignment + return = 2 time complexity
     }
}

 template<typename T>
 void List<T>::push_front(const T &val) {

     if(head != nullptr) {
         Node *insert = new Node;
         Node *next = head;

         insert->next = next;
         next->prev = insert;
         insert->data = val;
         head = insert;

     } else {
         Node *insert = new Node;
         head = insert;
         head->next = tail;
         head->data = val;
         tail->prev = head;
     }
     theSize++;

 }

 template<typename T>
 void List<T>::push_front(T &&val) {

     if(!empty()) {
         Node *insert = new Node;

         head->prev = insert;
         insert->next = head;
         insert->data = val;
         head = insert;
         theSize++;
     }
     else {
         Node *insert = new Node;
         head = insert;
         insert->data = val;
         insert->next = tail;
         tail->prev = insert;
         theSize++;
     }
 }

 template<typename T>
 void List<T>::push_back(const T &val) {

    if(!empty()){
        Node *insert = new Node;
        Node *prev = tail->prev;

        tail->prev = insert;
        insert->next = tail;
        insert->prev = prev;
        prev->next = insert;
        insert->data = val;
        theSize++;
    } else {
        Node *insert = new Node;
        head = insert;
        insert->data = val;
        insert->next = tail;
        tail->prev = insert;
        theSize++;
    }
 }

 template<typename T>
 void List<T>::push_back(T &&val) {
     if(!empty()){
         Node *insert = new Node;
         Node *prev = tail->prev;

         tail->prev = insert;
         insert->next = tail;
         insert->prev = prev;
         prev->next = insert;
         insert->data = val;
         theSize++;
     } else {
         Node *insert = new Node;
         head = insert;
         insert->data = val;
         insert->next = tail;
         tail->prev = insert;
         theSize++;
     }

 }

 template<typename T>
 void List<T>::pop_front() {

    auto itr = begin();
    erase(itr);
 }

 template<typename T>
 void List<T>::pop_back() {

     auto itr = end();
     erase(--itr);
 }

 template<typename T>
 template<typename PREDICATE>
 void List<T>::remove_if(PREDICATE pred) {
    if(!empty()) {
        auto itr = begin();
        auto itre = end();
        while(itr != itre) {
            if (pred(*itr))
                itr = erase(itr);
            else
                itr++;
        }
    }

 }

 template<typename T>
 void List<T>::remove(const T &val) {
     if(!empty()) {
         auto itr = begin();
         auto itre = end();
         while(itr != itre) {
             if (*itr == val)
                 itr = erase(itr);
             else
                 itr++;
         }
     }
 }


 template<typename T>
 T &List<T>::front() {
    if(!empty())
        return head->data;
 }

 template<typename T>
 const T &List<T>::front() const {
     if(!empty())
         return head->data;
 }

 template<typename T>
 T &List<T>::back() {
     if(!empty())
         return tail->prev->data;
 }

 template<typename T>
 const T &List<T>::back() const {
     if(!empty())
         return tail->prev->data;
 }


 template<typename T>
 typename List<T>::iterator List<T>::begin() {

    auto itr = List<T>::iterator();
    if(!empty())
        itr.current = head;
    return itr;

 }

 template<typename T>
 typename List<T>::const_iterator List<T>::begin() const {
     auto itr = List<T>::const_iterator();
     if(!empty())
         itr.current = head;
     return itr;
 }

 template<typename T>
 typename List<T>::iterator List<T>::end() {

     auto itr = List<T>::iterator();
     itr.current = tail;
     return itr;
 }

 template<typename T>
 typename List<T>::const_iterator List<T>::end() const {
     auto itr = List<T>::const_iterator();
     itr.current = tail;
     return itr;
 }

 template<typename T>
 typename List<T>::iterator List<T>::insert(List::iterator itr, const T &val) {
     if(itr.current != nullptr) {
         if (itr.current != head) {
             Node *next_index = itr.current->next;
             Node *current = itr.current;
             Node *insert = new Node;

             insert->prev = current;
             insert->next = next_index;
             current->next = insert;
             next_index->prev = insert;

             insert->data = val;

         } else {
             Node *insert = new Node;
             head = insert;
             insert->data = val;
             insert->next = tail;
         }
         theSize++;
     }
     return itr;
 }

 template<typename T>
 typename List<T>::iterator List<T>::insert(List::iterator itr, T &&val) {
     if(itr.current != nullptr) {
         if (itr.current != head) {
             Node *next_index = itr.current->next;
             Node *current = itr.current;
             Node *insert = new Node;

             insert->prev = current;
             insert->next = next_index;
             current->next = insert;
             next_index->prev = insert;

             insert->data = val;

         } else {
             Node *insert = new Node;
             head = insert;
             insert->data = val;
             insert->next = tail;
         }
         theSize++;
     }
     return itr;
 }


 template<typename T>
 typename List<T>::iterator List<T>::erase(List::iterator itr) {
    if(itr.current != nullptr) {
        if (itr.current != head) {

            Node *prev_index = itr.current->prev;
            Node *next_index = itr.current->next;
            Node *deletion = itr.current;

            prev_index->next = next_index;
            next_index->prev = prev_index;

            delete deletion;
            itr.current = next_index;
        } else {
            Node *oldhead = head;
            Node *next = head->next;
            next->prev = nullptr;
            if (next != tail)
                head = next;
            else
                head = nullptr;
            delete oldhead;
            itr.current = head;
        }

        theSize--;

    }

    return itr;
 }

 template<typename T>
 typename List<T>::iterator List<T>::erase(List::iterator start, List::iterator end) {
     while(start != end)
        start = erase(start);
     return start;
 }

 template<typename T>
 void List<T>::init() {
     theSize = 0;           // number of elements
     head = nullptr;           // head node
     tail = new Node;

 }

 template<typename T>
 void List<T>::print(std::ostream &os, char ofc) const {
     {
         if(!this->empty())
         {
             typename List<T>::const_iterator::const_iterator begin;
             for(begin = this->begin(); begin != this->end() ; begin++)
             {
                 os << *begin << ofc;
             }
         }
         else
         {
             os << "---";

         }

 }

     // overloading comparison operators





