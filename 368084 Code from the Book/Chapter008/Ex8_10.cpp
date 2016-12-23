// Ex8_10.cpp
// Using a class template
#include <iostream>
#include <utility>                          // For operator overload templates
using std::cout;
using std::endl;
using std::move;
using namespace std::rel_ops;
        
class CBox                                  // Class definition at global scope
{
  public:
    // Constructor definition
    explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0): m_Height(hv)
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
    bool CBox::operator==(const CBox& aBox) const
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
    double m_Length;                        // Length of a box in inches
    double m_Width;                         // Width of a box in inches
    double m_Height;                        // Height of a box in inches
};
        
// CSamples class template definition
template <class T> class CSamples
{
  public:
    // Constructors
    CSamples(const T values[], int count);
    CSamples(const T& value);
    CSamples(T&& value);
    CSamples() : m_Free(0) {}
        
    bool Add(const T& value);               // Insert a value
    bool Add(T&& value);                    // Insert a value with mve semantics
    T Max() const;                          // Calculate maximum
        
  private:
    static const size_t maxSamples = 100;   // Maximum number od sample
    T m_Values[maxSamples];                 // Array to store samples
    int m_Free;                             // Index of free location in m_Values
};

// Constructor template definition to accept an array of samples
template<class T> CSamples<T>::CSamples(const T values[], int count)
{
  m_Free = count < maxSamples ? count : maxSamples;       // Don't exceed the array
  for(int i = 0; i < m_Free; i++)
    m_Values[i] = values[i];                // Store count number of samples
}
        
// Constructor to accept a single sample
template<class T> CSamples<T>::CSamples(const T& value)
{
  m_Values[0] = value;                      // Store the sample
  m_Free = 1;                               // Next is free
}
        
// Constructor to accept a temporary sample
template<class T> CSamples<T>::CSamples(T&& value)
{
  cout << "Move constructor." << endl;
  m_Values[0] = move(value);                // Store the sample
  m_Free = 1;                               // Next is free
}
        
// Function to add a sample
template<class T> bool CSamples<T>::Add(const T& value)
{
  cout << "Add." << endl;
  bool OK = m_Free < maxSamples;                   // Indicates there is a free place
  if(OK)
    m_Values[m_Free++] = value;             // OK true, so store the value
  return OK;
}
        
template<class T> bool CSamples<T>::Add(T&& value)
{
  cout << "Add move." << endl;
  bool OK = m_Free < maxSamples;                   // Indicates there is a free place
  if(OK)
    m_Values[m_Free++] = move(value);       // OK true, so store the value
  return OK;
}
 
// Function to obtain maximum sample
template<class T> T CSamples<T>::Max() const
{
  T theMax = m_Values[0];                   // Set first sample as maximum
  for(int i = 1; i < m_Free; i++)           // Check all the samples
    if(theMax < m_Values[i])
      theMax = m_Values[i];                 // Store any larger sample
  return theMax;
}
        
int main()
{
  CBox boxes[] = {                          // Create an array of boxes
                   CBox(8.0, 5.0, 2.0),     // Initialize the boxes...
                   CBox(5.0, 4.0, 6.0),
                   CBox(4.0, 3.0, 3.0)
                 };
        
  // Create the CSamples object to hold CBox objects
  CSamples<CBox> myBoxes(boxes, _countof(boxes));
        
  CBox maxBox = myBoxes.Max();              // Get the biggest box
  cout << endl                              // and output its volume
       << "The biggest box has a volume of "
       << maxBox.Volume()
       << endl  << endl;

  CSamples<CBox> moreBoxes(CBox(8.0, 5.0, 2.0));
  moreBoxes.Add(CBox(5.0, 4.0, 6.0));
  moreBoxes.Add(CBox(4.0, 3.0, 3.0));
  cout << "The biggest box has a volume of "
       << moreBoxes.Max().Volume()
       << endl;
  return 0;
}
