// Ex8_04.cpp
// Implementing the comparison operators
#include <iostream>                    // For stream I/O
#include <utility>                     // For operator overload templates
using std::cout;
using std::endl;
using namespace std::rel_ops;
        
class CBox                             // Class definition at global scope
{
  public:
    // Constructor definition
    explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0):
                            m_Length(lv), m_Width(wv), m_Height(hv)
    {
      cout << endl << "Constructor called.";
    }
        
    // Function to calculate the volume of a box
    double Volume() const
    {
      return m_Length*m_Width*m_Height;
    }
        
    // Operator function for 'less than' that
    // compares volumes of CBox objects.
    bool operator<(const CBox& aBox) const
    {
      return this->Volume() < aBox.Volume();
    }

    // 'Less than' operator function to compare a CBox object volume with a constant
    bool operator<(const double& value) const
    {
      return this->Volume() < value;
    }

    // 'Greater than' function to compare a CBox object volume with a constant
    bool operator>(const double& value) const
    {
      return this->Volume() > value;
    }
        
    // Overloaded equality operator
    bool operator==(const CBox& aBox) const
    {
      return this->Volume() == aBox.Volume();
    }
        
    // Destructor definition
    ~CBox()
    { cout << "Destructor called." << endl;}
        
  private:
    double m_Length;                   // Length of a box in inches
    double m_Width;                    // Width of a box in inches
    double m_Height;                   // Height of a box in inches
};
        
// Function comparing a constant with a CBox object
inline bool operator<(const double& value, const CBox& aBox)
{
  return value < aBox.Volume();
}
        
int main()
{
  CBox smallBox(4.0, 2.0, 1.0);
  CBox mediumBox(10.0, 4.0, 2.0);
  CBox otherBox(2.0, 1.0, 4.0);

  if(mediumBox != smallBox)
    cout << endl << "mediumBox is not equal to smallBox";
       
  if(mediumBox > smallBox)
    cout << endl << "mediumBox is bigger than smallBox";
  else
    cout << endl << "mediumBox is not bigger than smallBox";

  if(otherBox >= smallBox)
    cout << endl << "otherBox is greater than or equal to smallBox";
  else
    cout << endl << "otherBox is smaller than smallBox";

  if(otherBox >= mediumBox)
    cout << endl << "otherBox is greater than or equal to mediumBox";
  else
    cout << endl << "otherBox is smaller than mediumBox";
    
  if(mediumBox > 50.0)
    cout << endl << "mediumBox capacity is more than 50";
  else
    cout << endl << "mediumBox capacity is not more than 50";

  if(10.0 < smallBox)
    cout << endl << "smallBox capacity is more than 10";
  else
    cout << endl << "smallBox capacity is not more than 10";
        
  cout << endl;
  return 0;
}
