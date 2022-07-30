#include <tuple>
#include <vector>
#include <math.h>
#include <algorithm>
#include "fileDiffSolverHuntSzymanski.h"
#include "programOptions.h"
#include "lineDiff.h"

fileDiffSolverHuntSzymanski::fileDiffSolverHuntSzymanski
    (vector<string>& _firstContents, vector<string>& _secondContents):
fileDiffSolver(_firstContents,_secondContents)
{
}

diffInfo fileDiffSolverHuntSzymanski::solve()
{
    diffInfo resDiff;
    resDiff.setFileName(1, this->firstFileName);
    resDiff.setFolderName(1, this->firstFolderName);
    resDiff.setFileName(2, this->secondFileName);
    resDiff.setFolderName(2, this->secondFolderName);

    size_t _lineDiffMaxChar = programOptions::getInstance().lineDiffMaxChar;
    string firstFileString;
    string secondFileString;
    vector<size_t> lineBreakPositionFirst(firstContents.size(),0);
    vector<size_t> lineBreakPositionSecond(secondContents.size(),0);


    for(auto&i : firstContents)
    {
        if(i.size()>_lineDiffMaxChar)
        {
            i.resize(_lineDiffMaxChar);
        }
        firstFileString += i;
        lineBreakPositionFirst.emplace_back(firstFileString.size()-1);
        firstFileString += "\n";
    }

    for(auto&i : secondContents)
    {
        if(i.size()>_lineDiffMaxChar)
        {
            i.resize(_lineDiffMaxChar);
        }
        secondFileString += i;
        lineBreakPositionSecond.emplace_back(secondFileString.size()-1);
        secondFileString += "\n";
    }

    std::vector<std::tuple<size_t, size_t, size_t>> LIS;
    LIS = lineDiff::executeGetDiff(firstFileString,secondFileString);

    size_t fistFPrevLineNum = 0;
    size_t secondFPrevLineNum = 0;
    size_t fistFLineNum = 0;
    size_t secondFLineNum = 0;

    for(int i = 0; i < LIS.size(); ++i)
    {
        if(!strcmp(&firstFileString[std::get<0>(LIS[i])],"\n") )
        {
            size_t firstFIdenticalID = std::get<1>(LIS[i]);
            size_t secondFIdenticalID = std::get<2>(LIS[i]);
            while(firstFIdenticalID != (lineBreakPositionFirst[fistFLineNum]+1)) fistFLineNum++;
            while(secondFIdenticalID != (lineBreakPositionSecond[secondFLineNum]+1)) secondFLineNum++;
            resDiff.firstFileDiff.insert(std::pair<regionDiff, vector<string>>
                (pair<int,int>(-(fistFPrevLineNum+1),fistFLineNum+1),
                vector<string> (firstContents.begin() + fistFPrevLineNum, 
                firstContents.begin()+fistFLineNum +1)));
            resDiff.firstFileDiff.insert(std::pair<regionDiff, vector<string>>
                (pair<int,int>(-(secondFPrevLineNum+1),secondFLineNum+1),
                vector<string> (secondContents.begin() + secondFPrevLineNum, 
                secondContents.begin()+secondFLineNum +1)));
            fistFPrevLineNum = fistFLineNum + 1;
            secondFPrevLineNum = secondFLineNum + 1;
        }
    }

    resDiff.firstFileDiff.insert(std::pair<regionDiff, vector<string>>
        (pair<int,int>(-(fistFPrevLineNum+1),lineBreakPositionFirst.size()),
        vector<string> (firstContents.begin() + fistFPrevLineNum, 
        firstContents.begin()+lineBreakPositionFirst.size())));
    resDiff.firstFileDiff.insert(std::pair<regionDiff, vector<string>>
        (pair<int,int>(-(secondFPrevLineNum+1),lineBreakPositionSecond.size()),
        vector<string> (secondContents.begin() + secondFPrevLineNum, 
        secondContents.begin()+lineBreakPositionSecond.size())));

    return resDiff;
}


  