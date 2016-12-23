// Ex6_02.cpp
// A pointer to a function as an argument
#include <iostream>
using std::cout;
using std::endl;
        
// Function prototypes
double squared(double);
double cubed(double);
double sumarray(double data[], int len, double (*pfun)(double));
        
int main(void)
{
  double data[] = { 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5 };
  int len(_countof(data));
        
  cout << endl << "Sum of squares = " << sumarray(data, len, squared);
  cout << endl << "Sum of cubes = " << sumarray(data, len, cubed);
  cout << endl;
  return 0;
}
        
// Function for a square of a value
double squared(double x)
{
  return x*x;
}
        
// Function for a cube of a value
double cubed(double x)
{
  return x*x*x;
}
        
// Function to sum functions of array elements
double sumarray(double data[], int len, double (*pfun)(double))
{
  double total(0.0);                   // Accumulate total in here
        
  for(int i = 0; i < len; i++)
    total += pfun(data[i]);
        
  return total;
}