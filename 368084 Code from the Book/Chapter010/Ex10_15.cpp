// Ex10_15.cpp Using lambda expressions
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std; // Just to avoid a lot of using directives in the example...
        
// Template function to return the average of the elements in a vector
template <class T> T average(const vector<T>& vec)
{
  static_assert(std::is_arithmetic<T>::value,
                            "Type parameter for average() must be aithmetic.");
  T sum(0);
  for_each(vec.begin(), vec.end(),
    [&sum](const T& value){ sum += value; });
  return sum/vec.size();
}
        
// Template function to set a vector to values beginning with start
// and incremented by increment
template <class T> void setValues(vector<T>& vec, T start, T increment)
{
  static_assert(std::is_arithmetic<T>::value,
                            "Type parameter for setValues() must be aithmetic.");
  T current(start);
  generate(begin(vec), end(vec),
    [increment, &current]()->T{T result(current);
                                current += increment;
                                return result;});
}
        
// Template function to set a vector to random values between min and max
template<class T> void randomValues(vector<T>& vec, T min, T max)
{
  static_assert(std::is_arithmetic<T>::value,
                            "Type parameter for randomValues() must be aithmetic.");
  srand(static_cast<unsigned int>(time(0)));   // Initialize random
                                              //  number generator
  generate(begin(vec), end(vec),
    [=](){ return static_cast<T>(static_cast<double>(rand())/
                                                     RAND_MAX*(max-min)+ min); });
}
        
// Template function to list the values in a vector
template<class T> void listVector(const vector<T>& vec)
{
  int count = 0;      // Used to control outputs per line
  const int valuesPerLine(5);
  for_each(begin(vec), end(vec),
    [&count, valuesPerLine](const T& n)->void{
                                 cout << setw(10) << n << "  ";
                                 if(++count % valuesPerLine == 0)
                                   cout << endl;});
}
        
int main()

{
  vector<int> integerData(50);
  randomValues(integerData, 1, 10);    // Set random integer values
  cout << "Vector contains:" << endl;
  listVector(integerData);
  cout << "Average value is "<< average(integerData) << endl;
        
  vector<double> realData(20);
  setValues(realData, 5.0, 2.5);   // Set real values starting at 5.0
  cout << "Vector contains:" << endl;
  listVector(realData);
  cout << "Average value is "<< average(realData) << endl;
        
   return 0;
}
