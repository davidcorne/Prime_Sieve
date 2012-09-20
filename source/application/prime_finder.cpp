//=============================================================================
//D The app that runs a (command line) prime finder

#include "PrimeSieve/sieve.h"
#include "PrimeSieve/naive.h"

#include <fstream>
#include <iostream>
#include <time.h>


// types: classes, enums, typedefs, namespaces

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
void print_help(const string& location)
//
//D Print the helpfile (help.txt) from the location given
//
{
  string file_location(location, 0, location.find_last_of('/'));
  file_location.append("/help_prime_finder.txt");
  ifstream file(file_location.c_str());
  if (file) {
    // print the buffer to standard output
    cout << file.rdbuf();
    file.close();
  } else {
    cerr << "Help file " << file_location << " not found." << endl;
  }
}

//=============================================================================
LARGE_UINT ask_for_limit()
//
//D Asks the user for the limit needed
{
  LARGE_UINT limit = 0;
  cerr << "Enter limit: ";
  // output as error in case you are piping the output to a file
  cin >> limit;
  cerr << endl;
  return limit;
}

//=============================================================================
void compare_time()
//
//D Compares the run times between the naive and sieve algorithms.
//
{
  LARGE_UINT limit = ask_for_limit();
  
  // clock() returns the number of clock ticks since the program started so
  // constantly subtract it from itself
  clock_t time_elapsed = clock();
  Naive n(limit);
  time_elapsed = clock() - time_elapsed;
  cout << "Naive - ";
  cout << "run time: " << ((float)time_elapsed) / CLOCKS_PER_SEC
      << " seconds "
      << endl;
  
  time_elapsed = clock();
  Sieve s(limit);
  time_elapsed = clock() - time_elapsed;
  cout << "Sieve - ";
  cout << "run time: " << ((float)time_elapsed) / CLOCKS_PER_SEC
      << " seconds "
      << endl;
}

//=============================================================================
int main(int num_arguments, char* arguments[])
//
//D The entry point and single function of this program
//
{
  // iterate over command line options
  LARGE_UINT limit = 0;
  string file = "";
  bool write = false;
  
  for (int i = 1; i < num_arguments; ++i) {
    string arg = string(arguments[i]);
    if (arg[0] == '-') {
      if (arg == "-h" || arg == "-help" || arg == "--help") {
        // help option
        print_help(arguments[0]);
        return 0;

      } else if (arg == "-c") {
        compare_time();
        return 0;

      } else if (arg == "-f") {
        write = true;
        // write to a file option
        if (i + 1 == num_arguments) {
          cerr << "Need a file name" << endl;
          return 0;
        }
        file = arguments[i+1];
        ++i;

      } else {
        cerr << "Unknown option" << endl;
        print_help(arguments[0]);
        return 0;
      }
    }
  }
  
  limit = ask_for_limit();
  Sieve finder(limit);
  cerr << "Prime array calculated." << endl;
  if (write) {
    // write to the given file
    finder.write_file(file);
    cout << file << " written." << endl;
  } else {
    if (finder.count() < 1000) {
      finder.print_numbers();
    }
  }
  cout << "There are " << finder.count() << " primes below " << limit 
       << "." << endl; 
  
  return 0;
}
