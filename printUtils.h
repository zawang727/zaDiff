#include <iostream>
#include <map>
using namespace std;


//-------------------------------------------------
//Here the regionDiff type pair<int,int> is the diff region negative means this line or  
//character upper, and positive means line or charactor downward
//-------------------------------------------------
class diffInfo
{
public:
	diffInfo() = default;
	~diffInfo() = default;
	typedef pair<int, int> regionDiff;
	typedef map<regionDiff, vector<string>> lineDiff;
	typedef map<regionDiff, vector<lineDiff>> fileDiff; 
	fileDiff firstFileDiff;
	fileDiff secondFileDiff;

	bool swapFirstAndSecondFiles()
	{
		swap(firstFileName, secondFileName);
		swap(firstFolderName, secondFolderName);
		swap(firstFileDiff, secondFileDiff);
		return true;
	}

	string firstFileName;
	string firstFolderName;
	string secondFileName;
	string secondFolderName;
};

class getPrinter
{
public:
	getPrinter() = default;
	~getPrinter() = default;
	diffPrinter* getDiffPrinter(); 
};

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
	string outputFileFolder = "za.df";
	string outputFileName = "./";
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

