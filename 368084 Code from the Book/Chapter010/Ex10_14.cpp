// Ex10_14.cpp
// Using stream and inserter iterators
#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
        
int main()
{
  vector<int> numbers;
  cout << "Enter a series of integers separated by spaces"
       << " followed by Ctrl+Z or a letter:" << endl;
        
  std::istream_iterator<int> input(cin), input_end;
  std::ostream_iterator<int> out(cout, " ");
        
  copy(input, input_end, std::back_inserter<vector<int>>(numbers));
        
  cout << "You entered the following values:" << endl;
  copy(begin(numbers), end(numbers), out);
        
  cout << endl << "The sum of these values is "
       << std::accumulate(begin(numbers),end(numbers), 0) << endl;
  return 0;
}
