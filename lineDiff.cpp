#include <set>
#include <tuple>
#include <algorithm>
#include "programOptions.h"
#include "lineDiff.h"


void sortString(vector<set<size_t>>& result, std::string& str)
{
    for(size_t i = 0; i < str.size(); ++i)
    {
        result[size_t(str[i])].insert(i);
    }
}

vector<std::tuple<size_t, size_t, size_t>> lineDiff::executeGetDiff(std::string l1, std::string l2)
{
    vector<set<size_t>> sortedL2(128);

    sortString(sortedL2, l2);

    vector<std::tuple<size_t, size_t, size_t>> identicalArray;  //asciiNum, l1ID, l2ID
    vector<size_t> LISInput;
    
    for(size_t j = 0; j < l1.size(); ++j)
    {
        size_t i = l1[j];
        if(sortedL2[i].size() == 0) continue;
        for(auto k = sortedL2[i].crbegin(); k != sortedL2[i].crend(); ++k)
        {
            identicalArray.emplace_back(std::make_tuple(i, j, *k));
            LISInput.emplace_back(*k);
            if(programOptions::getInstance().debugMsgLevel > 10) 
            {
                std::printf("identicalArray %d %d %d\n",i,j,*k);
            }
        }
    }

    vector<size_t> lis = lineDiff::LISSolver(LISInput);

    /*vector<size_t> tail;
    vector<size_t> tailID;
    vector<size_t> parent(identicalArray.size(), -1);
    int last = -1;

    for(size_t i = 1; i < identicalArray.size(); ++i)
    {
        auto it = std::lower_bound(tail.begin(), tail.end(), std::get<2>(identicalArray[i]));
        if(it==tail.end()) 
        {
            parent[i] = (tail.empty()) ? -1 : tailID.back();
            tail.push_back(std::get<2>(identicalArray[i]));
            tailID.push_back(i);
            last = i;
        }
        else 
        {
            parent[i] = (it == tail.begin()) ? -1 : tailID[(size_t)(it - tail.begin()) - 1];
            *it = std::get<2>(identicalArray[i]);
            tailID[(size_t)(it - tail.begin())] = i;
        }
    }
    
    int m = tail.size();
    vector<int> lis(m);
  
    while (last != -1) {
        lis[--m] = last;
        last = parent[last];
    }*/

    //std::printf("%d\n",last);
    if(programOptions::getInstance().debugMsgLevel > 10) 
    {
        for(auto &i: lis ) std::printf("%d, ", std::get<2>(identicalArray[i]));
        std::printf("\n");
    }

    vector<std::tuple<size_t, size_t, size_t>> result;
    for(auto &i: lis )
    {
        result.push_back(identicalArray[i]);
    }

    return result;
}

size_t lineDiff::executeGetIdenticalNumber(std::string l1, std::string l2)
{
    if(programOptions::getInstance().debugMsgLevel > 10) std::printf("executeGetIdenticalNumber %s %s\n",l1.c_str(),l2.c_str());    
    vector<set<size_t>> sortedL2(128);

    sortString(sortedL2, l2);

    vector<std::tuple<size_t, size_t, size_t>> LIS;  //asciiNum, l1ID, l2ID
    
    for(size_t j = 0; j < l1.size(); ++j)
    {
        size_t i = l1[j];
        if(sortedL2[i].size() == 0) continue;
        for(auto k = sortedL2[i].crbegin(); k != sortedL2[i].crend(); ++k)
        {
            LIS.emplace_back(std::make_tuple(i, j, *k));
            if(programOptions::getInstance().debugMsgLevel > 10) std::printf("LIS %d %d %d\n",i,j,*k);
        }
    }

    vector<size_t> tail;

    for(size_t i = 1; i < LIS.size(); ++i)
    {
        auto it = std::lower_bound(tail.begin(), tail.end(), std::get<2>(LIS[i]));
        if(it==tail.end()) 
        {
            tail.push_back(std::get<2>(LIS[i]));
        }
        else 
        {
            *it = std::get<2>(LIS[i]);
        }
    }
    if(programOptions::getInstance().debugMsgLevel > 10) std::printf("executeGetIdenticalNumber finish\n"); 
    return tail.size();
}

template <typename T>
vector<T> lineDiff::LISSolver(vector<T> input)
{
    vector<T> tail;
    vector<size_t> tailID;
    vector<size_t> parent(input.size(), -1);
    int last = -1;

    for(size_t i = 1; i < input.size(); ++i)
    {
        auto it = std::lower_bound(tail.begin(), tail.end(), input[i]);
        if(it==tail.end()) 
        {
            parent[i] = (tail.empty()) ? -1 : tailID.back();
            tail.push_back(input[i]);
            tailID.push_back(i);
            last = i;
        }
        else 
        {
            parent[i] = (it == tail.begin()) ? -1 : tailID[(size_t)(it - tail.begin()) - 1];
            *it = input[i];
            tailID[(size_t)(it - tail.begin())] = i;
        }
    }
    
    size_t m = tail.size();
    vector<T> lis(m);
  
    while (last != -1) {
        lis[--m] = last;
        last = parent[last];
    }
    return lis;
}    
