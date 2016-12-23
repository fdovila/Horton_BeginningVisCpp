#pragma once
#include "element.h"
#include <vector>

class CCurve :
  public CElement
{
DECLARE_SERIAL(CCurve)
public:
  virtual ~CCurve(void);
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;  // Function to display a curve
  virtual void Move(const CSize& aSize) override;                                    // Function to move an element
  CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penWidth);   // Constructor for a curve object
  void AddSegment(const CPoint& point);                                              // Add a segment to the curve
  virtual void Serialize(CArchive& ar) override;                                     // Serialize object

protected:
  std::vector<CPoint> m_Points;                                                      // Points defining the curve
  CCurve(void);                                                                      // Default constructor - should not be used
};


