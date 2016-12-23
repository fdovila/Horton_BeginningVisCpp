// Ex10_11.cpp Using an array storing tuple objects
#include <array>
#include <tuple>
#include <string>
#include <iostream>
#include <iomanip>
        
using std::get;
using std::cout;
using std::endl;
using std::setw;
using std::string;
        
const size_t maxRecords(100);
typedef std::tuple<int, string, string, int> Record;
typedef std::array<Record, maxRecords> Records;
        
// Lists the contents of a Records array
void listRecords(const Records& people)
{
  const size_t ID(0), firstname(1), secondname(2), age(3);
  cout << std::setiosflags(std::ios::left);
  Record empty;
  for(auto& record : people)
  {
    if(record == empty) break;            // In case array is not full
    cout << "ID: " << setw(6)    << get<ID>(record)  
         << "Name: " << setw(25) << (get<firstname>(record) + " " + get<secondname>(record))
         << "Age: " << setw(5)   << get<age>(record)
         << endl;
  }
}
        
int main()
{
  Records personnel = {Record(1001, "Arthur", "Dent", 35),
                       Record(1002, "Mary", "Poppins", 55),
                       Record(1003, "David", "Copperfield", 34),
                       Record(1004, "James", "Bond", 44)};
  personnel[4] = std::make_tuple(1005, "Harry", "Potter", 15);
  personnel.at(5) = Record(1006, "Bertie", "Wooster", 28);
        
  listRecords(personnel);
  return 0;
}
