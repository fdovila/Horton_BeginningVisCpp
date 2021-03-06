#pragma once
#include "element.h"
class CLine :
  public CElement
{
public:
  virtual ~CLine(void);
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;    // Function to display a line
  virtual void Move(const CSize& aSize) override;                                      // Function to move an element
  // Constructor for a line object
  CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int penWidth);

protected:
  CPoint m_EndPoint;                                                                   // End point of line

protected:
  CLine(void);                                                                         // Default constructor should not be used
};

