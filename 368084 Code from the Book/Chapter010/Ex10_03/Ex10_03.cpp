// Ex10_03.cpp
// Storing pointers to objects in a vector

#include <iostream>
#include <vector>
#include <memory>
#include "Person.h" 

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

int main()
{
   vector<unique_ptr<Person>> people;               // Vector of Person object pointers
  const size_t maxlength(50);
  char firstname[maxlength];
  char secondname[maxlength];
  while(true)
  {
    cout << "Enter a first name or press Enter to end: ";
    cin.getline(firstname, maxlength, '\n'); 
    if(strlen(firstname) == 0)
      break;
    cout << "Enter the second name: ";
    cin.getline(secondname, maxlength, '\n'); 
    auto pPerson = unique_ptr<Person>(new Person(firstname, secondname));
    people.push_back(std::move(pPerson));
    //people.push_back(unique_ptr<Person>(new Person(firstname, secondname)));
    pPerson->showPerson();
  }

  // Output the contents of the vector
  cout << endl;
  for(auto& p : people)
    p->showPerson();

  cout << endl << " and again..." << endl;
  for(auto& p : people)
    p->showPerson();
  // Pointers in the people vector are now invalid
  // so remove the contents
  people.clear();

  return 0;

  //vector<shared_ptr<Person>> people;           // Vector of Person object pointers
  //const size_t maxlength(50);
  //char firstname[maxlength];
  //char secondname[maxlength];
  //while(true)
  //{
  //  cout << "Enter a first name or press Enter to end: ";
  //  cin.getline(firstname, maxlength, '\n'); 
  //  if(strlen(firstname) == 0)
  //    break;
  //  cout << "Enter the second name: ";
  //  cin.getline(secondname, maxlength, '\n'); 
  //  people.push_back(make_shared<Person>(firstname, secondname));
  //}

  //// Output the contents of the vector
  //cout << endl;
  //for(auto p : people)
  //  p->showPerson();
  //
  //cout << endl << " and again..." << endl;
  //for(auto& p : people)
  //  p->showPerson();

  //people.clear();                                 // Clear the vector
  //return 0;
}
