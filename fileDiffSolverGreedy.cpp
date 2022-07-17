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
    int secondContentsStartID = 0;

    if(programOptions::getInstance().debugMsgLevel > 0) printf("start compare lines\n");

    for(int i = 0; i < this->firstContents.size(); ++i)
    {
        inputStr1 = this->firstContents[i];
        if(inputStr1.size()>100) inputStr1.resize(100);
        score = 0;

        if(programOptions::getInstance().debugMsgLevel > 0) printf("Compare lines %s %d\n", inputStr1.c_str(), this->secondContents.size());

        //here j should from big to small use a buffer to store candidates j
        for(int j = secondContentsStartID; j < this->secondContents.size(); ++j)
        {
            inputStr2 = this->secondContents[j];
            if(inputStr2.size()>100) inputStr2.resize(100);
            identicalNum = lineDiff::executeGetIdenticalNumber(inputStr1,inputStr1);
            similarity = (float) identicalNum / 
            (inputStr1.size() > inputStr2.size())? (float) inputStr1.size(): (float) inputStr2.size();
            if(programOptions::getInstance().debugMsgLevel > 0) printf("%f, ", similarity);
            
            if(similarity >= _sameLineFilter) 
            {
                tempJID.emplace_back(similarity,j);
                secondContentsStartID = j;
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
    int firstHead, secondHead;
    bool inIdentical = true;
    if(programOptions::getInstance().debugMsgLevel > 0) printf("Compose to diffinfo\n");
    //Here compose to diff info
    
    if(!LISOutput.empty() && (std::get<1>(identicalArray[LISOutput[0]]) != 1 
    || std::get<1>(identicalArray[LISOutput[0]]) !=1))
    {
        resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
            (pair<int,int>(-1,std::get<1>(identicalArray[LISOutput[0]])),
            vector<string> (firstContents.begin(), 
            firstContents.begin()+std::get<1>(identicalArray[LISOutput[0]]))));
        resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
            (pair<int,int>(-1,std::get<2>(identicalArray[LISOutput[0]])),
            vector<string> (firstContents.begin(), 
            secondContents.begin()+std::get<2>(identicalArray[LISOutput[0]]))));
        firstHead = std::get<1>(identicalArray[LISOutput[0]]);
        secondHead = std::get<2>(identicalArray[LISOutput[0]]);
    }
    if(programOptions::getInstance().debugMsgLevel > 0) printf("Compose to diffinfo 2 \n");
    for(int i = 0; i < LISOutput.size() -1 ; ++i)
    {
        if(i < LISOutput.size() -1 &&
        std::get<1>(identicalArray[LISOutput[i]])+1 == std::get<1>(identicalArray[LISOutput[i+1]]) &&
        std::get<2>(identicalArray[LISOutput[i]])+1 == std::get<2>(identicalArray[LISOutput[i+1]]) )
        {
            continue;
        }
        else
        {
            resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(-firstHead,std::get<1>(identicalArray[LISOutput[i]])),
                vector<string> (firstContents.begin() + firstHead +1, 
                firstContents.begin()+std::get<1>(identicalArray[LISOutput[i]]))));
            resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(-secondHead,std::get<2>(identicalArray[LISOutput[i]])),
                vector<string> (secondContents.begin() + secondHead +1, 
                secondContents.begin()+std::get<2>(identicalArray[LISOutput[i]]))));
            
            resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(std::get<1>(identicalArray[LISOutput[i]]),-std::get<1>(identicalArray[LISOutput[i+1]])),
                vector<string> (firstContents.begin() + std::get<1>(identicalArray[LISOutput[i]]) +1, 
                firstContents.begin()+std::get<1>(identicalArray[LISOutput[i+1]]))));
            resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(std::get<2>(identicalArray[LISOutput[i]]),-std::get<2>(identicalArray[LISOutput[i+1]])),
                vector<string> (secondContents.begin() + std::get<2>(identicalArray[LISOutput[i]]) +1, 
                secondContents.begin()+std::get<2>(identicalArray[LISOutput[i+1]]))));
            firstHead = std::get<1>(identicalArray[LISOutput[i+1]]);
            secondHead = std::get<2>(identicalArray[LISOutput[i+1]]);
        }
    }

    //need add rest of it

    return resDiff;
}


  