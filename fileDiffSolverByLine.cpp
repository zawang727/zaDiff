#include "fileDiffSolverByLine.h"

fileDiffSolverByLine::fileDiffSolverByLine(vector<string>& _firstContents, 
    vector<string>& _secondContents):
fileDiffSolver(_firstContents,_secondContents)
{
}

diffInfo fileDiffSolverByLine::solve()
{
    diffInfo resDiff;
    resDiff.firstFileName = this->firstFileName;
    resDiff.firstFolderName = this->firstFolderName;
    resDiff.secondFileName = this->secondFileName;
    resDiff.secondFolderName = this->secondFolderName;

    bool inDiff = false;
    int startDiff = 1;
    unsigned int compareLines = (firstContents.size()>secondContents.size())? 
    secondContents.size():firstContents.size();

    for(int i = 0; i < compareLines-1; ++i)
    {
        if(firstContents[i+1] == secondContents[i+1])
        {
            if(inDiff)
            {
                resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(-1*(int)startDiff, i+1),
                vector<string> (firstContents.begin()+startDiff+1, firstContents.begin()+i+1)));
                resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(-1*(int)startDiff, i+1),
                vector<string> (secondContents.begin()+startDiff+1, secondContents.begin()+i+1)));
                inDiff = false;
                startDiff = i+1;
            }
            else
            {
                startDiff = i+1;
            }
        }
        else
        {
            inDiff = true;
        }

    }
    if(inDiff)
    {
        resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
        (pair<int,int>(-1*(int)startDiff, compareLines),
        vector<string> (firstContents.begin()+startDiff+1, firstContents.begin()+compareLines)));
        resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
        (pair<int,int>(-1*(int)startDiff, compareLines),
        vector<string> (secondContents.begin()+startDiff+1, secondContents.begin()+compareLines)));
    } 
    return resDiff;
}