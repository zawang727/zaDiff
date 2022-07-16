#pragma once
#include "fileDiffSolver.h"


class fileDiffSolverGreedy: public fileDiffSolver
{
public:
    fileDiffSolverGreedy(vector<string>& _firstContents, 
    vector<string>& _secondContents);
    ~fileDiffSolverGreedy() = default;
    diffInfo solve() override;
};