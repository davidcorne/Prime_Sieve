//=============================================================================
//D unit test for the prime finding sieve

#include "sieve.h"

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
//D Print the helpfile (help.txt) from the location given
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

class utest_sieve {
public:
  void run_tests() {
    test_1();
    test_2();
    test_3();
  }

private:
  void test_1() {
    //D test various numbers of primes
    cout << "Test 1" << endl;
    cout << endl;
    int limit = 100;

    sieve primes(limit);
    utest(primes.count() == 25, "25 primes below 100");

    limit = 1000;
    change_limit(primes, limit);
    utest(primes.count() == 168, "168 primes below 1,000");

    limit = 10000;
    change_limit(primes, limit);
    utest(primes.count() == 1229, "1,229 primes below 10,000");

    limit = 100000;
    change_limit(primes, limit);
    utest(primes.count() == 9592, "9,592 primes below 100,000");

    limit = 1000000;
    change_limit(primes, limit);
    utest(primes.count() == 78498, "78,498 primes below 1,000,000");
  }

  void test_2() {
    //D test that the primes are the correct ones
    cout << "Test 2" << endl;
    cout << endl;
    int limit = 100;

    sieve primes(limit);
    bool ok = true;
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

  void test_3() {
    //D tests outputting to a file
    cout << "Test 3" << endl;
    cout << endl;
    string file_name = "test_file.txt";
    sieve primes(100);
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

  void change_limit(sieve& primes, int limit) {
    //D emulate the construction of a new sieve
    primes.m_limit = limit;
    vector<bool> new_list(limit, true);
    primes.m_primes = new_list;
    primes.m_calculated = false;
    primes.calculate();
  }

};

//=============================================================================
int main(int num_arguments, char* arguments[])
//
//D The entry for the tests
//
{
  utest_sieve test;
  test.run_tests();
  return 0;
}
