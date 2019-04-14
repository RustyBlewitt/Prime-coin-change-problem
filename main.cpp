#include <stdio.h>
#include <fstream>
#include "funcs.h"
#include <string>
#include <sstream>

using namespace std;

int main () {
    string line;
    string fname;
    cout << "Please enter input filename: ";
    cin >> fname;

    // Create filestream using input file
    ifstream fs (fname);

    // If file can be successfully opened
    if (fs.is_open()) {

        // For each line of input
        while ( getline(fs, line)) {
            // iss to help read input
            istringstream iss (line);
            vector<int> inputs;

            // x will receive data from istringstream
            string x;

            // Put inputs in vector
            while( iss >> x) {
                // Push integer equivalent of char from x to inputs
                inputs.push_back( stoi(x) );
            }

            if ( inputs.size() == 1 ) {
                // inputs[0] expects that the first value on line of input is balance.
                vector<int> coins = get_coins(inputs[0]);
                cout << recurse(inputs[0], coins) << " possible combinations" << endl;
            } else {
                cout << "Inputs of this size are not yet supported" << endl;
            }
        }

        return 0;
    }
    else {
        cout << "File " << fname << "could not be opened, check file and try again" << endl;
        return 1;
    }

}