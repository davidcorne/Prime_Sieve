//=============================================================================
//D unit test for the prime finding classes I have with the same API.

#include "PrimeSieve/Sieve.h"
#include "PrimeSieve/Naive.h"

#include <assert.h> // use asserts
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

// types: classes, enums, typedefs, namespaces
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
void utest(const bool test_value, const string& message)
//
//D Test the value and return the message with PASSED or FAILED, assert on fail
//
{
  if (!test_value) {
    cerr << "FAILED: " << message << endl;
    assert(test_value);
  } else {
    cout << "PASSED: " << message << endl;
    cout << endl;
  }
}

//=============================================================================
template<typename PRIME_FINDER>
void test_prime_count_limit(LARGE_INT limit, LARGE_INT expected_primes) {
  PRIME_FINDER primes(limit);
  stringstream ss;
  ss << expected_primes << " primes below " << limit;
  utest(primes.count() == expected_primes, ss.str());
}

//=============================================================================
template<typename PRIME_FINDER>
void test_prime_count() {
  //D test various numbers of primes
  cout << "Test 1" << endl;
  cout << endl;
  test_prime_count_limit<PRIME_FINDER>(100, 25);
  test_prime_count_limit<PRIME_FINDER>(1000, 168);
  test_prime_count_limit<PRIME_FINDER>(100000, 9592);
  test_prime_count_limit<PRIME_FINDER>(1000000, 78498);
}

//=============================================================================
template<typename PRIME_FINDER>
void test_correct_primes() {
  //D test that the primes are the correct ones
  cout << "Test 2" << endl;
  cout << endl;
  int limit = 100;

  PRIME_FINDER primes(limit);
  int small_primes[25] =
    {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  for (int i = 0; i < 25; ++i) {
    // these entries should be true as they are prime
    stringstream ss;
    ss << small_primes[i];
    string msg = ss.str();
    msg += " is prime";
    utest(primes.is_prime(small_primes[i]), msg);
  }
  // now test some non-primes, for simplictiy on check multiples of 2, 3, 5
  // and 7
  for (int i = 8; i < 100; ++i) {
    if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
      // these entries should be false as they are not prime
      stringstream ss;
      ss << i;
      string msg = ss.str();
      msg += " is not prime";
      utest(!primes.is_prime(i), msg);
    }
  }
}

//=============================================================================
template<typename PRIME_FINDER>
void test_file_output() {
  //D tests outputting to a file
  cout << "Test 3" << endl;
  cout << endl;
  string file_name = "test_file.txt";
  PRIME_FINDER primes(100);
  primes.write_file(file_name);

  ifstream prime_file(file_name.c_str());
  if (prime_file.is_open()) {
    string line;
    while (getline(prime_file, line).good()) {
      int result;
      stringstream convert(line);
      convert >> result;
      string message = line + " is in the file";
      utest(primes.is_prime(result), message);
    }
    prime_file.close();
  }
  // delete the created file
  utest(remove(file_name.c_str()) == 0, "File succesfully removed");
}

template<typename PRIME_FINDER>
void run_tests() {
  test_prime_count<PRIME_FINDER>();
  test_correct_primes<PRIME_FINDER>();
  test_file_output<PRIME_FINDER>();
}  

//=============================================================================
int main(int num_arguments, char* arguments[])
//
//D The entry for the tests
//
{
  cout << "Testing naive implementation" << endl;
  run_tests<naive>();

  cout << "Testing sieve implementation" << endl;
  run_tests<sieve>();
  
  return 0;
}
