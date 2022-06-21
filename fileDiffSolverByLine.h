#pragma once
#include "fileDiffSolver.h"

class fileDiffSolverByLine: public fileDiffSolver
{
public:
    fileDiffSolverByLine(vector<string>& _firstContents, 
    vector<string>& _secondContents);
    ~fileDiffSolverByLine() = default;
    diffInfo solve() override;
};