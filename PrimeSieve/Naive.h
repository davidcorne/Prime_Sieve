//=============================================================================
// Implementation of a naive prime finding method. We store all the odd numbers
// in a vector<bool> m_primes and if m_primes[i] is true then 2i + 3 is prime.
//
//=============================================================================

#ifndef Naive_H
#define Naive_H

#include "PrimeSieve/Prime.h"

// types: classes, enums, typedefs, namespaces

using std::ostream;
using std::vector;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class Naive : public Prime {
public:

  Naive(const LARGE_INT& limit);
  // Constructor, calculates the vector of primes

  ~Naive();
  // Destructor

  bool is_prime(const LARGE_INT& prime) const;
  // returns if the given number is prime
  // Precondition: m_calculated
  // Precondition: prime < m_limit

private:

  // functions
  Naive();
  // Prohibited default constructor

  Naive(const Naive&);
  // Prohibited copy constructor

  void operator=(const Naive&);
  // Prohibited assignment operator

  void calculate();
  // Calculates the primes

  void print_numbers_stream(ostream& stream) const;
  // prints out the primes bellow m_limit to the stream
  // Precondition: m_calculated

  // variables
  vector<bool> m_primes;

};

#endif
