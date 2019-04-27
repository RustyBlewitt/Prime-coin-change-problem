#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

// FUNCTION: in_vector
// Checks if value is in vector
bool in_vector ( int n, vector<int> v ) 
{
    for( vector<int>::iterator i = v.begin(); i != v.end(); i++ )
    {
        if ( *i == n ) return true;   // Return true if n is found in vector
    }
    return false;           // Return false if all items checked and no success
}

// FUNCTION: get_coins
// Returns vector of [1, ...primes smaller than n... , n]
vector<int> get_coins ( int n )
{
    vector<int> composites;
    vector<int> coins;

    if ( n <= 0 ) return coins;    // Return empty vector if n <= 0
    coins.push_back(1);            // Push 1 as 1 is a valid coin
    if ( n == 1 ) return coins;    // Return only 1 coin if n == 1
    coins.push_back(2);            // Push 2 as 2 is the only even prime

    for ( int i = 3; i < n; i+=2 )     // For all other prime candidates (odd numbers > 2)
    {
        if ( !in_vector(i, composites) )  // If i not in composites...
        {
            coins.push_back(i);            // ...push i to coins
            for ( int j = 3; i*j < n; j += 2 )
            {    
                composites.push_back( i*j );      // Push all odd multiples of i and j (where j > 2) to composites
            }
        }
    }

    coins.push_back( n );            // Push n to coins as n is the 'gold' coin
    return coins;                  // Return coins vector
}

// FUNCTION: recurse
// Recursive function to find all valid coin combinations
int recurse( int balance, int* coins_ptr, int arg1 = 0, int arg2 = 0, int coins_used = 1 )
{
    int solutions = 0;

    while ( *coins_ptr != -1 )           // For all coins in coins array from coins_ptr to end of array
    {
        int new_balance = balance - *coins_ptr; // Balance following use of first available coin

        if ( new_balance == 0 )
        {
            // If ( success with 0 args || ( success with 1 arg ) || ( success with 2 args ) ) ...
            if ( arg1 == 0 || ( arg2 == 0 && arg1 == coins_used ) || ( arg1 <= coins_used && arg2 >= coins_used ) )
                solutions += 1;

            break;  // Prune as regardless of solution being found, next coin will result in overpaying
        }
        else if ( new_balance < 0 )
        {
            break;  // Prune as already over paying 
        }
        else    // This block reached when haven't yet paid full amount, recurse in here
        {
            if ( arg1 > 0 && arg2 == 0 && coins_used > arg1 )          
                break; // Prune if one input given and over specified number of coins to use

            else if ( 0 < arg2 && arg2 < coins_used )
                break; // Prune if two inputs given and over max number of coins to use

            else
                solutions += recurse ( new_balance, coins_ptr, arg1, arg2, coins_used + 1 );
        }

        coins_ptr++; // Move to next coin 

    }
        
    return solutions;

}

// Program runs here

int main ( int argc, char *argv[] ) {
    
    if ( argc != 2 ) {          // Bail out if any more or less than one additional arg given
        cout << "Please try running program again with input file's path as the only argument." << endl;
        return 1;
    }

    string fname = argv[1];     // Store input filename

    ifstream in_fs ( fname );   // Create input and output filestreams
    ofstream out_fs ( "output.txt" );

    string line;                // Where each line of input will be read to

    if ( in_fs.is_open() )            // If file can be successfully opened
    {   
        int line_num = 0;                 // Keep track of line number
        while ( getline( in_fs, line ) )  // While more lines of input file can be read ...
        {
            line_num++;
            istringstream iss (line);     // iss to help read input
            int inputs[] = {0, 0, 0};     // Init inputs to zero for use in algorithm 
            int inputs_count = 0;         // Track where to place inputs in above inputs array

            string x;                     // String x will hold groups of non whitespace string from istringstream

            while( iss >> x)              // While next group of non whitespace string can be sent to string x
            {
                if (inputs_count == 3)        // If three inputs already detected on line, bail out and notify user.
                {
                    cout << "More than 3 inputs detected on line" << line_num << 
                        ", please try again using 1, 2 or 3 inputs" <<endl;
                    return 1;
                }
                try                           // If input can be converted to int, add to inputs ...
                {
                    inputs[inputs_count] = stoi(x);
                }
                catch (...)                   // ... otherwise bail out and notify user
                {
                    cout << "Input could not be converted to integer on line " << line_num <<endl;
                    cout << "Check input file and try again." << endl;
                    return 1;
                }
                inputs_count++;
            }

            if ( inputs_count == 0 ) {          // If blank line encountered, notify user and move on to next line
                cout << "No inputs detected on line " << line_num << endl;
                continue;
            }

            vector<int> coins = get_coins(inputs[0]);   // Generate coins and store in vector

            clock_t start_t, end_t;                     // Set up timer
            double time_taken;
            start_t = clock();

            // Algorithm is executed and result stored here
            int result = recurse(inputs[0], &coins[0], inputs[1], inputs[2]);
            // ____________________________________________

            // Write result to outfile
            out_fs << result << endl;
            
            // Record and print time taken with result to standard output
            end_t = clock();
            time_taken = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
            cout << fixed << result << " " << time_taken << " secs" << endl;
        }
            
    }
    else // This block reached when input file stream could not be opened.
    {
        cout << argv[1] << " could not be opened, please check file / file path and try again." << endl;
        return 1;
    }

    // Close file streams
    in_fs.close();
    out_fs.close();

    return 0;
}