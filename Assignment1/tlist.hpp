//
// Created by deant on 4/21/2020.
//
#include <iostream>


// *****************************************************************
// * Function Name: TList()                                        *
// * Description:  Constructs a TList object created by initializing      *
// *         head and tail nodes.
// *         Initializes a doubly linked list object.              *
// *                                                               *
// * Variable Description:                                         *
// *                                                               *
// *                                                               *
// *                                                               *
// * Date:  01/23/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes:  David Gaitros Office Hour                         *
// *****************************************************************
template <typename T>
TList<T>::TList()
{
    first = new Node<T>(dummy);
    last = new Node<T>(dummy);

    first->next = last;
    last->prev = first;

    first->prev = nullptr;
    last->next = nullptr;

    size = 0;
}

// *****************************************************************
// * Function Name: TList(T val, int num)                          *
// * Description: Constructor with passed initialization values.   *
// *        
// *         Initializes a doubly linked list object.              *
// *                                                               *
// * Variable Description: T val: The value that will occupy each 
//                         node in the constructed list            *
// *                       int num:                                *
// *                                                               *
// *                                                       .       *
// * Date:  01/23/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes:                                                    *
// *****************************************************************
template <typename T>
TList<T>::TList(T val, int num)
{
    first = new Node<T>(dummy);
    last = new Node<T>(dummy);
    size = 0;
    Node<T>* prevNode= first;
    for(int i = 0; i < num; i++){
 Node<T>* newNode = new Node<T>(val);
 size++;
 prevNode->next = newNode;
 newNode->prev = prevNode;
 newNode->data = val;
 prevNode = newNode;
 }

    prevNode->next = last;
    last->prev = prevNode;
}


// *****************************************************************
// * Function Name: ~TList()                                       *
// * Description:  Default Destructor for the TList object         *
// *                                                               *
// *                                                               *
// * Parameter Description:                                        *
// * Date:  04/25/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes: David Gaitros Office Hour                          *
// *****************************************************************


template <typename T>
TList<T>::~TList()
 {

}

template<typename T>
TList<T>::TList(const TList &L) {

    if (L.first->next == last) {
        TList();
    }
    else {
        first = new Node<T>(dummy);
        last = new Node<T>(dummy);
        size = 0;
        TListIterator<T> itr = L.GetIterator();
        Node<T>* prevCopy = nullptr;
        itr.Previous(); // begins at elements ahead of dummy head
        while(itr.ptr != L.last){
            if(itr.ptr == L.first){
                Node<T>* cpyNode = new Node<T>(itr.GetData());
                size++;
                cpyNode->prev = first;
                first->next = cpyNode;
                prevCopy = cpyNode;
                itr.Next();}
            else{
                Node<T>* cpyNode = new Node<T>(itr.GetData());
                size++;
                cpyNode->prev = prevCopy;
                prevCopy->next = cpyNode;
                prevCopy = cpyNode;
                itr.Next();
            }
            last->prev = prevCopy;
        }
    }

}

// *****************************************************************
// * Function Name: TList& operator=(const TList& L)               *
// * Description:  Default Destructor for the TList object         *
// *                                                               *
// *                                                               *
// * Parameter Description:                                        *
// * Date:  04/25/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes:                                                    *
// *****************************************************************

template<typename T>
TList<T> &TList<T>::operator=(const TList &L) {

    TListIterator<T> itr = L.GetIterator();
    while(itr.HasNext()){
        Node<T>* cpyNode = new Node<T>(itr.GetData());
        if(itr.Previous() == first)
            cpyNode->prev = first;
        else
            cpyNode->prev = (*itr.ptr)->prev;
	itr.Next();
        cpyNode->next = itr->ptr; //Assuming data member ptr remains unchanged and "peeks" ahead.
        //itr.Next();
    }
}
// *****************************************************************************************
// * Function Name: bool TList<T>::TList(TList &&L)                                        *
// * Description:   Move constructor                                                       *
// *                                                                                       *
// *                                                                                       *
// * Parameter Description:                                                                *
// * Date:  04/22/2020                                                                     *
// * Author:   Deanta Pittman                                                              *
// * Referenes: https://stackoverflow.com/questions/46882189/linked-list-move-constructor  *
// *****************************************************************************************


