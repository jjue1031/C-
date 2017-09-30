
/*
 Lingjue Xie
 PIC 10B Summer 2017
 ID: 904599062
 7/30/2017
 The program is to template the Pic10b::Vector class that we have been studying during lecture
 */

#ifndef pic10b_vector_h
#define pic10b_vector_h

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::ostream;

// forward declaration
namespace Pic10b{
    template<typename T>
    class vector;
}

template<typename T>
Pic10b::vector<T> operator+(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs);

ostream& operator<<(ostream& out, const Pic10b::vector<string>& v);

//--------------Declaration and Implementation of Pic10b::vector class. -------------------
namespace Pic10b{
    //class vector
    template<typename T>
    class vector{
    public:
        //default constructor
        vector():the_data(nullptr), the_capacity(INITIAL_CAP), the_size(0){
            cout << "xxxxxxxxxx Default constructor called" << endl;
            the_data = new T[the_capacity];
        }
        
        // copy constructor
        vector(const vector<T>& v) : the_data(nullptr), the_capacity(v.the_capacity), the_size(v.the_size){
            cout << "xxxxxxxxxx Copy constructor called" << '\n';
            // reserve heap memory
            the_data = new T[the_capacity];
            
            // deep copy
            for(size_t i=0; i<the_size; ++i){
                the_data[i] = v.the_data[i];
            }
        }
        
        // override assignment operator in order for deep copy
        vector<T>& operator=(const vector<T>& rhs){
            cout << "xxxxxxxxxx Assignment operator called" << endl;
            if(this != &rhs){
                // release dynamic memory
                delete[] the_data;
                
                the_data = new T[rhs.the_capacity];
                // shallow copy stack variable
                this->the_size = rhs.the_size;
                this->the_capacity = rhs.the_capacity;
                
                // deep copy
                for(size_t i=0; i<the_size; ++i){
                    the_data[i] = rhs.the_data[i];
                }
            }
            return *this;
        }
        
        // destructor
        ~vector(){
            // release dynamic memory
            delete[] the_data;
            cout << "xxxxxxxxxx Destructor called" << endl;
        }
        
        // operator []
        T& operator[](size_t index){
            return the_data[index];
        }
        
        // operator [] const version
        T operator[](size_t index) const{
            return the_data[index];
        }
        
        // return the size of the vector
        size_t size() const{
            return the_size;
        }
        
        // dot product
        T operator*(const vector<T>& rhs) const{
            T product = 0;
            for(size_t i=0; i< the_size; i++){
                product += (the_data[i] * rhs[i]);
            }
            return product;
        }

        
        void push_back( T new_value ){
            if ( the_size == the_capacity ) {
                // No room to grow, we need to move the data over to a "better"
                // location that has capacity for at leats one more value.
                reserve( the_capacity + 1 );
            }
            
            // add the new value to the end of the vector
            the_data[the_size] = new_value;
            ++the_size;
        }
        
        
        // override +=
        void operator+=(const vector<T>& rhs){
            for(size_t i = 0; i < the_size; i++){
                the_data[i] += rhs[i];
            }
        }
        
        // bool operator override
        bool operator<(const vector<T>& rhs) const{
            // use dot product to compare two vectors
            // reuse the overridden operator*
            return operator*(*this) <  operator*(rhs);
        }
        
        bool operator<=(const vector<T>& rhs) const{
            return operator*(*this) <=  operator*(rhs);
        }
        
        bool operator>(const vector<T>& rhs) const{
            return operator*(*this) >  operator*(rhs);
        }
        
        bool operator>=(const vector<T>& rhs) const{
            return operator*(*this) >=  operator*(rhs);
        }
        
        bool operator==(const vector<T>& rhs) const{
            return operator*(*this) ==  operator*(rhs);
        }
        
        
        bool operator!=(const vector<T>& rhs) const{
            return operator*(*this) !=  operator*(rhs);
        }
        
        
    private:
        T* the_data;
        size_t the_capacity;
        size_t the_size;
        
        static const int INITIAL_CAP = 10;
        
