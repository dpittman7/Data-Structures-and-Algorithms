


const int ALLOCATION_AMOUNT = 32;
    // ***************************************************************************************
    // * Function Name: Stack<T>::Stack()                                                    *
    // * Description: Generic Constructor. Allocates 32 * T bytes of memory for the          *
    // *                          internal vector obj. All other private data members        *
    // *                          default initialization is in header.                       *
    // * Parameter Description:                                                              *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
    template<typename T>
    Stack<T>::Stack() {
		v.reserve(ALLOCATION_AMOUNT);

    }
    // ***************************************************************************************
    // * Function Name: Stack<T>::~Stack()                                                   *
    // * Description: Generic Destructor. Clears the vector object before deleting obj       *
    // *                                                                                     *
    // * Parameter Description:                                                              *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    Stack<T>::~Stack() {
		v.clear();

    }

    // ***************************************************************************************
    // * Function Name: Stack<T>::Stack(const Stack& rhs)           *
    // * Description: Copy Constructor. Assigns the properties of the rhs Stack to call stack   *
    // *                                                                                     *
    // * Parameter Description: Stack<T>&rhs: The stack object that the lsh obj is mimicing  *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    Stack<T>::Stack(const Stack& rhs) {
		if(!rhs.empty()){
			v = rhs.v;
			vtop = &(v[v.size()-1]);
        }
		else
			Stack();
		 
    }
    // ***************************************************************************************
    // * Function Name: const Stack <T> & Stack<T>::operator=(const Stack <T>&rhs)           *
    // * Description: Copy operator. Assigns the properties of the rhs Stack to call stack   *
    // *                                                                                     *
    // * Parameter Description: Stack<T>&rhs: The stack object that the lsh obj is mimicing  *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    const Stack <T> & Stack<T>::operator=(const Stack <T>&rhs) {
		
		v = rhs.v;
		vtop = &(v[v.size()-1]);
		vsize = v.size();

    }

    // ***************************************************************************************
    // * Function Name: int Stack<T>::size() const                                           *
    // * Description: Accessor of private data member size.                                  *
    // *                                                                                     *
    // * Parameter Description:                                                              *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    int Stack<T>::size() const {
		
		return vsize;
    }
	
	template<typename T>
    bool Stack<T>::empty() const {
		return vsize == 0; //ternary operator
    }
    // ***************************************************************************************
    // * Function Name: void Stack<T>::clear()                                               *
    // * Description: Inserts element *
    // *                                                                                     *
    // * Parameter Description:                                                              *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    void Stack<T>::clear() {
		
		v.clear();
        vtop = nullptr;
    }
    // ***************************************************************************************
    // * Function Name: void Stack<T>::push()                                                *
    // * Description: Inserts element at end of Stack. Increment size. Reassign top reference*
    // *                                                                                     *
    // * Parameter Description: T &val: Accepts data type of Stack initilization.            *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    void Stack<T>::push(T &val) {
		
		v.push_back(val);
		vsize++;
		vtop = &(v[v.size()-1]); // updates size variable and prevent segmentation error by
		                      // reverting size to index notation by -1.
    }

    // ***************************************************************************************
    // * Function Name: void Stack<T>::pop()                                                 *
    // * Description: Deletes the last element. Resize Stack Obj. Assign new reference to top*
    // *                                                                                     *
    // * Parameter Description:                                                              *
    // *                                                                                     *
    // *                                                                                     *
    // * Date:  02/20/2021                                                                   *
    // * Author: Deanta Pittman                                                              *
    // * Referenes:                                                                          *
    // ***************************************************************************************
	template<typename T>
    void Stack<T>::pop() {
		
		this->v.pop_back();
		vsize--;
		if(vsize != 0)
		    vtop = &(v[v.size()-1]);
        else
            vtop = &v[0];
    }
    // *************************************************************************************
    // * Function Name: T& Stack<T>::top_c()                                               *
    // * Description: Returns a reference to the last element/ the top of the stack        *
    // *                                                                                   *
    // * Parameter Description:                                                            *
    // *                                                                                   *
    // *                                                                                   *
    // * Date:  02/20/2021                                                                 *
    // * Author: Deanta Pittman                                                            *
    // * Referenes:                                                                        *
    // *************************************************************************************
	template<typename T>
    T& Stack<T>::top() {
        return *vtop;

    }
    // *************************************************************************************
    // * Function Name: const T& Stack<T>::top_c()                                         *
    // * Description: Returns a const reference to the last element/ the top of the stack  *
    // *                                                                                   *
    // * Parameter Description:                                                            *
    // *                                                                                   *
    // *                                                                                   *
    // * Date:  02/20/2021                                                                 *
    // * Author: Deanta Pittman                                                            *
    // * Referenes:                                                                        *
    // *************************************************************************************
	template<typename T>
    const T& Stack<T>::top_c()  {
	T* const temp =  vtop;
	return *temp;
		
    }

    // *************************************************************************************
    // * Function Name: void Stack<T>::print(std::ostream&os, char ofc) const              *
    // * Description: iterates through Stack and passes dereference to os.                 *
    // *                                                                                   *
    // * Parameter Description: ostream os: ostream object to stream data to terminal      *
    // *            char ofc: delimiter that will seperate each printed element.           *
    // *                                                                                   *
    // * Date:  02/20/2021                                                                 *
    // * Author: Deanta Pittman                                                            *
    // * Referenes:                                                                        *
    // *************************************************************************************
	template<typename T>
    void Stack<T>::print(std::ostream&os, char ofc) const {
		
		if(!v.empty()){
		auto from = v.begin();
		auto to = v.end();
		
		for(auto itr = from; itr != to; itr++)
			os << *itr << ofc;
		}
		else
			os << "BAKA, THE STACK IS EMPTY" << ofc;
		
    }
    // *************************************************************************************
    // * Function Name: std::ostream& operator<< (std::ostream& os, const Stack<T>& a)     *
    // * Description: Overloads the << operator to initaite the print function fot a.      *
    // *                                                                                   *
    // * Parameter Description: ostream os: ostream object to stream data to terminal      *
    // *            Stack<T> a: the stack whose elements will be streamed into the terminal*
    // *                                                                                   *
    // * Date:  02/20/2021                                                                 *
    // * Author: Deanta Pittman                                                            *
    // * Referenes:https://web.mst.edu/~nmjxv3/articles/templates.html                     *
    // *************************************************************************************
