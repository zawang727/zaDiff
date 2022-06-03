#include "printUtils.h"
#include "programOptions.h"
#include <fstream>
#include <vector>

using namespace std;
typedef pair<int, int> regionDiff;
typedef map<regionDiff, vector<string>> lineDiff;
typedef map<regionDiff, vector<lineDiff>> fileDiff;

diffPrinter* getPrinter::getDiffPrinter()
{
	diffPrinter* res = nullptr;
	programOptions &option = programOptions::getInstance();

	diffPrinterEnum printerType = option.diffPrinter;

	if(printerType = diffPrinterEnumDefault) printerType = diffPrinterEnumMerged; 

	switch (printerType)
	{
		case diffPrinterEnumMerged:
			res = new mergedDiffPrint();
			break;
		case diffPrinterEnumSingle:
			res = new singleFileDiffPrint();
			break;
		default:
			res = new mergedDiffPrint();
	}
	return res; 
} 

bool mergedDiffPrint::printConsole()
{
	if(_diffInfo.firstFileDiff.size() != _diffInfo.secondFileDiff.size()) return false;
	auto bDiff = _diffInfo.secondFileDiff.begin();
	for(auto& i: _diffInfo.firstFileDiff)
	{
		
		++bDiff;
	}
	return true;
}

bool mergedDiffPrint::printToFile()
{
	std::ofstream ofs ((this->outputFileFolder+this->outputFileName).c_str(),
	std::ofstream::out);

	return true;
}

bool mergedDiffPrint::setDiffInfo(diffInfo diff)
{
	return true;
}

bool singleFileDiffPrint::printConsole()
{
	return true;
}

bool singleFileDiffPrint::printToFile()
{

}

bool singleFileDiffPrint::setDiffInfo(diffInfo diff)
{

}

void singleFileDiffPrint::setFileIndex(int index)
{

}

void singleFileDiffPrint::setOriginalContents(string str)
{

}