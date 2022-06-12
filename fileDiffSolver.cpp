#include "fileDiffSolver.h"
#include "programOptions.h"
#include "fileDiffSolverByLine.h"

void fileDiffSolver::setContents(vector<string>& contents, int index)
{
    if(index == 1)
    {
        firstContents = contents;
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
        case solverEnumByLine:
        resSolver = new fileDiffSolverByLine();
        break;
        default:
        resSolver = new fileDiffSolverByLine();
    }

    return resSolver;
}