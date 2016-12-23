// BoxOperators.h
// CBox object operations that don't need to access private members
#pragma once
#include "Box.h"
        
// Function for testing if a constant is > a CBox object
inline bool operator>(const double& value, const CBox& aBox)
{ return value > aBox.Volume(); }
        
// Function for testing if a constant is < CBox object
inline bool operator<(const double& value, const CBox& aBox)
{ return value < aBox.Volume(); }
        
// Function for testing if CBox object is > a constant
inline bool operator>(const CBox& aBox, const double& value)
{ return aBox.Volume() > value; }
        
// Function for testing if CBox object is < a constant
inline bool operator<( const CBox& aBox, const double& value)
{ return aBox.Volume() < value; }
        
// Function for testing if a constant is >= a CBox object
inline bool operator>=(const double& value, const CBox& aBox)
{ return value >= aBox.Volume(); }
        
// Function for testing if a constant is <= CBox object
inline bool operator<=(const double& value, const CBox& aBox)
{ return value <= aBox.Volume(); }
        
// Function for testing if CBox object is >= a constant
inline bool operator>=( const CBox& aBox, const double& value)
{ return aBox.Volume() >= value; }
        
// Function for testing if CBox object is <= a constant
inline bool operator<=( const CBox& aBox, const double& value)
{ return aBox.Volume() <= value; }
        
// Function for testing if a constant is == CBox object
inline bool operator==(const double& value, const CBox& aBox)
{ return value == aBox.Volume(); }
        
// Function for testing if CBox object is == a constant
inline bool operator==(const CBox& aBox, const double& value)
{ return aBox.Volume() == value; }
        
// CBox multiply operator n*aBox
inline CBox operator*(int n, const CBox& aBox)
{ return aBox * n; }
        
// Operator to return the free volume in a packed CBox
inline double operator%( const CBox& aBox, const CBox& bBox)
{ return aBox.Volume() - (aBox / bBox) * bBox.Volume(); }
