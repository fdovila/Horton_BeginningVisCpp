// Ex10_04
// Using array containers
#include <iostream>
#include <iomanip>
#include <array>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::array;
using std::accumulate;


template<class T, size_t N>
void listValues(const array<T, N>& data)
{
  const int values_per_line(6);
  int count(0);
  for(auto& value : data)
  {
    cout << setw(14) << value;
    if(++count % values_per_line == 0)
      cout<< endl;
  }
  cout << endl;
}

int main()
{
  // Create the famous Fibonacci series
  const size_t N(20);
  array<long, N> fibonacci = {1L, 1L};
  for(size_t i = 2 ; i<fibonacci.size() ; ++i)
    fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
  cout << "Fibonacci series is:" << endl;
  listValues(fibonacci);

  array<long, N> numbers;
  numbers.fill(99L);
  fibonacci.swap(numbers);
  cout << endl << "After swap fibonacci contains:" << endl;
  listValues(fibonacci);

  // Create the series for pi/4
  array<double, 120> series;
  double factor(-1.0);
  for(size_t x = 0 ; x<series.size() ; ++x)
  {
    factor *= -1.0;
    series[x] = factor/(2*x+1);
  }
  cout << endl << "Series for pi is:" << endl;
  listValues(series);
  double result(accumulate(begin(series), end(series), 0.0));
  cout << "The series sum converges slowly to pi/4. The sum x 4 is: " << 4.0*result << endl;

  return 0;
}
