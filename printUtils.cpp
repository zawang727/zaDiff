#include "printUtils.h"
#include "programOptions.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>

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
	cout << "First file is:" << _diffInfo.firstFolderName.c_str() 
	<< _diffInfo.firstFileName.c_str() << endl;
	cout << "Second file is:" << _diffInfo.secondFolderName.c_str() 
	<< _diffInfo.secondFileName.c_str() << endl;

	auto bDiff = _diffInfo.secondFileDiff.begin();
	for(auto& i: _diffInfo.firstFileDiff)
	{
		cout << "First file line " << abs(i.first.first) << " to " 
		<< abs(i.first.second) << "." << endl;
		for(auto &j : i.second)
		{
			cout << j.c_str() << endl;
		}
		cout << "Second file line " << abs(bDiff->first.first) << " to " 
		<< abs(bDiff->first.second) << "." << endl;
		for(auto &j : bDiff->second)
		{
			cout << j.c_str() << endl;
		}
		cout << "---------------------------------------" << endl;
		++bDiff;
	}
	return true;
}

bool mergedDiffPrint::printToFile()
{
	string filePrint;

	if(_diffInfo.firstFileDiff.size() != _diffInfo.secondFileDiff.size()) 
	{
		filePrint += "Error in data\n";
		return false;
	}
	filePrint += "First file is:";
	filePrint += _diffInfo.firstFolderName;
	filePrint += _diffInfo.firstFileName;
	filePrint += "\n";
	filePrint += "Second file is:";
	filePrint += _diffInfo.secondFolderName;
	filePrint += _diffInfo.secondFileName;
	filePrint += "\n";

	auto bDiff = _diffInfo.secondFileDiff.begin();
	for(auto& i: _diffInfo.firstFileDiff)
	{
		filePrint += "First file line ";
		filePrint += to_string(abs(i.first.first));
		filePrint += " to ";
		filePrint += to_string(abs(i.first.second));
		filePrint += ".\n";
		for(auto &j : i.second)
		{
			filePrint += j;
			filePrint += "\n";
		}
		filePrint += "Second file line ";
		filePrint += to_string(abs(i.first.first));
		filePrint += " to ";
		filePrint += to_string(abs(i.first.second));
		filePrint += ".\n";
		for(auto &j : bDiff->second)
		{
			filePrint += j;
			filePrint += "\n";
		}
		filePrint += "---------------------------------------\n";
		++bDiff;
	}

	std::ofstream ofs((this->outputFileFolder+this->outputFileName).c_str(),
	std::ofstream::out);

	if(ofs)
	{
		ofs << filePrint;
		ofs.close();
		return true;
	}
	ofs.close();
	return false;
}

bool mergedDiffPrint::setDiffInfo(diffInfo diff)
{
	_diffInfo = diff;
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

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));
    return strings;
}