        void reserve( size_t new_capacity ){
            //     compare new_capacity to the_capacity
            //     if new_capacity is not big enough, the number is ignored
            if ( new_capacity > the_capacity ) {
                if ( new_capacity <= 2 * the_capacity )
                    new_capacity = 2 * the_capacity;
                
                // copy the pointer to the original data
                T* old_location = the_data;
                
                the_data = new T[new_capacity];
                the_capacity = new_capacity;
                
                for ( size_t i = 0 ; i < the_size ; ++i )
                    the_data[i] = old_location[i];
                delete old_location;
            }
        }
    };
    
    
    // definition of operator* with specialization of string
    template<>
    string vector<string>:: operator*(const vector<string>& rhs)const{
        string product;
        for(size_t i=0; i< the_size; i++){
            if(i == the_size-1) product = product + (the_data[i] + rhs[i]);
            else product = product + (the_data[i] + rhs[i]) + " + ";
        }
        return product;
    }
    
    // definition of bool operator with specialization of string
    template<>
    bool vector<string>::operator==(const vector<string>& rhs) const{
        bool compare = true;
        for (size_t i=0; i<the_size; i++){
            if(the_data[i] != rhs[i]){
                compare = false;
                break;
            }
        }
        return compare;
    }
    
    template<>
    bool vector<string>::operator!=(const vector<string>& rhs) const{
        return !((*this)==rhs);
    }
// end of namespace
}

//--------------Declaration and Implementation of non member functions --------------
// override operator<<
template<typename T>
ostream& operator<<(ostream& out, const Pic10b::vector<T>& v){
    for(size_t i=0; i < v.size(); ++i){
        if(i == 0) out << "{" << v[i] << ", ";
        else if(i == v.size()-1) out << v[i] << "}";
        else out << v[i] << ", ";
    }
    out << endl;
    return out;
}

// override operator<< with specialization of string
ostream& operator<<(ostream& out, const Pic10b::vector<string>& v){
    for(size_t i=0; i < v.size(); ++i){
        if(i == 0) out << "[ " << v[i] << ", ";
        else if(i == v.size()-1) out << v[i] << " ]";
        else out << v[i] << ", ";
    }
    out << endl;
    return out;
}


// override operator*
template<typename T>
Pic10b::vector<T> operator*(const Pic10b::vector<T>& v, T aNum){
    Pic10b::vector<T> v2=v;
    for(size_t i = 0; i<v2.size(); ++i){
        v2[i] *= aNum;
    }
    return v2;
}

// override operator* with specialization of string
Pic10b::vector<string> operator*(const Pic10b::vector<string>& v, string s){
    Pic10b::vector<string> v2=v;
    for(size_t i = 0; i<v2.size(); ++i){
        v2[i] = v2[i] + " " + s ;
    }
    return v2;
}

// override operator*
template<typename T>
Pic10b::vector<T> operator*(T aInt, const Pic10b::vector<T>& v){
    Pic10b::vector<T> v2=v;
    for(size_t i = 0; i<v2.size(); ++i){
        v2[i] *= aInt;
    }
    return v2;
}

// override operator* with specialization of string
Pic10b::vector<string> operator*(string s, const Pic10b::vector<string>& v){
    Pic10b::vector<string> v2=v;
    for(size_t i = 0; i<v2.size(); ++i){
        v2[i] = s + " " + v2[i];
    }
    return v2;
}

// override operator+
template<typename T>
Pic10b::vector<T> operator+(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs){
    Pic10b::vector<T> v = lhs;
    for(size_t i = 0; i < v.size(); i++){
        v[i] += rhs[i];
    }
    return v;
}


// override operator+ with specialization of string
Pic10b::vector<string> operator+(const Pic10b::vector<string>& lhs, const Pic10b::vector<string>& rhs){
    Pic10b::vector<string> v=lhs;
    for(size_t i = 0; i < v.size(); i++){
        v[i] = v[i]+rhs[i];
    }
    return v;
}

#endif /* pic10b_vector_h */
