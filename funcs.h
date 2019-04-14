#ifndef FUNCS_H
#define FUNCS_H
#include <iostream>
#include <vector>
#include <time.h>
#include <numeric>

using namespace std;

// Function: show_vector
// Prints all items in vector to console
void show_vector(std::vector<int> v) {

    // Show mem loc of vector
    cout << "Items in vector at mem location: " << &v << endl;
    // Loop through vector using iterator, printing each item on each iteration
        for(std::vector<int>::iterator i = v.begin(); i != v.end(); i++){
            // cout << *i << endl;
            cout << *i << ' ';
        }
}

// Function: get_range
// Get range, takes lower bound and upper bound and returns vector of all nums between.
std::vector<int> get_range(int lower_bound, int upper_bound) {

    // Declare int vector v 
    std::vector<int> v;

    // For all vals lower_bound to upper_bound, add val to vector
    for (int i = lower_bound; i <= upper_bound; i++){
        v.push_back(i);
    }

   // Return vector
    return v;
}

// Function: get_rev_range
// Get range in reverse, takes lower bound and upper bound and returns vector of all nums between.
std::vector<int> get_rev_range(int lower_bound, int upper_bound) {

   // Declare int vector v 
   std::vector<int> v;

   // For all vals upper_bound to lower_bound, add val to vector
    for (int i = upper_bound; i >= lower_bound; i--){
        v.push_back(i);
    }

   // Return vector
    return v;
}

// Function: in_vector
// Checks if value is in vector
bool in_vector(int n, std::vector<int> v) {

   // Iterate over vector and return true if iteration == n
    for(std::vector<int>::iterator i = v.begin(); i != v.end(); i++){
        if (*i == n) {
            return true;
        };
    }
   
   // Return false
    return false;

}

// Function: get_primes
// Get all primes smaller than n, returns vector of primes.
std::vector<int> get_primes(int n) {

    std::vector<int> composites;
    std::vector<int> primes;

    // Init 2 as 2 is the only even prime number
    primes.push_back(2);

    // For all possible primes, check if already in composites.
    // Start from 3 to skip initialised 2 and increment by 2 to skip even numbers.
    for(int i = 3; i < n; i+=2) {

      // If c not composite, put in prime then fill composites with all multiples of c that are < n
        if(!in_vector(i, composites)){
            primes.push_back(i);
            // cout<<i<<'\n';
            for(int j=3; i*j <= n; j+=2){
                composites.push_back(i*j);
            }
        }

    }

   // Return vector
    return primes;
}

// Function: get_coins
// Get all primes smaller than n, returns vector of 1, primes and n.
std::vector<int> get_coins(int n) {

    std::vector<int> composites;
    std::vector<int> primes;

    // Init 1 and 2 as 1 is a valid coin and 2 is the only even prime number.
    primes.push_back(1);
    primes.push_back(2);

    // For all possible primes, check if already in composites.
    // Start from 3 to skip initialised 2 and increment by 2 to skip even numbers.
    for(int i = 3; i < n; i+=2) {

      // If i not in composites, put i in primes then fill composites with all multiples of i that are < n
        if(!in_vector(i, composites)){
            primes.push_back(i);
            for(int j=3; i*j < n; j+=2){
                composites.push_back(i*j);
            }
        }

    }

    // Push n as n is the gold coin
    primes.push_back(n);

   // Return vector
    return primes;
}

int v_sum (vector<int> v) {
    return accumulate(v.begin(), v.end(), 0);
}

int recurse ( int balance, vector<int> coins, int level = 0) {
    int solutions = 0;
    for (int i = 0; i < coins.size(); i++) {
        
        int new_balance = balance - coins[i];

        // Details for debugging -----------------------------------------------------
        // Pad for level of recursion to track process
        for (int x = 0; x < level * 2; x++) {
            cout << ' ';
        }

        cout << '[' << balance << ']' << " - " << coins[i] << " coin = " << new_balance << endl;
        // ---------------------------------------------------------------------------

        if ( new_balance == 0 ){
            solutions += 1;
            break;
        } else if ( new_balance < 0 ){
            break;
        }
        else {
            vector<int>::const_iterator first = coins.begin() + i;
            vector<int>::const_iterator last = coins.end();
            vector<int> new_coins(first, last);
            show_vector (new_coins);

            solutions += recurse (new_balance, new_coins, level + 1);
            }
        }
    return solutions;
    }

#endif