#include <iostream>
#include <map>
#include <vector>
#include <functional>
using namespace std;

typedef pair<int, int> regionDiff;

struct regionDiffCmp 
{
	bool operator()(const regionDiff& a, const regionDiff& b) const {
		if(abs(a.first) == abs(b.first)) return (bool)(a.first<0);
		return (bool)(abs(a.first) < abs(b.first)); 
	}
};

//-------------------------------------------------
//Here the regionDiff type pair<int,int> is the diff region negative means this line or  
//character upper, and positive means line or charactor downward
//-------------------------------------------------
class diffInfo
{
public:
	diffInfo() = default;
	~diffInfo() = default;
	map<regionDiff, vector<string>, regionDiffCmp> firstFileDiff;
	map<regionDiff, vector<string>, regionDiffCmp> secondFileDiff;

	bool swapFirstAndSecondFiles()
	{
		swap(firstFileName, secondFileName);
		swap(firstFolderName, secondFolderName);
		map<regionDiff, vector<string>, regionDiffCmp> buffer = firstFileDiff;
		firstFileDiff = secondFileDiff;
		secondFileDiff = buffer;
		return true;
	}

	string firstFileName;
	string firstFolderName;
	string secondFileName;
	string secondFolderName;
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

class getPrinter
{
public:
	getPrinter() = default;
	~getPrinter() = default;
	diffPrinter* getDiffPrinter(); 
};

std::vector<std::string> split_string(const std::string& str,
                                      const std::string delimiter);

