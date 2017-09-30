#include <iostream>   // std::cout
#include <ctime>      // time()
#include <cstdlib>    // RAND_MAX, rand(), srand()
#include <fstream>    // std::ostream
#include <iomanip>    // std::fixed, std::setprecision
#include "hw3.h"      // average_complexity(...)



// Number of times this driver will call the function
// 'average_complexity(...)'
int const NUM_TRIALS = 100;


// Test the efficiency of your function by slowly increasing the
// values of MAX_N. I suggest using [some, or all of] the values
// below:
//
// long int const MAX_N = RAND_MAX;
// int const MAX_N = 16000;
// int const MAX_N = 8000;
// int const MAX_N = 4000;
//
// Notes:
// + Only test for big numbers once you are confident your program has
//   been optimized. If it is not optimized, even relatively small
//   values of MAX_N (e.g. 10000) could cause this program to run for
//   hours and even days.
//
// + RAND_MAX (above), is architecture dependent, it could be as small
//   as 32767, or it could be way bigger. For example, in my main
//   computer (the one I use for lectures), RAND_MAX = 2147483647,
//   which is about 2.15 billion.
int const MAX_N = 4000;


// The function you need to implement in the separate library file
// 'hw3.h' must have the signature
//
//     double average_complexity( int );
//
// Within this library file you are free to implement as many other
// functions and/or classes as you see fit.




int main(){
    
    /**
     *  Setup needed to find out how long it takes for this
     *  program to perform all computations. Feel free to comment
     *  this out, or to remove it from this driver. I will
     *  use a different set of benchmark tools to measure the
     *  efficiency of your code.
     */
    long int startingTime = static_cast<long int>( time( NULL ) );
    srand( startingTime );
    
    
    
    // This program should create the file 'data.txt'. This file will
    // be used to visualize [plot] your data.
    std::ofstream fout("data.txt");
    fout << std::setprecision(2) << std::fixed ;
    
    
    // Perform experiment [linear search] NUM_TRIALS times.
    // (see global constants above)
    for ( int k = 0 ; k < NUM_TRIALS ; k++ ){
        
        int n = 1 + rand() % MAX_N ;  // Random number in [1,MAX_N]
        double T_n = average_complexity(n);
        
        // Output data to file
        fout << n << '\t' << T_n << '\n';
    }
    
    
    // Close file stream and display usage statistics.
    fout.close();
    
    
    
    /**
     *  Do not forget to eliminate this part as well in case you
     *  decided not to time your program.
     */
    std::cout << "Program ran in: "
    << static_cast<long int>( time(0) ) - startingTime
    << " seconds" << '\n' ;
    
    return 0;
} 
