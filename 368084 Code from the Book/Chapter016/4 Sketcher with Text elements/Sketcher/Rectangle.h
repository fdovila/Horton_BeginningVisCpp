#pragma once
#include "element.h"
class CRectangle :
  public CElement
{
public:
  virtual ~CRectangle(void);
 virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;  // Function to display a rectangle
  virtual void Move(const CSize& aSize) override;                                   // Function to move an element

 
 CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth);   // Constructor for a rectangle object

protected:
  CPoint m_BottomRight;                                                              // Bottom-right point for the rectangle
  CRectangle(void);                                                                  // Default constructor - should not be used
};

