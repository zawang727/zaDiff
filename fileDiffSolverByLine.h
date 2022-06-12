#include "fileDiffSolver.h"

class fileDiffSolverByLine: public fileDiffSolver
{
public:
    fileDiffSolverByLine() = default;
    ~fileDiffSolverByLine() = default;
    diffInfo solve() override;
};