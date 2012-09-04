//=============================================================================
// Implementation of the Sieve of Eratosthenes to find primes.
//
// Algorithm:
//
//  1) Create a list of consecutive integers from 2 to n: (2, 3, 4, ..., n).
//  2) Initially, let p equal 2, the first prime number.
//  3) Starting from p, count up in increments of p and mark each of these
//     numbers greater than p itself in the list. These numbers will be 2p,
//     3p, 4p, etc.; note that some of them may have already been marked.
//  4) Find the first number greater than p in the list that is not marked. If
//     there was no such number, stop. Otherwise, let p now equal this number
//     (which is the next prime), and repeat from step 3.
//
// When the algorithm terminates, all the numbers in the list that are not
// marked are prime.
//
// Note: due to the size of some numbers most places ints would be used long
// unsigned 64 bit integers are used instead.
//
//=============================================================================

#ifndef Sieve_H
#define Sieve_H

#include "PrimeSieve/Prime.h"

// types: classes, enums, typedefs, namespaces

using std::ostream;
using std::string;
using std::vector;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class Sieve : public Prime {
public:

  Sieve(const LARGE_INT& limit);
  // Constructor, calculates the vector of primes

  ~Sieve();
  // Destructor

  bool is_prime(const LARGE_INT& prime) const;
  // returns if the given number is prime
  // Precondition: m_calculated
  // Precondition: prime < m_limit

private:

  // functions
  Sieve();
  // Prohibited default constructor

  Sieve(const Sieve&);
  // Prohibited copy constructor

  void operator=(const Sieve&);
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
