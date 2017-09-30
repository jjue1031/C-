/*
 Lingjue Xie
 PIC 10B Summer 2017
 ID: 904599062
 7/14/2017
 
 Program that implements the function
 double average_complexity( int );
 that repeatedly performs linear searches on a vector and computes the average number of comparisons needed to find an element.
 
 This program has a running time T = O (N).
 */


#ifndef hw3_h
#define hw3_h

#include <iostream>
#include <vector>
#include "hw3.h"

using namespace std;

// declaration of functions
double average_complexity( int );

void shuffleVector(vector<int>& intVector);


/** shuffleVector function
    This function shuffle the elements in the vector in order to make the vector look like random
    @param intVector is a reference of the int vector we want to be random
 */
void shuffleVector(vector<int>& intVector){
    size_t number_of_entry = intVector.size();
    
    //Fisher-Yates shuffle method
    //From the end of the vector, each time swap the last element with a random selected previous element
    for(size_t i = number_of_entry-1; i > 0; --i){
        
        int intToExchange = intVector[i];
        // random select an int from intVector[0] to intVector[i]
        int indexToExchange = rand() % (i+1);

        // swap intVector[i] and intVector[selected]
        intVector[i] = intVector[indexToExchange];
        intVector[indexToExchange] = intToExchange;
    }
}


// Implementation of average_complexity function

/** average_complexity function
    This function calculate the average steps linear search use for search a number in a vector which length is given 
    @param number_of_entry is number of int the vector contains
 */

double average_complexity( int number_of_entry ){
    
    vector<int> intVector(number_of_entry);
    // put 1:number_of_entry in order to the vector
    for(int i = 0; i<number_of_entry; ++i){
        intVector[i] = i+1;
    }
    
    // shuffle the vector, make it random
    shuffleVector(intVector);

    double averageStep = 0;
    
    // set total number of int to find equals to 10000
    for (size_t i=0; i<10000; i++){
        // record the total steps taken in ith loop
        size_t stepsToFind = 0;
        
        // randomly select the int to find
        int intToFind = rand() % (number_of_entry) +1;
        
        
        // linear search
        for(size_t j=0; j<number_of_entry; j++){
            stepsToFind++;
            if(intVector[j]==intToFind) break;
        }
        // update average steps
        averageStep = (averageStep*i + stepsToFind)/(i+1);
    }
    return averageStep;
}


#endif /* hw3_h */