template<typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
    if(a.empty())
        os << "BAKA, THE STACK IS EMPTY" << ' ';
    else
        a.print(os, ' ');

    return os;
}

    // ************************************************************************************
    // * Function Name: bool operator==(const Stack<T>& a, const Stack<T> &b)             *
    // * Description: Overloads the == operator to test the equality of Stack a and b     *
    // *                                                                                  *
    // * Parameter Description:                                                           *
    // * Date:  02/20/2021                                                                *
    // * Author: Deanta Pittman                                                           *
    // * Referenes:https://web.mst.edu/~nmjxv3/articles/templates.html                    *
    // ************************************************************************************
template<typename T>
bool operator==(const Stack<T>& a, const Stack<T> &b) {

    return a.v == b.v;

}
    // ************************************************************************************
    // * Function Name: bool operator!=(const Stack<T>& a, const Stack<T> &b)             *
    // * Description: Overloads the == operator to test the inequality of Stack a and b   *
    // *                                                                                  *
    // * Parameter Description:                                                           *
    // * Date:  02/20/2021                                                                *
    // * Author: Deanta Pittman                                                           *
    // * Referenes:https://web.mst.edu/~nmjxv3/articles/templates.html                    *
    // ************************************************************************************
template<typename T>
bool operator!=(const Stack<T>& a, const Stack<T> &b) {

    return a.v != b.v;

}
    // ************************************************************************************
    // * Function Name: bool operator<=(const Stack<T>& a, const Stack<T> &b)             *
    // * Description: Overloads the <= operator to compare the size of Stack A and B      *
    // *                                                                                  *
    // * Parameter Description:                                                           *
    // * Date:  02/20/2021                                                                *
    // * Author: Deanta Pittman                                                           *
    // * Referenes:https://web.mst.edu/~nmjxv3/articles/templates.html                    *
    // ************************************************************************************
template<typename T>
bool operator<=(const Stack<T>& a, const Stack<T> &b) {

    return a.v <= b.v;
}


}
	
	
