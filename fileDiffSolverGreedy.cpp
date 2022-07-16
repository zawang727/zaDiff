#include "fileDiffSolverGreedy.h"
#include "programOptions.h"
#include "lineDiff.h"

fileDiffSolverGreedy::fileDiffSolverGreedy
    (vector<string>& _firstContents, vector<string>& _secondContents):
fileDiffSolver(_firstContents,_secondContents)
{
}

diffInfo fileDiffSolverGreedy::solve()
{
    diffInfo resDiff;
    resDiff.setFileName(1, this->firstFileName);
    resDiff.setFolderName(1, this->firstFolderName);
    resDiff.setFileName(2, this->secondFileName);
    resDiff.setFolderName(2, this->secondFolderName);

    float _sameLineFilter = programOptions::getInstance().sameLineFilter;
    size_t _lineDiffMaxChar = programOptions::getInstance().lineDiffMaxChar;

    

    return resDiff;
}


