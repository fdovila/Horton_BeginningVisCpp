// CandyBox.h in Ex9_04
#pragma once
#include "Box.h"
#include <cstring>                               // For strlen() and strcpy()
#include <iostream>

class CCandyBox: public CBox
{
  public:
    char* m_Contents;

    // Derived class function to calculate volume
    double Volume() const
    { return m_Length*m_Width*m_Height; }

    // Constructor to set dimensions and contents
    // with explicit call of CBox constructor
    explicit CCandyBox(double lv, double wv, double hv, const char* str = "Candy") : CBox(lv, wv, hv) 
    {
      std::cout << std::endl <<"CCandyBox constructor2 called";
      m_Contents = new char[ strlen(str) + 1 ];
      strcpy_s(m_Contents, strlen(str) + 1, str);
    }

    // Constructor to set contents
    // calls default CBox constructor automatically
    explicit CCandyBox(const char* str = "Candy")   
    {
      std::cout << std::endl << "CCandyBox constructor1 called";
      m_Contents = new char[ strlen(str) + 1 ];
      strcpy_s(m_Contents, strlen(str) + 1, str);
    }

    ~CCandyBox()                                 // Destructor
    {
      std::cout << "CCandyBox destructor called" << std::endl;
      delete[] m_Contents;
    }
};
