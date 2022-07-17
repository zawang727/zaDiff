#include <tuple>
#include <vector>
#include <math.h>
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
    float _identicalLineFilter  = programOptions::getInstance().identicalLineFilter;
    size_t _lineDiffMaxChar = programOptions::getInstance().lineDiffMaxChar;

    vector<std::tuple<float, size_t, size_t>> identicalArray;

    string inputStr1, inputStr2;
    size_t identicalNum;
    float similarity;
    size_t score;
    vector<pair<float,size_t>> tempJID;
    vector<size_t> LISInput;
    vector<size_t> LISOutput;

    for(int i = 0; i < this->firstContents.size(); ++i)
    {
        inputStr1 = this->firstContents[i];
        if(inputStr1.size()>100) inputStr1.resize(100);
        score = 0;
        //here j should from big to small use a buffer to store candidates j
        for(int j = 0; j < this->secondContents.size(); ++i)
        {
            inputStr2 = this->secondContents[j];
            if(inputStr2.size()>100) inputStr2.resize(100);
            identicalNum = lineDiff::executeGetIdenticalNumber(inputStr1,inputStr1);
            similarity = (float) identicalNum / 
            (inputStr1.size() > inputStr2.size())? (float) inputStr1.size(): (float) inputStr2.size();
            if(similarity >= _sameLineFilter) 
            {
                tempJID.emplace_back(similarity,j);
                break;
            }
            else if(similarity >= _identicalLineFilter)
            {
                tempJID.emplace_back(similarity,j);
                score += 20;
                if(score >= 100) break;
            }
        }

        //here push to identicalArray
        for(auto it = tempJID.rbegin(); it != tempJID.rend(); ++it)
        {
            identicalArray.emplace_back(std::make_tuple(it->first, i, it->second));
            LISInput.emplace_back(it->second);
        }
        tempJID.clear();
    }

    LISOutput = lineDiff::LISSolver(LISInput);

    //Here compose to diff info

    return resDiff;
}


  