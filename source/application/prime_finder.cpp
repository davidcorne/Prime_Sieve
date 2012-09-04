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
  file_location.append("/help.txt");
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
int main(int num_arguments, char* arguments[])
//
//D The entry point and single function of this program
//
{
  // iterate over command line options
  LARGE_INT limit = 0;
  string file = "";
  bool write = false;
  for (int i = 1; i < num_arguments; ++i) {
    string arg = string(arguments[i]);
    if (arg[0] == '-') {
      if (arg == "-h" || arg == "-help" || arg == "--help") {
        // help option
        print_help(arguments[0]);
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
  cerr << "Enter limit: ";
  // output as error in case you are piping the output to a file
  cin >> limit;
  cerr << endl;
  clock_t t_start = clock();
  naive n(limit);
  cout << "Naive: ";
  cout << "run time: " << (clock() - t_start)/CLOCKS_PER_SEC
       << " seconds " << (clock() - t_start) << " microseconds"
       << endl;

  t_start = clock();
  sieve s(limit);
  cout << "Sieve: ";
  cout << "run time: " << (clock() - t_start)/CLOCKS_PER_SEC
       << " seconds " << (clock() - t_start) << " microseconds"
       << endl;

  return 0;
  
  naive finder(limit);
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
