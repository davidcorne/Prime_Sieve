//=============================================================================
// abstract base class for some prime finding functionality
//
//=============================================================================

#ifndef prime_H
#define prime_H

#include "large_int.h"

#include <ostream>
#include <vector>

// types: classes, enums, typedefs, namespaces

using std::ostream;
using std::string;
using std::vector;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
class prime {
public:

  prime(const LARGE_INT& limit);
  // Constructor
  
  virtual ~prime() = 0;
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
  prime();
  // Prohibited default constructor

  prime(const prime&);
  // Prohibited copy constructor

  void operator=(const prime&);
  // Prohibited assignment operator

  virtual void calculate() = 0;
  // Calculates the primes

  virtual void print_numbers_stream(ostream& stream) const = 0;
  // prints out the primes bellow m_limit to the stream
  // Precondition: m_calculated

  // variables
  bool m_calculated;
  LARGE_INT m_count;
  LARGE_INT m_limit;

};

#endif
