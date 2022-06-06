#include <iostream>
#include <map>
#include <functional>
using namespace std;

typedef pair<int, int> regionDiff;
auto regionDiffCmp = [](const regionDiff& a, const regionDiff& b)
{ 
	if(abs(a.first) == abs(b.first)) return (a.first<0);
	return abs(a.first) < abs(b.first); 
};
//typedef map<regionDiff, vector<string>, regionDiffCmp> fileDiff;

//-------------------------------------------------
//Here the regionDiff type pair<int,int> is the diff region negative means this line or  
//character upper, and positive means line or charactor downward
//-------------------------------------------------
class diffInfo
{
public:
	diffInfo() = default;
	~diffInfo() = default;
	map<regionDiff, vector<string>, decltype(regionDiffCmp)> firstFileDiff;
	map<regionDiff, vector<string>, decltype(regionDiffCmp)> secondFileDiff;

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
	virtual bool setDiffInfo(diffInfo& diff) = 0;
	bool setOutputFileFolder(string str);
	bool setOutputFileName(string str);
protected:
	string outputFileFolder = "./";
	string outputFileName = "za.df";  
	diffInfo& _diffInfo;
};

class mergedDiffPrint: public diffPrinter
{
public:
	mergedDiffPrint() = default;
	~mergedDiffPrint() = default;
	bool printConsole() override;
	bool printToFile() override;
	bool setDiffInfo(diffInfo& diff) override;
};

class singleFileDiffPrint: public diffPrinter
{
public:
	singleFileDiffPrint() = default;
	~singleFileDiffPrint() = default;
	bool printConsole() override;
	bool printToFile() override;
	bool setDiffInfo(diffInfo& diff) override;
	void setFileIndex(int index);
	void setOriginalContents(vector<string>& str);
private:
	int fileIndex = 0;
	vector<string>& originalContents;
};

std::vector<std::string> split_string(const std::string& str,
                                      const std::string delimiter);

