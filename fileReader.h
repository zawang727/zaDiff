#include <iostream>
#include <vector>
#include "printUtils.h"

using namespace std;

class fileReader
{
public:
  fileReader() = default;
  ~fileReader() = default;
  bool read();
  bool setFilePath(string str);
private:
  string filePath;
  string contents;
};
