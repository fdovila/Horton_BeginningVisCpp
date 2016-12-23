// Ex10_05.cpp
// Using a double-ended queue
        
#include <iostream>
#include <deque>
#include <algorithm>                 // For sort<T>()
#include <numeric>                   // For accumulate<T>()
#include <functional>                // For function objects
        
using std::cin;
using std::cout;
using std::endl;
using std::deque;
using std::sort;
        
int main()
{
  deque<int> data;
        
  // Read the data
  cout << "Enter a series of non-zero integers separated by spaces."
       << " Enter 0 to end." << endl;
  int value(0);
  while(cin >> value, value != 0)
    data.push_front(value);
        
  // Output the data
  cout << endl << "The values you entered are:" << endl;
  for(auto& n : data)
    cout << n << "  ";
  cout << endl;
        
  // Output the data using a reverse iterator
  cout << endl << "In reverse order the values you entered are:" << endl;
  for(auto riter = data.rbegin() ; riter != data.rend() ; riter++)
    cout << *riter << "  ";
        
  // Sort the data in descending sequence
  cout << endl;
  cout << endl << "In descending sequence the values you entered are:" << endl;
  sort(data.begin(), data.end(), std::greater<int>());   // Sort the elements
//  sort(data.rbegin(), data.rend());                      // Sort the elements
  for(auto& n : data)
    cout << n << "  ";
  cout << endl;
        
  // Calculate the sum of the elements
  cout << endl << "The sum of the elements in the queue is: "
       << std::accumulate(data.begin(), data.end(), 0)  << endl;
        
  return 0;
}
