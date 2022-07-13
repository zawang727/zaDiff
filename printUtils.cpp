#include "printUtils.h"
#include "programOptions.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "fileReader.h"

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
	if(_diffInfo->firstFileDiff.size() != _diffInfo->secondFileDiff.size()) return false;
	cout << "First file is:" << _diffInfo->getFolderName(1).c_str() << "\\"
	<< _diffInfo->getFileName(1).c_str() << endl;
	cout << "Second file is:" << _diffInfo->getFolderName(2).c_str() << "\\"
	<< _diffInfo->getFileName(2).c_str() << endl;

	auto bDiff = _diffInfo->secondFileDiff.begin();
	for(auto& i: _diffInfo->firstFileDiff)
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

	if(_diffInfo->firstFileDiff.size() != _diffInfo->secondFileDiff.size()) 
	{
		filePrint += "Error in data\n";
		return false;
	}
	filePrint += "First file is:";
	filePrint += _diffInfo->getFolderName(1);
	filePrint += _diffInfo->getFileName(1);
	filePrint += "\n";
	filePrint += "Second file is:";
	filePrint += _diffInfo->getFolderName(2);
	filePrint += _diffInfo->getFileName(2);
	filePrint += "\n";

	auto bDiff = _diffInfo->secondFileDiff.begin();
	for(auto& i: _diffInfo->firstFileDiff)
	{
		filePrint += "First file line ";
		filePrint += to_string(abs(i.first.first));
		filePrint += (i.first.first>0)? " Upper" : " Downward";
		filePrint += " to ";
		filePrint += to_string(abs(i.first.second));
		filePrint += (i.first.second>0)? " Upper" : " Downward";
		filePrint += ".\n";
		for(auto &j : i.second)
		{
			filePrint += j;
			filePrint += "\n";
		}
		filePrint += "Second file line ";
		filePrint += to_string(abs(bDiff->first.first));
		filePrint += (bDiff->first.first>0)? " Upper" : " Downward";
		filePrint += " to ";
		filePrint += to_string(abs(bDiff->first.second));
		filePrint += (bDiff->first.second>0)? " Upper" : " Downward";
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

bool mergedDiffPrint::setDiffInfo(diffInfo* diff)
{
	_diffInfo = diff;
	return true;
}

bool singleFileDiffPrint::printConsole()
{
	if(fileIndex != 1 && fileIndex != 2)
	{
		cout<<"File index unset\n";
		return false;
	}
 	bool isInADiff =false;
	auto diffIterThis = (fileIndex==2)? _diffInfo->secondFileDiff.begin():_diffInfo->firstFileDiff.begin();
	auto diffIterAnother = (fileIndex==1)? _diffInfo->secondFileDiff.begin():_diffInfo->firstFileDiff.begin();

	for(unsigned int i = 0; i < originalContents->size(); ++i)
	{
		if(-(diffIterThis->first.second) == static_cast<int>(i+1) && isInADiff)
		{
			cout << "---------------------------------------" << endl;
			isInADiff = false;
			diffIterThis++;
			diffIterAnother++;
		}
		if(-(diffIterThis->first.first) == static_cast<int>(i+1) && !isInADiff)
		{
			cout << "---------------------------------------" << endl;
			cout << "This file line " << abs(diffIterThis->first.first) 
			<< ((diffIterThis->first.first>0)? " Upper" : " Downward") << " to " 
			<< abs(diffIterThis->first.second) << ((diffIterThis->first.second>0)? " Upper" : " Downward") << ".\n";
			cout << "Another file line " << abs(diffIterAnother->first.first) 
			<< ((diffIterAnother->first.first>0)? " Upper" : " Downward") << " to " 
			<< abs(diffIterAnother->first.second) << ((diffIterAnother->first.second>0)? " Upper" : " Downward") << ".\n";
			isInADiff = true;
		}
		cout<< (*originalContents)[i+1].c_str() << endl;
		if((diffIterThis->first.second) == static_cast<int>(i+1) && isInADiff)
		{
			cout << "---------------------------------------" << endl;
			isInADiff = false;
			diffIterThis++;
			diffIterAnother++;
		}
		if((diffIterThis->first.first) == static_cast<int>(i+1) && !isInADiff)
		{
			cout << "---------------------------------------" << endl;
			cout << "This file line " << abs(diffIterThis->first.first) 
			<< ((diffIterThis->first.first>0)? " Upper" : " Downward") << " to " 
			<< abs(diffIterThis->first.second) << ((diffIterThis->first.second>0)? " Upper" : " Downward") << ".\n";
			cout << "Another file line " << abs(diffIterAnother->first.first) 
			<< ((diffIterAnother->first.first>0)? " Upper" : " Downward") << " to " 
			<< abs(diffIterAnother->first.second) << ((diffIterAnother->first.second>0)? " Upper" : " Downward") << ".\n";
			isInADiff = true;
		}
	}
	cout << "---------------------------------------" << endl;
	return true;
}

bool singleFileDiffPrint::printToFile()
{
	string filePrint;

	if(fileIndex != 1 && fileIndex != 2)
	{
		cout<<"File index unset\n";
		return false;
	}

 	bool isInADiff =false;
	auto diffIterThis = (fileIndex==2)? _diffInfo->secondFileDiff.begin():_diffInfo->firstFileDiff.begin();
	auto diffIterAnother = (fileIndex==1)? _diffInfo->secondFileDiff.begin():_diffInfo->firstFileDiff.begin();

	for(unsigned int i = 0; i < originalContents->size(); ++i)
	{
		if(-(diffIterThis->first.second) == static_cast<int>(i+1) && isInADiff)
		{
			filePrint += "---------------------------------------\n";
			isInADiff = false;
			diffIterThis++;
			diffIterAnother++;
		}
		if(-(diffIterThis->first.first) == static_cast<int>(i+1) && !isInADiff)
		{
			filePrint += "---------------------------------------\n";
			filePrint += "This file line ";
			filePrint += to_string(abs(diffIterThis->first.first));
			filePrint += ((diffIterThis->first.first>0)? " Upper" : " Downward");
			filePrint += " to ";
			filePrint += to_string(abs(diffIterThis->first.second));
			filePrint += ((diffIterThis->first.second>0)? " Upper.\n" : " Downward.\n");
			filePrint += "Another file line ";
			filePrint += to_string(abs(diffIterAnother->first.first));
			filePrint += ((diffIterAnother->first.first>0)? " Upper to " : " Downward to ");
			filePrint += to_string(abs(diffIterAnother->first.second));
			filePrint += ((diffIterAnother->first.second>0)? " Upper.\n" : " Downward.\n");
			isInADiff = true;
		}
		cout<< (*originalContents)[i+1].c_str() << endl;
		if((diffIterThis->first.second) == static_cast<int>(i+1) && isInADiff)
		{
			filePrint += "---------------------------------------\n";
			isInADiff = false;
			diffIterThis++;
			diffIterAnother++;
		}
		if((diffIterThis->first.first) == static_cast<int>(i+1) && !isInADiff)
		{
			filePrint += "---------------------------------------\n";
			filePrint += "This file line ";
			filePrint += to_string(abs(diffIterThis->first.first));
			filePrint += ((diffIterThis->first.first>0)? " Upper" : " Downward");
			filePrint += " to ";
			filePrint += to_string(abs(diffIterThis->first.second));
			filePrint += ((diffIterThis->first.second>0)? " Upper.\n" : " Downward.\n");
			filePrint += "Another file line ";
			filePrint += to_string(abs(diffIterAnother->first.first));
			filePrint += ((diffIterAnother->first.first>0)? " Upper to " : " Downward to ");
			filePrint += to_string(abs(diffIterAnother->first.second));
			filePrint += ((diffIterAnother->first.second>0)? " Upper.\n" : " Downward.\n");
			isInADiff = true;
		}
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

bool singleFileDiffPrint::setDiffInfo(diffInfo* diff)
{
	_diffInfo = diff;
	return true;
}

void singleFileDiffPrint::setFileIndex(int index)
{
	fileIndex = index;
}

void singleFileDiffPrint::setOriginalContents(vector<string>* str)
{
	originalContents = str;
}

std::vector<std::string> split_string(const std::string& str,
                                      const std::string delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    strings.push_back(str.substr(prev));
    return strings;
}