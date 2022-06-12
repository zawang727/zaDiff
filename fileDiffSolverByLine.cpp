#include "fileDiffSolverByLine.h"

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
                continue;
            }
            else
            {
                startDiff = i+1;
            }
        }
        else
        {
            if(inDiff)
            {
                resDiff.firstFileDiff.insert(pair(pair(-1*(int)startDiff, i),
                vector<string> (firstContents.begin()+startDiff-1, firstContents.begin()+i+1)));
            }
        }
    }

    return resDiff;
}