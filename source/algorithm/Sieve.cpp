//=============================================================================
//D generates primes
//
// a prime sieve based on the Sieve of Eratosthenes, see header for more detail
//

#include "PrimeSieve/Sieve.h"
#include <assert.h> // use asserts
#include <math.h>

// types: classes, enums, typedefs
// only use what we need from standard library
using std::endl;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
Sieve::Sieve(const LARGE_UINT& limit)
//
//D Constructor
//
  : Prime(limit),
    m_primes(limit, true) // initialise all the bits to true
{
  calculate();
}

//=============================================================================
Sieve::~Sieve()
//
//D Destructor, nothing newed so nothing needs deletion
//
{
}

//=============================================================================
void Sieve::calculate()
//
//D Calculates a vector bool of primes
//
{
  // set 0 and 1 to be non-prime, and set 2 to be prime
  m_primes[0] = 0;
  m_primes[1] = 0;
  m_primes[2] = 1;

  LARGE_UINT limit_sqrt = static_cast<LARGE_UINT>(sqrt(m_limit));
  LARGE_UINT current = 2;
  while (current <= limit_sqrt) {
    // if it's prime then eliminate the multiples of it
    if (m_primes[current]) {
      LARGE_UINT multiple = 2;
      while (multiple * current < m_limit) {
        m_primes[multiple * current] = 0;
        ++multiple;
      }
    }
    ++current;
  }
  // now count the primes
  m_count = 0;
  for (LARGE_UINT i = 1; i < m_limit; ++i) {
    if (m_primes[i]) {
      ++m_count;
    }
  }
  m_calculated = true;
}

//=============================================================================
void Sieve::print_numbers_stream(ostream& stream) const
//
//D print the primes less than limit
//
{
  assert(m_calculated);
  for (LARGE_UINT i = 1; i < m_limit; ++i) {
    if (m_primes[i]) {
      // write out the actual number which is prime
      stream << i << endl;
    }
  }
}

//=============================================================================
bool Sieve::is_prime(const LARGE_UINT& prime) const
//
//D returns whether prime is prime
//
{
  assert(m_calculated);
  assert(prime < m_limit);
  return m_primes[prime];
}

