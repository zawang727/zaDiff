#include "fileDiffSolver.h"
#include "programOptions.h"
#include "fileDiffSolverByLine.h"
#include "fileDiffSolverGreedy.h"
#include "fileDiffSolverHuntSzymanski.h"

fileDiffSolver::fileDiffSolver(vector<string>& _firstContents, 
vector<string>& _secondContents):
firstContents(_firstContents), secondContents(_secondContents)
{
}

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

fileDiffSolver* fileDiffSolverFactory::getFileDiffSolver(vector<string>& _firstContents, 
vector<string>& _secondContents)
{
    programOptions& solverOption = programOptions::getInstance();
    solverEnum solverType = solverOption.solver;

    fileDiffSolver* resSolver;

    switch(solverType)
    {
        case solverEnumByLine:
        resSolver = new fileDiffSolverByLine(_firstContents, _secondContents);
        break;
        case solverGreedy1:
        resSolver = new fileDiffSolverGreedy(_firstContents, _secondContents);
        break;
        case solverHuntSzymanski:
        resSolver = new fileDiffSolverHuntSzymanski(_firstContents, _secondContents);
        break;
        default:
        resSolver = new fileDiffSolverByLine(_firstContents, _secondContents);
    }

    return resSolver;
}