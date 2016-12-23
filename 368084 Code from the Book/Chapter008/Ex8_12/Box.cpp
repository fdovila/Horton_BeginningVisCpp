#include "Box.h"

// Constructor
CBox::CBox(double lv, double wv, double hv) : m_Height(hv)
{
  if(lv < 0.0 || wv < 0.0 || hv < 0.0)
    throw "Negative dimension specified for CBox object.";

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


CBox::~CBox(void)
{
}

// Less-than operator for CBox objects
bool CBox::operator<(const CBox& aBox) const
{
  return Volume() < aBox.Volume();
}

// Equality comparison for CBox objects
bool CBox::operator==(const CBox& aBox) const
{
  return Volume() == aBox.Volume();
}

// Returns the volume of a CBox object
double CBox::Volume(void) const
{
     return m_Length*m_Width*m_Height;
}

// Addition  operator for CBox objects
CBox CBox::operator+(const CBox& aBox) const
{
  // New object has larger length and width of the two,
  // and sum of the two heights
  return CBox(m_Length > aBox.m_Length ? m_Length : aBox.m_Length,
              m_Width > aBox.m_Width ? m_Width : aBox.m_Width,
              m_Height + aBox.m_Height);
}

// Multiply  operator for CBox objects
CBox CBox::operator*(int n) const
{
  if(n % 2)
    return CBox(m_Length, m_Width, n*m_Height);            // n odd
  else
    return CBox(m_Length, 2.0*m_Width, (n/2)*m_Height);    // n even
}

// Division  operator for CBox objects
int CBox::operator/(const CBox& aBox) const
{
  // Number of boxes in horizontal plane this way
  int tc1 = static_cast<int>((m_Length / aBox.m_Length))*static_cast<int>((m_Width / aBox.m_Width));

  // Number of boxes in horizontal plane that way
  int tc2 = static_cast<int>((m_Length / aBox.m_Width))*static_cast<int>((m_Width / aBox.m_Length));
       
  //Return best fit
  return static_cast<int>((m_Height/aBox.m_Height)*(tc1 > tc2 ? tc1 : tc2));
}
