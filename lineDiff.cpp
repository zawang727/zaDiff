#include <set>
#include <tuple>
#include <algorithm>
#include "programOptions.h"
#include "lineDiff.h"


void sortString(vector<set<size_t>>& result, std::string& str)
{
    for(size_t i = 0; i < str.size(); ++i)
    {
        result[size_t(str[i]-'0')].insert(i);
    }
}

vector<std::tuple<size_t, size_t, size_t>> lineDiff::executeGetDiff(std::string l1, std::string l2)
{
    vector<set<size_t>> sortedL2(128);

    sortString(sortedL2, l2);

    vector<std::tuple<size_t, size_t, size_t>> LIS;  //asciiNum, l1ID, l2ID
    
    for(size_t j = 0; j < l1.size(); ++j)
    {
        size_t i = l1[j] - '0';
        if(sortedL2[i].size() == 0) continue;
        for(auto k = sortedL2[i].crbegin(); k != sortedL2[i].crend(); ++k)
        {
            LIS.emplace_back(std::make_tuple(i, j, *k));
            //std::printf("LIS %d %d %d\n",i,j,*k);
        }
    }

    vector<size_t> tail;
    vector<size_t> tailID;
    vector<size_t> parent(LIS.size(), -1);
    int last = -1;

    for(size_t i = 1; i < LIS.size(); ++i)
    {
        auto it = std::lower_bound(tail.begin(), tail.end(), std::get<2>(LIS[i]));
        if(it==tail.end()) 
        {
            parent[i] = (tail.empty()) ? -1 : tailID.back();
            tail.push_back(std::get<2>(LIS[i]));
            tailID.push_back(i);
            last = i;
        }
        else 
        {
            parent[i] = (it == tail.begin()) ? -1 : tailID[(size_t)(it - tail.begin()) - 1];
            *it = std::get<2>(LIS[i]);
            tailID[(size_t)(it - tail.begin())] = i;
        }
    }
    
    int m = tail.size();
    vector<int> lis(m);
  
    while (last != -1) {
        lis[--m] = last;
        last = parent[last];
    }

    //std::printf("%d\n",last);
    for(auto &i: lis )
    {
        std::printf("%d, ", l2[std::get<2>(LIS[i])]);
    }

    vector<std::tuple<size_t, size_t, size_t>> result;
    for(auto &i: lis )
    {
        result.push_back(LIS[i]);
    }

    return result;
}

size_t executeGetIdenticalNumber(std::string l1, std::string l2)
{
    vector<set<size_t>> sortedL2(128);

    sortString(sortedL2, l2);

    vector<std::tuple<size_t, size_t, size_t>> LIS;  //asciiNum, l1ID, l2ID
    
    for(size_t j = 0; j < l1.size(); ++j)
    {
        size_t i = l1[j] - '0';
        if(sortedL2[i].size() == 0) continue;
        for(auto k = sortedL2[i].crbegin(); k != sortedL2[i].crend(); ++k)
        {
            LIS.emplace_back(std::make_tuple(i, j, *k));
            //std::printf("LIS %d %d %d\n",i,j,*k);
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

    return tail.size();
}

