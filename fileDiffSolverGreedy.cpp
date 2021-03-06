#include <tuple>
#include <vector>
#include <math.h>
#include <algorithm>
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

        if(programOptions::getInstance().debugMsgLevel > 5) printf("Compare lines %s %d\n", inputStr1.c_str(), this->secondContents.size());

        //here j should from big to small use a buffer to store candidates j
        for(int j = secondContentsStartID; j < this->secondContents.size(); ++j)
        {
            inputStr2 = this->secondContents[j];
            if(inputStr2.size()>100) inputStr2.resize(100);
            if(inputStr1.size() == 0 && inputStr2.size() == 0)
            {
                similarity = 1.0;
            }
            else
            {
                identicalNum = lineDiff::executeGetIdenticalNumber(inputStr1,inputStr1);
                similarity = ((float)identicalNum / (float)max((int)max(inputStr1.size(), inputStr2.size()), 1));
            }
            
            if(programOptions::getInstance().debugMsgLevel > 0 && similarity>0.4) printf("%f %d %d\n", similarity, i , j);
            
            if(similarity >= _identicalLineFilter)  tempJID.emplace_back(pair<float,size_t>(similarity,j));
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
    int firstHead = 1, secondHead = 1;
    bool inIdentical = true;
    if(programOptions::getInstance().debugMsgLevel > 0) printf("Compose to the diffinfo LISInput size %d LISOutput size %d \n",LISInput.size(), LISOutput.size());
    if(programOptions::getInstance().debugMsgLevel > 0)
    {
        std::printf("identicalArray result ");
        for(const auto& i : LISOutput)
        {
            std::printf("%d %d,", std::get<1>(identicalArray[i]),std::get<2>(identicalArray[i]));
        }
        std::printf("\n");
    }
    //Here compose to diff info
    
    if(!LISOutput.empty() && (std::get<1>(identicalArray[LISOutput[0]]) != 0 
    || std::get<1>(identicalArray[LISOutput[0]]) !=0))
    {
        resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
            (pair<int,int>(-1,std::get<1>(identicalArray[LISOutput[0]])),
            vector<string> (firstContents.begin(), 
            firstContents.begin()+std::get<1>(identicalArray[LISOutput[0]]))));
        resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
            (pair<int,int>(-1,std::get<2>(identicalArray[LISOutput[0]])),
            vector<string> (firstContents.begin(), 
            secondContents.begin()+std::get<2>(identicalArray[LISOutput[0]]))));
        firstHead = std::get<1>(identicalArray[LISOutput[0]]) + 1;
        secondHead = std::get<2>(identicalArray[LISOutput[0]]) + 1;
    }
    if(programOptions::getInstance().debugMsgLevel > 0) printf("Compose to diffinfo 2 \n");
    for(int i = 0; i < LISOutput.size(); ++i)
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
                vector<string> (firstContents.begin() + (firstHead - 1), 
                firstContents.begin()+std::get<1>(identicalArray[LISOutput[i]]))));
            resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(-secondHead,std::get<2>(identicalArray[LISOutput[i]])),
                vector<string> (secondContents.begin() + (secondHead - 1), 
                secondContents.begin()+std::get<2>(identicalArray[LISOutput[i]]))));

            if(i+1 == LISOutput.size())
            {
                firstHead = firstContents.size();
                secondHead = secondContents.size();
            }
            else
            {
                firstHead = std::get<1>(identicalArray[LISOutput[i+1]]);
                secondHead = std::get<2>(identicalArray[LISOutput[i+1]]);
            }
            
            resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(std::get<1>(identicalArray[LISOutput[i]]),-firstHead),
                vector<string> (firstContents.begin() + std::get<1>(identicalArray[LISOutput[i]]) +1, 
                firstContents.begin()+firstHead)));
            resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
                (pair<int,int>(std::get<2>(identicalArray[LISOutput[i]]),-secondHead),
                vector<string> (secondContents.begin() + std::get<2>(identicalArray[LISOutput[i]]) +1, 
                secondContents.begin()+secondHead))); 
        }
    }

    resDiff.firstFileDiff.insert(pair<regionDiff, vector<string>>
        (pair<int,int>(-firstHead,secondContents.size()),
        vector<string> (firstContents.begin() + (firstHead - 1), 
        firstContents.end())));
    resDiff.secondFileDiff.insert(pair<regionDiff, vector<string>>
        (pair<int,int>(-secondHead,secondContents.size()),
        vector<string> (secondContents.begin() + (secondHead - 1), 
        secondContents.end())));

    //need add rest of it

    return resDiff;
}


  