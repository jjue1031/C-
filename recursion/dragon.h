/*
 Lingjue Xie
 PIC 10B Summer 2017
 ID: 904599062
 8/6/2017
 The program is to implement function generate_dragon_sequence(...) which has recursive call inside 
 */

#include <ostream>
#include <vector>
using namespace std;

#ifndef dragon_h
#define dragon_h

// declaration and definition of generate_dragon_sequence function
void generate_dragon_sequence(vector<bool>& v, int numOfFlips, ostream& out){
    // if finish folding the imaginary paper strip, store all the data into ostream
    if(numOfFlips == 0){
        for(size_t i = 0; i<v.size(); i++){
            out << v[i] << endl;
        }
        return;
    }else{
        // adding an R at the end
        v.push_back(true);
        // taking the original iteration, flipping it retrograde
        for(int i = v.size()-2; i>=0; i--){
            //swapping each letter and adding the result after the R.
            v.push_back(!v[i]);
        }
        // call function itself with parameter numOfFlips-1, which is one fold fewer
        generate_dragon_sequence(v, numOfFlips-1, out);
    }
}

#endif /* dragon_h */
