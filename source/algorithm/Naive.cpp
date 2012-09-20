//=============================================================================
//D generates primes
//

#include "PrimeSieve/Naive.h"
#include <assert.h> // use asserts
#include <iostream>
#include <math.h>

// types: classes, enums, typedefs
// only use what we need from standard library
using std::endl;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
Naive::Naive(const LARGE_UINT& limit)
//
//D Constructor
//

  : Prime(limit),
    m_primes(limit / 2, false)  // initialise all the bits to false
{
  calculate();
}

//=============================================================================
Naive::~Naive()
//
//D Destructor, nothing newed so nothing needs deletion
//
{
}

//=============================================================================
void Naive::calculate()
//
//D Calculates a vector bool of primes
//
{
  m_count = 0;
  if (m_limit >= 2) {
    // 2 not counted by this
    m_count = 1;
  }
  
  for (LARGE_UINT i = 3; i < m_limit; i += 2) {
    LARGE_UINT num_sqrt = static_cast<LARGE_UINT>(sqrt(i));
    LARGE_UINT j = 0;
    bool prime = true;
    while (j <= ((num_sqrt - 3) / 2)) {
      // divide by all the numbers
      LARGE_UINT number_to_divide_by = (2 * j) + 3;
      if (number_to_divide_by > num_sqrt) {
        // if you've not found factors by the square root you're never going to
        break;
      }
      if (i % number_to_divide_by == 0) {
        // if there is a factor it's not prime
        prime = false;
        break;
      }
      ++j;
    }
    if (prime) {
      m_primes[(i - 3) / 2] = true;
      ++m_count;
    }
  }
  m_calculated = true;
}

//=============================================================================
void Naive::print_numbers_stream(ostream& stream) const
//
//D print the primes less than limit
//
{
  assert(m_calculated);
  if (m_limit >= 2) {
    stream << "2" << endl;
  }
  for (LARGE_UINT i = 0; i < m_primes.size(); ++i) {
    if (m_primes[i]) {
      // write out the actual number which is prime
      stream << 2*i + 3 << endl;
    }
  }
}

//=============================================================================
bool Naive::is_prime(const LARGE_UINT& prime) const
//
//D returns whether prime is prime
//
{
  assert(m_calculated);
  if (prime == 2) {
    return true;
  }
  if (prime % 2 == 0) {
    return false;
  }
  return m_primes[(prime - 3) / 2];
}

