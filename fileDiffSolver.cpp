#include "fileDiffSolver.h"
#include "programOptions.h"

void fileDiffSolver::setContents(vector<string>& contents, int index)
{
    if(index == 1)
    {
        firstContents = contents
    }
    else if (index == 2)
    {
        secondContents = contents;
    }
    else
    {
        cout<< "Warning, fie contents unset because invalid index.\n";
    }
}

fileDiffSolver* fileDiffSolverFactory::getFileDiffSolver()
{
    programOptions& solverOption = programOptions::getInstance();
    solverEnum solverType = solverOption.solver;

    fileDiffSolver* resSolver;

    switch(solverType)
    {
        default:
        resSolver = new  
    }

    return resSolver;
}