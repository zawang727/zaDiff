#include <iostream>
#include <string>
#include "programOptions.h"
#include "fileReader.h"
#include "fileDiffSolver.h"
#include "printUtils.h"
#include "lineDiff.h"

int main()
{
	lineDiff _lineDiff;
	_lineDiff.execute(string("aabacd566"),string("adbaabca5668"));

	std::cout<<"hello world\n";
	string firstFileName = "1.txt";
	string firstFolderName = "C:\\Users\\Jennan Wang\\Desktop\\zaDiff\\testcases\\simpleSameLineNumber";
	string secondFileName = "2.txt";
	string secondFolderName = "C:\\Users\\Jennan Wang\\Desktop\\zaDiff\\testcases\\simpleSameLineNumber";
	fileReader reader1;
	reader1.setFilePath(firstFolderName + "\\" + firstFileName);
	reader1.read();
	std::string& readString1 = reader1.getContents();
	vector<string> contents1 = split_string(readString1, "\n");
	fileReader reader2;
	reader2.setFilePath(secondFolderName + "\\" + secondFileName);
	reader2.read();
	std::string& readString2 = reader2.getContents();
	vector<string> contents2 = split_string(readString2, "\n");
	
	fileDiffSolverFactory _fileDiffSolverFactory;
	fileDiffSolver* _fileDiffSolver = _fileDiffSolverFactory.getFileDiffSolver(contents1, contents2);
	_fileDiffSolver->setContents(contents1,1);
	_fileDiffSolver->setContents(contents2,2);
	_fileDiffSolver->setFirstFileName(firstFileName);
	_fileDiffSolver->setFirstFolderName(firstFolderName);
	_fileDiffSolver->setSecondFileName(secondFileName);
	_fileDiffSolver->setSecondFolderName(secondFolderName);
	diffInfo result = _fileDiffSolver->solve();
	mergedDiffPrint _mergedDiffPrint;
	_mergedDiffPrint.setDiffInfo(&result);
	_mergedDiffPrint.printConsole();
	_mergedDiffPrint.printToFile();
	system("pause");
	return 0; 
};