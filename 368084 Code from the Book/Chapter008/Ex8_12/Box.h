#pragma once
#include <utility>
#include <algorithm>                                  // For max() & min() functions
using namespace std::rel_ops;

class CBox
{
public:
 explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0);
 ~CBox(void);

private:
  double m_Length;
  double m_Width;
  double m_Height;
public:
  bool operator<(const CBox& aBox) const;
  bool operator==(const CBox& aBox) const;
  double Volume(void) const;

  double GetLength() const { return m_Length; }
  double GetWidth() const { return m_Width; }
  double GetHeight() const { return m_Height; }

  CBox operator+(const CBox& aBox) const;             // Addition  operator for CBox objects
  CBox operator*(int n) const;                        // Multiply  operator for CBox objects
  int operator/(const CBox& aBox) const;              // Division  operator for CBox objects
};

