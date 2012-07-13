//=============================================================================
//D generates primes
//
// a prime sieve based on the Sieve of Eratosthenes, see header for more detail
//

#include "sieve.h"
#include <assert.h> // use asserts
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <sstream>

// types: classes, enums, typedefs
// only use what we need from standard library
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::filebuf;
using std::ifstream;
using std::ostream;
using std::string;
using std::stringstream;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
sieve::sieve(const uint64_t& limit)
//
//D Constructor
//
  : m_count(-1), // 0 is a valid value for m_count so use something silly
    m_limit(limit),
    m_primes(limit, true), // initialise all the bits to true
    m_calculated(false)
{
  calculate();
}

//=============================================================================
sieve::~sieve()
//
//D Destructor, nothing newed so nothing needs deletion
//
{
}

//=============================================================================
void sieve::calculate()
//
//D Calculates a vector bool of primes
//
{
  // set 0 and 1 to be non-prime, and set 2 to be prime
  m_primes[0] = 0;
  m_primes[1] = 0;
  m_primes[2] = 1;

  uint64_t limit_sqrt = static_cast<int>(sqrt(m_limit));
  uint64_t current = 2;
  while (current < limit_sqrt) {
    // if it's prime then eliminate the multiples of it
    if (m_primes[current]) {
      uint64_t multiple = 2;
      while (multiple * current < m_limit) {
        m_primes[multiple * current] = 0;
        ++multiple;
      }
    }
    ++current;
  }
  // now count the primes
  m_count = 0;
  for (uint64_t i = 1; i < m_limit; ++i) {
    if (m_primes[i]) ++m_count;
  }
  m_calculated = true;
}

//=============================================================================
const uint64_t& sieve::count()
//
//D return how many primes there are less than limit
//
{
  assert(m_calculated);
  return m_count;
}

//=============================================================================
void sieve::print_numbers() const
//
//D print the primes less than limit
//
{
  assert(m_calculated);
  print_numbers_stream(cout);
}

//=============================================================================
void sieve::print_numbers_stream(ostream& stream) const
//
//D print the primes less than limit
//
{
  assert(m_calculated);
  for (uint64_t i = 1; i < m_limit; ++i) {
    if (m_primes[i]) {
      // write out the actual number which is prime
      stream << i << endl;
    }
  }
}

//=============================================================================
void sieve::write_file(const string& file_name) const
//
//D wrte primes to file_name
//
{
  assert(m_calculated);
  filebuf fb;
  fb.open (file_name.c_str(), std::ios::out);
  ostream os(&fb);
  print_numbers_stream(os);
  fb.close();
}

//=============================================================================
const char sieve::convert_to_text(const int& to_convert) const
//
//D
//
{
  // add 33 to the number then convert to ascii
  return static_cast<char>(to_convert);
}

//=============================================================================
const int sieve::convert_from_text(const char& c) const
//
//D
//
{
  // convert to int then take 33 away
  return (static_cast<int>(c));
}

void print_help(const string& arg_0)
//
//D Print the helpfile at the location of the ran exe, passed argument 0
//
{
  string file_location(arg_0, 0, arg_0.find_last_of('/'));
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
  uint64_t limit = 0;
  bool read = false;
  bool numerical = true;
  bool binary = false;
  string file = "";
  for (int i = 1; i < num_arguments; ++i) {
    string arg = string(arguments[i]);
    if (arg[0] == '-') {

      if (arg == "-h" || arg == "-help" || arg == "--help") {
        // help option
        print_help(arguments[0]);
        return 0;

      } else if (arg == "-b" || arg == "-binary") {
        // write in binary
        binary = true;
        numerical = false;

      } else if (arg == "-f" || arg == "-file") {
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
    } else {
      // convert the number into a long integer (sadly 32 bit atm)
      limit = atol(arg.c_str());
    }
  }

  if (limit == 0) {
    cout << "Enter limit: ";
    // output as error in case you are piping the output to a file
    cin >> limit;
    cout << endl;
  }

  sieve finder(limit);
  if (!read) {
    // output as error in case you are piping the output to a file
    cout << "Sieve of Eratosthenes array calculated." << endl;
  }
  return 0;
}
