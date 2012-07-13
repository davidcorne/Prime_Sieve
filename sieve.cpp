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

// types: classes, enums, typedefs
// only use what we need from standard library
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::filebuf;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
sieve::sieve(const LARGE_INT& limit)
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

  LARGE_INT limit_sqrt = static_cast<int>(sqrt(m_limit));
  LARGE_INT current = 2;
  while (current <= limit_sqrt) {
    // if it's prime then eliminate the multiples of it
    if (m_primes[current]) {
      LARGE_INT multiple = 2;
      while (multiple * current < m_limit) {
        m_primes[multiple * current] = 0;
        ++multiple;
      }
    }
    ++current;
  }
  // now count the primes
  m_count = 0;
  for (LARGE_INT i = 1; i < m_limit; ++i) {
    if (m_primes[i]) ++m_count;
  }
  m_calculated = true;
}

//=============================================================================
const LARGE_INT& sieve::count() const
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
  for (LARGE_INT i = 1; i < m_limit; ++i) {
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
