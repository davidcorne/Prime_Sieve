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

#ifndef _sieve_H
#define _sieve_H

#include <stdlib.h>
#include <ostream>
#include <vector>

// types: classes, enums, typedefs, namespaces
using std::vector;

class istream;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class sieve {
public:

  sieve(const uint64_t& limit);
  // Constructor, calcualtes the 

  ~sieve();
  // Destructor

  const uint64_t& count();
  // returns the number of primes
  // Precondition: m_calculated

  void print_numbers() const;
  // prints out the primes bellow m_limit to std output
  // Precondition: m_calculated

  void write_file(const std::string& file_name) const;
  // Writes a file with the primes bellow m_limit
  // Precondition: m_calculated

private:

  // friends
  // functions
  sieve();
  // Prohibited default constructor

  sieve(const sieve&);
  // Prohibited copy constructor

  void operator=(const sieve&);
  // Prohibited assignment operator

  void calculate();
  // Calculates the primes

  void print_numbers_stream(std::ostream& stream) const;
  // prints out the primes bellow m_limit to the stream
  // Precondition: m_calculated

  const char convert_to_text(const int& to_convert) const;
  // converts an integer into a character of ascii value 33 above it's value to
  // eliminate whitespace characters

  const int convert_from_text(const char& c) const;
  // reverse convert_to_text

  // variables
  vector<bool> m_primes;
  bool m_calculated;
  uint64_t m_count;
  uint64_t m_limit;

};

#endif
