#include <iostream>
#include <vector>
#include "printUtils.h"

using namespace std;

class fileReader
{
public:
  fileReader() = default;
  ~fileReader() = default;
  
private:
  string filePath;
  vector<string> contents;
};
