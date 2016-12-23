// Ex6_07.cpp
// Using overloaded functions
#include <iostream>
using std::cout;
using std::endl;
        
int max(int data[],const int& len);               // Prototypes for
long max(long data[],const int& len);             // a set of overloaded
double max(double data[],const int& len);         // functions
        
int main(void)
{
   int small[] = {1, 24, 34, 22};
   long medium[] = {23, 245, 123, 1, 234, 2345};
   double large[] = {23.0, 1.4, 2.456, 345.5, 12.0, 21.0};
        
   int lensmall(_countof(small));
   int lenmedium(_countof(medium));
   int lenlarge(_countof(large));

   cout << endl << max(small, lensmall);
   cout << endl << max(medium, lenmedium);
   cout << endl << max(large, lenlarge);
        
   cout << endl;
   return 0;
}
        
// Maximum of ints
int max(int x[],const int& len)
{
   int maximum(x[0]);
   for(int i = 1; i < len; i++)
      if(maximum < x[i])
         maximum = x[i];
   return maximum;
}
        
// Maximum of longs
long max(long x[],const int& len)
{
   long maximum (x[0]);
   for(int i = 1; i < len; i++)
      if(maximum < x[i])
         maximum = x[i];
   return maximum;
}
        
// Maximum of doubles
double max(double x[],const int& len)
{
   double maximum(x[0]);
   for(int i = 1; i < len; i++)
      if(maximum < x[i])
         maximum = x[i];
   return maximum;
}