template<typename T>
TList<T>::TList(TList &&L) {
    TListIterator<T> itr = L.GetIterator();
    while (itr.HasNext()) {
        Node<T>* cpyNode = new Node<T>(itr.GetData());
        itr.Previous();
        if (itr.ptr == first)
            cpyNode->prev = first;
        else
            cpyNode->prev = itr.ptr;
         itr.Next();
         itr.Next();
        cpyNode->next = itr.ptr;
    }
}

// *****************************************************************************************
// * Function Name: TList<T> &TList<T>::operator=(TList &&L)                               *
// * Description:   Move constructor standard conventions. See link for explanation.       *
// *                                                                                       *
// *                                                                                       *
// * Parameter Description:                                                                *
// * Date:  04/22/2020                                                                     *
// * Author:   Deanta Pittman                                                              *
// * Referenes: https://stackoverflow.com/questions/46882189/linked-list-move-constructor  *
// *****************************************************************************************

template<typename T>
TList<T> &TList<T>::operator=(TList &&L) {
    TListIterator<T> itr = L.GetIterator();
    first->next = (L.first)->next;
    last->prev = (L.last)->prev;
    size = L.size;

}

// *****************************************************************
// * Function Name: bool TList::IsEmpty()                          *
// * Description:  Returns true if the head structure points to    *
// *               the tail structure. Indicates Empty List        *
// *                                                               *
// * Parameter Description:                                        *
// * Date:  04/22/2020                                             *
// * Author:   Deanta Pittman                                      *
// * Referenes:                                                    *
// *****************************************************************
template <typename T>
bool TList<T>::IsEmpty() const {

    return first->next == last;
}

// *********************************************************************
// * Function Name: void TList<T>::Clear()                             *
// * Description:  Transverse List and deletes all elements before last*
// *            structure. Indicates Empty List                        *
// *                                                                   *
// * Parameter Description:                                            *
// * Date:  04/22/2020                                                 *
// * Author:   Deanta Pittman                                          *
// * Referenes:                                                        *
// *****************************************************************

template<typename T>
void TList<T>::Clear() {
    TListIterator<T> itr = this->GetIterator();
    while(itr.HasNext()){
        Node<T>* temp = itr.ptr;
        itr.Next();
        delete temp;
        size--;
    }

    first->next = last;
    last->prev = first;
    first->prev = nullptr;
    last->next = nullptr;
}




// *****************************************************************
// * Function Name: int TList::GetSize()                           *
// * Description: Returns the total size of the linked list.       *
// *              int count is incremented after every successful  *
// *              memory allocation of a Node object.              *
// * Date:  04/22/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes:                                                    *
// *****************************************************************
template <typename T>
int TList<T>::GetSize() const{
    return size;
}

// *****************************************************************
// * Function Name: void TList::InsertFront(const T& d)            *
// * Description:  Inserts a node to the front of the list.        *
// *                                                               *
// *                                                               *
// * Parameter Description: const T& d- The abstract data type to  *
// *                        be inserted into the list              *
// *                                                               *
// *                       - Copies passed record into node.       *
// * Date:  04/22/2020                                             *
// * Author:   Deanta Pittman                                      *
// * Referenes:                                                    *
// *****************************************************************
template <typename T>
void TList<T>::InsertFront(const T& d) {
    //Add empty test to cover edge case.
Node<T>* newNode = new Node<T>(d); // Initializes memory for new node in list.


Node<T>* index1 = first->next;

newNode->prev = first; // Sets the prev pointer to the head node
newNode->next = index1; //next pointer points to node that was originally following head.
index1->prev = newNode; // Sets the pointer that followed head previous pointer to newNode

	first->next = newNode; // declares the newNode as new leading node in linked list.

size++;
// Note, first acts as a dummy head. first element is front->next
}
// *****************************************************************
// * Function Name: void TList::InsertBack(const T& d)             *
// * Description:  Inserts a node to the back of the list.         *
// *                                                               *
// *                                                               *
// * Parameter Description: const T& d- The abstract data type to  *
// *                        be inserted into the list              *
// *                                                               *
// * Date:  04/22/2020                                             *
// * Author:   Deanta Pittman                                      *
// * Referenes:                                                    *
// *****************************************************************
template <typename T>
void TList<T>::InsertBack(const T& d) {
    Node<T>* newNode = new Node<T>(d); // Initializes memory for new node in list.


    Node<T>* index_NminusOne = last->prev;

    newNode->prev = index_NminusOne; //next pointer points to node that was originally following head.
    newNode->next = last; // Sets the pointer that followed head previous pointer to newNode
    index_NminusOne->next = newNode;

    last->prev = newNode;
    size++;
}

