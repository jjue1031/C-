/* *************************************************
 Ricardo Salazar
 July 2017
 
 Driver for the Pic10b::vector<std::string> class.
 ************************************************* */

#include "pic10b_vector.h"   // Pic10b::vector<ItemType>
#include <iostream>          // std::cout
#include <iomanip>           // std::boolalpha
#include <string>            // std::string
#include <algorithm>         // std::reverse(...)

using std::cout;
using std::boolalpha;
using std::string;
using std::reverse;
using Pic10b::vector;


int main(){
    const string itemType = "std::string";
    const int SIZE = 6;
    const string newEntry = "airolG";
    
    cout << "Statement:\tvector<int> v1;\n";
    vector<string> v1;
    
    cout << "\nAction(s):\tv1 is populated with " << SIZE
    << " " + itemType + " values\n";
    v1.push_back("Abigail");
    v1.push_back("Beatriz");
    v1.push_back("Citlali");
    v1.push_back("Daneli");
    v1.push_back("Elisa");
    v1.push_back("Frida");
    
    cout << "\nStatement:\tvector<int> v2(v1);\n";
    vector<string> v2(v1);
    
    cout << "\nAction(s):\t3rd entry of v1 is modified (ilaltiC)\n"
    << "\t\tone more " << itemType + " value is pushed back ("
    << newEntry << ")\n" << "\t\tv1 is displayed\n";
    reverse(v1[2].begin(),v1[2].end());
    v1.push_back(newEntry);
    cout << "\tv1 = " << v1 << '\n';
    
    cout << "\nAction(s):\tv2 is displayed\n";
    cout << "\tv2 = " << v2 << '\n';
    
    cout << "\nStatement:\tv2 = v1;\n";
    v2 = v1;
    
    const string prefix = "Name:";
    const string lastName = "Salazar";
    cout << "\nStatement:\tv1 = ( " << prefix << " * v2 ) * "
    << lastName << ";\n";
    v1 = ( prefix * v2 ) * lastName;
    
    cout << "\nAction(s):\tv1 and v2 are displayed\n";
    cout << "\tv1 = " << v1 << '\n';
    cout << "\tv2 = " << v2 << '\n';
    
    
    cout << "\nAction(s):\tBoolean comparisons '==' and '!='\n";
    cout << std::boolalpha
    << "\tv1 == v2 is " << ( v1 == v2 ) << '\n'
    << "\tv2 != v1 is " << ( v2 != v1 ) << '\n';
    
    cout << "\nStatement:\treturn 0;\n";
    return 0;
}
