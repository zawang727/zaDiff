#pragma once
#include "fileDiffSolver.h"


class fileDiffSolverHuntSzymanski: public fileDiffSolver
{
public:
    fileDiffSolverHuntSzymanski(vector<string>& _firstContents, 
    vector<string>& _secondContents);
    ~fileDiffSolverHuntSzymanski() = default;
    diffInfo solve() override;
};