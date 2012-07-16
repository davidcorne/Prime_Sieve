//=============================================================================
//D generates primes, abstract class to be overridden
//

#include "prime.h"
#include <assert.h> // use asserts
#include <fstream>
#include <iostream>

// types: classes, enums, typedefs
// only use what we need from standard library
using std::cout;
using std::filebuf;

// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
prime::prime(const LARGE_INT& limit)
//
//D Constructor
//
  : m_count(-1), // 0 is a valid value for m_count so use something silly
    m_limit(limit),
    m_calculated(false)
{
}  

//=============================================================================
prime::~prime()
//
//D Destructor
//
{
}  

//=============================================================================
const LARGE_INT& prime::count() const
//
//D return how many primes there are less than limit
//
{
  assert(m_calculated);
  return m_count;
}

//=============================================================================
void prime::print_numbers() const
//
//D print the primes less than limit
//
{
  assert(m_calculated);
  print_numbers_stream(cout);
}

//=============================================================================
void prime::write_file(const string& file_name) const
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
