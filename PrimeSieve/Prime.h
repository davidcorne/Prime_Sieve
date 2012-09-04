//=============================================================================
// abstract base class for some prime finding functionality
//
//=============================================================================

#ifndef Prime_H
#define Prime_H

#include "PrimeSieve/LargeInt.h"

#include <ostream>
#include <vector>

// types: classes, enums, typedefs, namespaces

using std::ostream;
using std::string;
using std::vector;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class Prime {
public:

  Prime(const LARGE_INT& limit);
  // Constructor
  
  virtual ~Prime() = 0;
  // Destructor

  const LARGE_INT& count() const;
  // returns the number of primes
  // Precondition: m_calculated

  virtual bool is_prime(const LARGE_INT& prime) const = 0;
  // returns if the given number is prime
  // Precondition: m_calculated
  // Precondition: prime < m_limit

  void print_numbers() const;
  // prints out the primes bellow m_limit to std::cout
  // Precondition: m_calculated

  void write_file(const string& file_name) const;
  // Writes a file with the primes bellow m_limit
  // Precondition: m_calculated

protected:

  // functions
  Prime();
  // Prohibited default constructor

  Prime(const Prime&);
  // Prohibited copy constructor

  void operator=(const Prime&);
  // Prohibited assignment operator

  virtual void calculate() = 0;
  // Calculates the primes

  virtual void print_numbers_stream(ostream& stream) const = 0;
  // prints out the primes bellow m_limit to the stream
  // Precondition: m_calculated

  // variables
  LARGE_INT m_count;
  LARGE_INT m_limit;
  bool m_calculated;

};

#endif
