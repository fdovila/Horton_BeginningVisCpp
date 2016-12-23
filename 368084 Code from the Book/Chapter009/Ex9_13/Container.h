// Container.h for Ex9_10
#pragma once
#include <iostream>
        
class CContainer        // Generic base class for specific containers
{
  public:
    // Function for calculating a volume - no content
    // This is defined as a 'pure' virtual function, signified by '= 0'
    virtual double Volume() const = 0;
        
    // Function to display a volume
    virtual void ShowVolume() const
    {
      std::cout << std::endl << "Volume is " << Volume();
    }

    virtual ~CContainer()
    { std::cout << "CContainer destructor called" << std::endl; }
};
