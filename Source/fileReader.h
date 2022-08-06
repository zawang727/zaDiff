#pragma once
#include <iostream>
#include <vector>

using namespace std;

class fileReader
{
public:
  fileReader() = default;
  ~fileReader() = default;
  bool read();
  bool setFilePath(string str);
  string& getContents()
  {
    return this->contents;
  } 
private:
  string filePath;
  string contents;
};
