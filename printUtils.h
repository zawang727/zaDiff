#include <iostream>
#include <studio.h>
using namespace std;

class printOptions
{
public:
	printOptions() = default;
	~printOptions() = default;
	bool setFileName(string str);
	bool setFolderName(string str);
	
private:
	string fileName = "za.df";
	string folderName = "./";
}

class diffInfo
{
public:
	diffInfo() = default;
	~diffInfo() = default;
	string firstFileName;
	string firstFolderName;
	string secondFileName;
	string secondFolderName;
	map<pair<unsigned int, unsigned int>, vector<string> firstFileDiff;
	map<pair<unsigned int, unsigned int>, vector<string> secondFileDiff;
	bool swapFirstAndSecondFiles();
}
//can be strategy pattern
class mergedPrint
{
	
}

class firstFilePrint
{
}

class secondFilePrint
{
	
}