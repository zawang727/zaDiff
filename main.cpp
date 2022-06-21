#include <iostream>
#include <string>
#include "programOptions.h"
#include "fileReader.h"
#include "fileDiffSolverByLine.h"
#include "printUtils.h"

int main()
{
	std::cout<<"hello world\n";
	fileReader reader;
	reader.setFilePath(std::string("C:\\Users\\Jennan Wang\\Desktop\\zaDiff\\zaDiff\\MAKEFILE_examaple"));
	reader.read();
	std::string& contents = reader.getContents();
	std::cout<<contents.c_str();
	system("pause");
	//fileDiffSolverByLine* _fileDiffSolverByLine = new fileDiffSolverByLine();
	return 0;
};