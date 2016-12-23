// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"


// CElement

CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, const int penWidth) :
  m_StartPoint(start), m_PenWidth(penWidth), m_Color(color){}

CElement::~CElement()
{
}


// CElement member functions
