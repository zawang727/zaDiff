#include "printUtils.h"

class fileDiffSolver
{
public:
    fileDiffSolver() = default;
    virtual ~fileDiffSolver() = default;
    virtual diffInfo solve() = 0;
    void setContents(vector<string>& contents, int index);
    string firstFileName;
	string firstFolderName;
	string secondFileName;
	string secondFolderName;
protected:
    vector<string>& firstContents;
    vector<string>& secondContents;
};

class fileDiffSolverFactory
{
public:
    fileDiffSolverFactory() = default;
    ~fileDiffSolverFactory() = default;
    fileDiffSolver* getFileDiffSolver();
};