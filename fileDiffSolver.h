#pragma once
#include "printUtils.h"

class fileDiffSolver
{
public:
    fileDiffSolver(vector<string>& _firstContents, vector<string>& _secondContents);
    fileDiffSolver(vector<string>&& , vector<string>&& ) = delete;
    virtual ~fileDiffSolver() = default;
    virtual diffInfo solve() = 0;
    void setContents(vector<string>& contents, int index);
    void setFirstFileName(string fileName)
    {
        firstFileName = fileName;
    };
    void setFirstFolderName(string folderName)
    {
        firstFolderName = folderName;
    };
    void setSecondFileName(string fileName)
    {
        secondFileName = fileName;
    };
    void setSecondFolderName(string folderName)
    {
        secondFolderName = folderName;
    };
protected:
    vector<string>& firstContents;
    vector<string>& secondContents;
    string firstFileName;
	string firstFolderName;
	string secondFileName;
	string secondFolderName;
};

class fileDiffSolverFactory
{
public:
    fileDiffSolverFactory() = default;
    ~fileDiffSolverFactory() = default;
    fileDiffSolver* getFileDiffSolver(vector<string>& _firstContents, 
    vector<string>& _secondContents);
};