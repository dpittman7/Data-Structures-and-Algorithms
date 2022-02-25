#include <vector>
#include <utility>


namespace cop4530 {


    template<typename T>
    class Stack {
    public:

        // constructor, destructor, copy constructor
        Stack(); // default zero parameter constructor
        ~Stack(); // destructor
        Stack(const Stack &rhs);   // copy constructor
        const Stack &operator=(const Stack &rhs); // copy assignment operator
        Stack(Stack &&rhs) {
            v = std::move(rhs.v);
            vtop = &(v[v.size() - 1]);
            rhs.vtop = nullptr;
            vsize = v.size();
            rhs.vsize = 0;
        };       // move constructor
        Stack &operator=(Stack &&rhs) {
            v = std::move(rhs->v);
            vtop = rhs->top;
            vsize = v.size();
        }; // move assignment operator



        // member functions
        int size() const;       // number of elements
        bool empty() const;     // check if list is empty
        void clear();           // delete all elements

        void push(T &val); // adds x to the stack. copy version.
        void push(T &&val) {
            v.push_back(std::move(val));
            vtop = &(v[(++vsize - 1)]);
        };     // adds x to the stack. move version.
        void pop();               // removes and discards the most recently added element

        T &top(); //returns a reference to the most recently added element.
         const T &top_c(); //accessor that returns most recently added element of the stack

        void print(std::ostream &os, char ofc = ' ') const; //prints element of stack into os.
        //oldest element is printed first.

        // non-member functions
        template<typename X>
        friend std::ostream &operator<<(std::ostream &os, const Stack<X> &a); //invokes print method to print Stack
        template<typename X>
        friend bool operator==(const Stack<X> &, const Stack<X> &); //returns true if the two Stacks have same elements in order
        template<typename X>
        friend bool operator!=(const Stack<X> &, const Stack<X> &); // Opposite of !=
        template<typename X>
        friend bool operator<=(const Stack<X> & a, const Stack<X> &b); //returns true if every element in Stack a is smaller than
        //elements in corresponding element in Stack b



    private:
        std::vector<T> v;
        int vsize = 0;// number of elements
        T *vtop = nullptr; // pointer to top element.
    };


#include "Stack.hpp"


// end of namespace 4530