// *****************************************************************
// * Function Name: void TList::RemoveFront()                      *
// * Description:  Inserts a node to the back of the list.         *
// *                                                               *
// *                                                               *
// * Parameter Description:                                        *
// *                                                               *
// *                                                               *
// * Date:  04/22/2020                                             *
// * Author:   Deanta Pittman                                      *
// * Referenes:                                                    *
// *****************************************************************
template<typename T>
void TList<T>::RemoveFront() {
    Node<T>* index1 = first->next;
    Node<T>* index2 = index1->next;

    first->next = index2;
    index2->prev = first;
    index1->next = index1->prev = nullptr;
    delete index1;

    size--;

}

// *****************************************************************
// * Function Name: void TList::RemoveBack()                      *
// * Description:  Inserts a node to the back of the list.         *
// *                                                               *
// *                                                               *
// * Parameter Description:                                        *
// *                                                               *
// *                                                               *
// * Date:  04/22/2020                                             *
// * Author:   Deanta Pittman                                      *
// * Referenes:                                                    *
// *****************************************************************

template<typename T>
void TList<T>::RemoveBack() {
 Node<T>* index_end = last->prev;
 Node<T>* index_beforeend = index_end->prev;

 last->prev = index_beforeend;
 index_beforeend->next = last;
 index_end->next = index_end->prev = nullptr;
 delete index_end;

 size--;
}

// *****************************************************************
// * Function Name: const TListIterator<T>::GetIterator()   ;       *
// * Description: initializes a pointer to Iterator object pointing *
// *              to the first element on this list                 *
// *                                                                *
// *                                                                *
// * Date:  04/22/2020                                              *
// * Author: Deanta Pittman                                         *
// * Referenes:                                                     *
// *****************************************************************

template <typename T>
TListIterator<T> TList<T>::GetIterator() const {
    TListIterator<T>* iterator = new TListIterator<T>;
    
    iterator->ptr = first->next;

    return *iterator;
}

// *****************************************************************
// * Function Name: const TListIterator<T>::GetIteratorEnd()       *
// * Description:  initializes a pointer to Iterator object pointing*
// *                to the first element on this list              *
// *                                                               *
// * Date:  04/22/2020                                             *
// * Author: Deanta Pittman                                        *
// * Referenes:                                                    *
// *****************************************************************

template <typename T>
TListIterator<T> TList<T>::GetIteratorEnd() const {
    TListIterator<T>* iterator = new TListIterator<T>; //Initialize memory for an iterator object
    
    iterator->ptr = last->prev; //Assign the iterator at the last element on the list of function call.
    
    return iterator; // Assign it to lhs. ie itr = L1.GetIteratorEnd();
}

