#include <iostream>
#include <map>
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
};

class diffInfo
{
public:
	diffInfo() = default;
	~diffInfo() = default;
	string firstFileName;
	string firstFolderName;
	string secondFileName;
	string secondFolderName;
	map<pair<unsigned int, unsigned int>, vector<string>> firstFileDiff;
	map<pair<unsigned int, unsigned int>, vector<string>> secondFileDiff;
	bool swapFirstAndSecondFiles();
};
//can be strategy pattern

class diffPrinter
{
public:
	diffPrinter() = default;
	virtual ~diffPrinter() = default;
	virtual bool printConsole() = 0;
	virtual bool printToFile() = 0;
	virtual bool setDiffInfo(diffInfo diff) = 0;
	bool setOutputFileFolder(string str);
	bool setoutputFileName(string str);
private:
	string outputFileFolder;
	string outputFileName;
	diffInfo _diffInfo;
};

class mergedDiffPrint: public diffPrinter
{
public:
	bool printConsole() override;
	bool printToFile() override;
	bool setDiffInfo(diffInfo diff) override;
};

class singleFileDiffPrint: public diffPrinter
{
public:
	bool printConsole() override;
	bool printToFile() override;
	bool setDiffInfo(diffInfo diff) override;
	void setFileIndex(int index);
	void setOriginalFile(string str);
private:
	int fileIndex = 0;
	string originalContents;
};

