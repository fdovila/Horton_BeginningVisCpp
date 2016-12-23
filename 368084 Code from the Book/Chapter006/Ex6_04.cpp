// Ex6_04.cpp  Using exception handling
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
  int counts[] = {34, 54, 0, 27, 0, 10, 0};
  int time(60);                        // One hour in minutes
  int hour(0);                         // Current hour
        
  for(auto& count : counts)
  {
    try
    {
      cout << endl << "Hour " << ++hour;
        
      if(0 == count)
        throw "Zero count - calculation not possible.";
        
      cout << " minutes per item: " << static_cast<double>(time)/count;
    }
    catch(const char aMessage[])
    {
      cout << endl << aMessage << endl;
    }
  }
  return 0;
}