// *************************************************************************
// * Function Name: void TList<T>::Insert(TListIterator<T> pos, const T& d)*
// * Description:  Initializes an node object and injects itself into the  *                                       .               *
// *               list before the node pt'ed to by pos                    *
// * Date:  04/22/2020                                                     *
// * Author: Deanta Pittman                                                *
// * Referenes:                                                            *
// **************************************************************************
template <typename T>
void TList<T>::Insert(TListIterator<T> pos, const T& d) {
   
    Node<T>* posNode = pos.ptr; //initialize an internal node pointer equal to the address of the node the passed iterator is pointing to.
    if (posNode==first->next)
    {
        this->InsertFront(d);
    } else {
        Node<T> *prevNode = posNode->prev; //points to a node (index-1) of the linked list.

        Node<T>* inject = new Node<T>(
                dummy); //initialized memory for size T Node that will emulate an new entry of the linked list.
        inject->data = d; //Store that passed data value into the initalized Node obejct.

        prevNode->next = inject;// VISUALIZATION: prevNode -> inject <- indexNode
        posNode->prev = inject;
        inject->prev = prevNode; //prevNode <- inject -> indexNode
        inject->next = posNode;

        size++;
    }
     
}
// **********************************************************************************
// * Function Name: void TList<T>::Remove(TListIterator<T> pos)                     *
// * Description:  There are no boundary checks for the iterator.                   *
// * It is assumed the user will not call this command with the iterator positioned.*
// *      at the head and tail nodes. Use Insert|Remove/FRONT()/BACK()              *
// * Date:  04/22/2020                                                              *
// * Author: Deanta Pittman                                                         *
// * Referenes:                                                                     *
// **********************************************************************************
template <typename T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos) {



    Node<T>* posNode = pos.ptr; //initialize an internal node pointer equal to the address of the node the passed iterator is pointing to.
    if (!pos.HasPrevious())
    {
        this->RemoveFront();
    } else if (!pos.HasNext()){

        this->RemoveBack();
    }
    else{
        Node<T> *prevNode = posNode->prev; //points to a node (index-1) of the linked list.
        Node<T> *nextNode = posNode->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        posNode->prev = posNode->next = nullptr;
        delete posNode;

        size--;
    }
}

// ***********************************************************************************
// * Function Name: void TList<T>::Print(std::ostream& os, char delim = ' ') const   *
// * Description: Passes streamable data into a ostream object to print into terminal*
// *                                                                                 *
// * Date:  04/22/2020                                                               *
// * Author: Deanta Pittman                                                          *
// * Referenes:                                                                      *
// * Note: The function in the header file is 'Print', however on the driver         *
// * the behavior is referenced by 'PrintList'                                       *
// ***********************************************************************************
template <typename T>
void TList<T>::Print(std::ostream& os, char delim) const {
    TListIterator<T> itr = this->GetIterator();

    while(itr.HasNext()){
        T const data = itr.GetData();
        os << data;
        os << delim;
        itr.Next();
    }
}

template<typename T>
T &TList<T>::GetFirst() const {
    return first->next->data;
}

template<typename T>
T &TList<T>::GetLast() const {
    return last->prev->data;
}


template<typename T>
TList<T> operator+(const TList<T> &t1, const TList<T> &t2) {

    static TList<T>* t3 = new TList<T>; //Moves object to permanent memory
    t3->Clear();
    TListIterator<T> itr = t1.GetIterator();
    while(itr.HasNext()) {
        if(itr.GetData() != 0)
            t3->InsertBack(itr.GetData());
        itr.Next();
    }
    //itr is currently at tail of t1
    TListIterator<T> itr2 = t2.GetIterator();

    while(itr2.HasNext()) {
        t3->InsertBack(itr2.GetData());
        itr2.Next();

    }
    return *t3;
}

    template<typename T>
    TListIterator<T>::TListIterator() {
    ptr = nullptr;
}

    template<typename T>
    bool TListIterator<T>::HasNext() const {
        return (ptr->next != nullptr );

    }
    template<typename T>
    bool TListIterator<T>::HasPrevious() const {
        return (ptr->prev != nullptr);
    }

template<typename T>
TListIterator<T> TListIterator<T>::Previous(){
        if (ptr->prev != nullptr)
            ptr = ptr->prev;
    }

template<typename T>
TListIterator<T> TListIterator<T>::Next() {
        if (this->HasNext())
            ptr = ptr->next;
    }
    template<typename T>
    T &TListIterator<T>::GetData() const {
        return this->ptr->data; //Bug Fix: Segmentation Error. Cause: extracted and returned the data in a local var
    }

