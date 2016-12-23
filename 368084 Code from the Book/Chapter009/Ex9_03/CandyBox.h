// CandyBox.h in Ex9_03
#pragma once
#include <cstring>                               // For strlen() and strcpy()
#include <iostream>
#include "Box.h"

class CCandyBox: public CBox
{
  public:
    char* m_Contents;

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
    { delete[] m_Contents; }
};
