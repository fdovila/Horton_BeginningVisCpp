// Header file CandyBox.h in project Ex9_02
#pragma once
#include <cstring>                                         // For strlen() and strcpy()
#include "Box.h"

class CCandyBox: public CBox
{
  public:
    char* m_Contents;

    explicit CCandyBox(const char* str = "Candy")          // Constructor
    {
      m_Contents = new char[ strlen(str) + 1 ];
      strcpy_s(m_Contents, strlen(str) + 1, str);
    }

    ~CCandyBox()                                           // Destructor
    { delete[] m_Contents; };
};
