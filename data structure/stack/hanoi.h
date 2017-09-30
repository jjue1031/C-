/*
 Lingjue Xie
 PIC 10B Summer 2017
 ID: 904599062
 8/12/2017
 The program is to implement a Stack class and use it to solve the Hanoi puzzle
 */

#ifndef hanoi_h
#define hanoi_h

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <vector>
#include <string>

using std::cout;
using std::ostream;
using std::setw;
using std::endl;
using std::string;
using std::vector;


// forward declaration
template<typename T>
class StackNode;

template<typename T>
class Stack;

// ---------------------------class StackNode declaration and implementation---------------------------------
template<typename T>
class StackNode{
public:
    friend class Stack<T>;
    
    StackNode(T data): the_data(data), nodeBelow(nullptr){}
    
    
    T get_data() const{
        return the_data;
    }
  
    
private:
    T the_data;
    StackNode* nodeBelow;
};
// --------------------------- end of class StackNode ---------------------------------




// --------------------------- class Stack declaration and implementation ---------------------------------
template<typename T>
class Stack{
public:
    // default constructor
    Stack():top(nullptr),name(""){}
    
    // constructor with two parameter
    Stack(string initial_name, size_t totalNodes=0):name(initial_name),top(nullptr){
        for ( int i = 0 ; i < totalNodes ; i++ )
            this->push(totalNodes - i);
    }
    
    // To avoid repetition of code extract the common parts
    // used in the copy constructor and the = operator
    void deep_copy( const Stack<T>& s ){
        
        // shallow copy stack variable
        this->name = s.name;
        
        Stack<T> temp;
        StackNode<T>* position = s.top;
        // deep copy
        while(position != nullptr){
            temp.push(position->the_data);
            position = position->nodeBelow;
        }
        
        // in order to maintain the order of original stack
        position = temp.top;
        while(position != nullptr){
            this->push(position->the_data);
            position = position->nodeBelow;
        }
    }

    
    // copy construct
    Stack(const Stack<T>& s):top(nullptr),name(""){
        deep_copy(s);
    }
    
    // assignment operator
    Stack& operator=(const Stack& s){
        // Only proceed if not a self-assignment
        if(this != &s){
            // delete existing list
            (*this).~Stack();
            deep_copy(s);
        }
        return *this;
    }
    
    
    // destructor
    // To release memory, continuously pop() until top points to null
    ~Stack(){
        while(top != nullptr){
            pop();
        }
    }
    

    T pop(){
        // only pop when there is element left in the stack
        assert(top != nullptr);
        T oldValue = top->the_data;
        StackNode<T>* ptrToOld = top;
        top = top->nodeBelow;
        // release the memory on heap
        delete ptrToOld;
        return oldValue;
    }
    
    void push(const T& newData){
        // create a new node and populate it with newData
        StackNode<T>* newTop = new StackNode<T>(newData);
        newTop->nodeBelow = top;
        top = newTop;
        return;
    }
    
    size_t size() const{
        int totalNodes = 0;
        StackNode<T>* position = top;
        while(position != nullptr){
            totalNodes++;
            position = position->nodeBelow;
        }
        return totalNodes;
    }
    
    
    T operator[](size_t index) const{
        size_t size = this->size();
        assert(index<size);
        StackNode<T>* position = top;
        for (size_t i=1; i<(size-index); i++){
            position = position->nodeBelow;
        }
        return position->the_data;
    }
    
    
    StackNode<T>* get_top() const{
        return top;
    }
    
    string get_name() const{
        return name;
    }
    
private:
    StackNode<T>* top;
    string name;
};
//------------------------ end of class Stack --------------

// ----------------------- non member function declaration and implementation ------------------
template<typename T>
ostream& operator<<( ostream& out, const Stack<T>& b ){
    out << b.get_name() << ":" << "\t";
    for ( int i = 0 ; i < b.size() ; i++ )
        out << setw(3) << b[i];
    out << endl;
    return out;
}

// printHanoi function is used to print the states of pegs in the recursion
template<typename T>
void printHanoi(const Stack<T>& s1,const Stack<T>& s2,const Stack<T>& s3){
    vector<Stack<T>> v{s1,s2,s3};
    vector<Stack<T>> inOrder(3);
    for(int i=0; i<v.size(); i++){
        if(v[i].get_name()=="top peg") inOrder[0] = v[i];
        else if (v[i].get_name()=="middle peg") inOrder[1] = v[i];
        else inOrder[2] = v[i];
    }
    cout << inOrder[0] << inOrder[1] << inOrder[2] << endl;
}

// hanoi function
template<typename T>
void hanoi( Stack<T>& source, Stack<T>& temp, Stack<T>& target, int depth, ostream& out){
    if ( depth == 1 ) {
        
        out << "Moving " << source.get_top()->get_data() << " from " << source.get_name() << " to "
        << target.get_name() <<". "<<endl;
        
        // move the remaining element to the target
        target.push( source[ source.size()-1 ] );
        source.pop();
        
        // print two pegs states
        printHanoi(source, temp, target);
        return;
        
    }else{
        
        // move the top (depth - 1) pile to the temporary peg
        hanoi( source, target, temp , depth - 1, out );
        
        out << "Moving " << source.get_top()->get_data() << " from " << source.get_name() << " to "
        << target.get_name() <<". "<<endl;
        
        // move the remaining one element to the target
        target.push( source[ source.size()-1 ] );
        source.pop();
        
        // print two pegs states
        printHanoi(source, temp, target);
        
        // move the (depth-1) pile from the temporary peg to the target peg
        hanoi( temp, source , target , depth - 1, out );
    }
    return;
}



#endif /* hanoi_h */
