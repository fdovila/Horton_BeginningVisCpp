// GlassBox.h in Ex9_09
#pragma once
#include "Box.h"

class CGlassBox: public CBox           // Derived class
{
  public:
    // Function to calculate volume of a CGlassBox
    // allowing 15% for packing
    virtual double Volume() const override
    { return 0.85*m_Length*m_Width*m_Height; }

    // Constructor
    CGlassBox(double lv, double wv, double hv): CBox(lv, wv, hv){}
};
