// Ex10_13.cpp
// A simple word collocation
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <iterator>
using std::cout;
using std::cin;
using std::endl;
using std::string;
        
int main()
{
  std::map<string, int> words;              // Map to store words and word counts
  cout << "Enter some text and press Enter followed by Ctrl+Z then Enter to end:"
       << endl << endl;
        
  std::istream_iterator<string> begin(cin); // Stream iterator
  std::istream_iterator<string> end;        // End stream iterator
        
  while(begin != end)                       // Iterate over words in the stream
    words[*begin++]++;                      // Increment and store a word count
        
  // Output the words and their counts
  cout << endl << "Here are the word counts for the text you entered:" << endl;
  const int wordsPerLine(4);
  int wordCount(0);
  cout << std::setiosflags(std::ios::left); // Ouput left-justified
  for (auto& word : words)
  {
    cout << std::setw(15) << word.first << " " << std::setw(5) << word.second;
    if(++wordCount % wordsPerLine == 0) cout << endl;
  }
  cout << endl;
        
  return 0;
}
