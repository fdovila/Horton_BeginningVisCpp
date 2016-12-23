// Ex8_06.cpp
// Adding CBox objects
#include <iostream>                    // For stream I/O
#include <utility>                     // For operator overload templates
using std::cout;
using std::endl;
using namespace std::rel_ops;
        
class CBox                             // Class definition at global scope
{
  public:
    // Constructor definition
    explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) : m_Height(hv)
    {
      m_Length = std::max(lv, wv);
      m_Width = std::min(lv, wv);

      // Length is now greater than or equal to width 
      if(m_Height > m_Length)
      {
        m_Height = m_Length;
        m_Length = hv;

        // m_Height is still greater than m_Width so swap them
        double temp = m_Width;
        m_Width = m_Height;
        m_Height = temp;
      }
      else if( m_Height > m_Width)
      {
        m_Height = m_Width;
        m_Width = hv;
      }
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

    // Function to add two CBox objects
    CBox operator+(const CBox& aBox) const
    {
      // New object has larger length & width, and sum of heights
      return CBox(m_Length > aBox.m_Length ? m_Length : aBox.m_Length,
                  m_Width > aBox.m_Width   ?  m_Width : aBox.m_Width,
                  m_Height + aBox.m_Height);
    }

    // Function to show the dimensions of a box
    void ShowBox() const
    {
      cout << m_Length << " " << m_Width  << " " << m_Height << endl;
    }
        
  private:
    double m_Length;                   // Length of a box in inches
    double m_Width;                    // Width of a box in inches
    double m_Height;                   // Height of a box in inches
};
        
// Function comparing a constant with a CBox object
inline bool operator>(const double& value, const CBox& aBox)
{
  return value > aBox.Volume();
}
        
int main()
{
  CBox smallBox(4.0, 2.0, 1.0);
  CBox mediumBox(10.0, 4.0, 2.0);
  CBox aBox;
  CBox bBox;

  cout << "smallBox dimensions are ";
  smallBox.ShowBox();

  cout << "mediumBox dimensions are ";
  mediumBox.ShowBox();


  aBox = smallBox + mediumBox;
  cout << "aBox = smallBox + mediumBox. Dimensions are ";
  aBox.ShowBox();

  bBox = aBox + smallBox + mediumBox;
  cout << "bBox = aBox + smallBox + mediumBox. Dimensions are ";
  bBox.ShowBox();

  return 0;
}
