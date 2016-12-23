// Ex10_06.cpp
// Working with a list
        
#include <iostream>
#include <list>
#include <string>
// #include <functional>
        
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
        
int main()
{
  list<string> text;
        
  // Read the data
  cout << "Enter a few lines of text. Just press Enter to end:"
       << endl;
  string sentence;
  while(getline(cin, sentence, '\n'), !sentence.empty())
    text.push_front(sentence);
 
  //while(getline(cin, sentence, '\n'), !sentence.empty())
  //  text.emplace_front(std::move(sentence));

  // Output the data using an iterator
  cout << endl << "In reverse order, here is the text you entered:" << endl;
  for(auto& s : text)
    cout << s << endl;
        
  // Sort the data in ascending sequence
  cout << endl << "In ascending sequence the sentences you entered are:" << endl;
  text.sort();
//  text.sort(std::greater<string>());
  for(auto& s : text)
    cout << s << endl;
        
  return 0;
}
