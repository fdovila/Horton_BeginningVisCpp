#pragma once
#include "element.h"

class CCircle : public CElement
{
DECLARE_SERIAL(CCircle)
public:
  virtual ~CCircle(void);
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;  // Function to display a circle
  virtual void Move(const CSize& aSize) override;                                    // Function to move an element
  CCircle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth);     // Constructor for a circle object
  virtual void Serialize(CArchive& ar) override;                                     // Serialize object

protected:
  CPoint m_BottomRight;                                                              // Bottom-right point for defining rectangle
  CCircle(void);                                                                     // Default constructor - should not be used
};

