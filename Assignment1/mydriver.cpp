#include <iostream>
#include <string>

#include "tlist.h"

using namespace std;

template <typename T> 
void PrintList(const TList<T>& L, string label)
{
   cout << label << " size is: " << L.GetSize() << "\n"
        << label << " = "; 
   L.Print(cout);
   cout << "\n\n";
}

int main()
{
   TList<int> L1;		// integer list

   for (int i = 0; i < 10; i++)
    L1.InsertBack(i*2);

   PrintList(L1, "L1");
   cout << "testing insert front/back" << endl;

   L1.InsertFront(20);
    L1.InsertBack(100);
    L1.InsertFront(30);
    L1.InsertBack(110);
    L1.InsertFront(40);
    L1.InsertBack(120);

    PrintList(L1, "L1");

    cout << "testing remove front/back" <<endl;

    L1.RemoveFront();
    L1.RemoveBack();
    L1.RemoveFront();
    L1.RemoveBack();
    L1.RemoveFront();
    L1.RemoveBack();

    PrintList(L1, "L1");

    cout << "testing iterator based insert/remove" << endl;

    TList<char> T2;
    TListIterator<char> itr_c = T2.GetIterator();

    T2.InsertFront('O');
    T2.Insert(itr_c,'T');
    if(itr_c.HasNext())
        itr_c.Next();
    T2.Insert(itr_c,'T');
    T2.Insert(itr_c, 'P');
    T2.Insert(itr_c, 'P');
    cout << "inserted two 'T' before the O" << endl;
    PrintList(T2, "L2");

    cout << " Now Removing some elements from said lsit" << endl;//Skipped up once ahead;
    T2.Remove(itr_c);
    itr_c.Previous();
    itr_c.Previous();
    T2.Remove(itr_c);


    PrintList(T2, "L2");



    T2.InsertFront('R');
    T2.InsertFront('R');
    T2.InsertFront('R');
    cout << T2.GetSize();
    T2.Remove(itr_c);
   //tr_c.Next(); itr points to tail
    T2.Remove(itr_c);

   // try an iterator, and some middle inserts/deletes
   cout << "Testing some inserts with an iterator\n\n";

   TListIterator<int> itr = L1.GetIterator();
   L1.Insert(itr, 999);
   itr.Next();
   itr.Next();// advance two spots
   L1.Insert(itr, 888);
   itr.Next();
   itr.Next();
   itr.Next();// advance three spots
   L1.Insert(itr, 777);

   PrintList(L1, "L1");

   cout << "Testing some removes (with iterator)\n\n";

   itr.Next();   
   itr.Next();// advance two spots
   L1.Remove(itr);// delete current item
   PrintList(L1, "L1");

   for (int i = 0; i < 5; i++)
      itr.Previous();// back 5 spots

   L1.Remove(itr);// delete current item
   PrintList(L1, "L1");
   
   // building another list

   TList<int> L2;
   for (int i = 0; i < 10; i++)
      L2.InsertBack(i * 3 + 1);

   PrintList(L2, "L2");

   // Testing + overload:

   TList<int> L3 = L1 + TList<int>(100, 7);

   TList<int> L4;
   L4 = L2 + L1;

   PrintList(L3, "L3");
   PrintList(L4, "L4");
   
    cout << "Testing clear function" << endl;


    PrintList(L2, "L2");
    L2.Clear();
    PrintList(L2, "L2 Deleted");
    cout << "Checking if its clear L2: " << L2.IsEmpty() << endl;
    cout << "Repopulating L2" << endl;
    L2.InsertFront(10);
    L2.InsertFront(11);
    PrintList(L2, "L2 Repopulated");

    cout << "Getting first element item from L2: " << L2.GetFirst() << endl;
    cout << "Getting last element item from L2: " << L2.GetLast() << endl;


}

