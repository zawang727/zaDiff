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

// Binary search (note boundaries in the caller)
int CeilIndex(vector<size_t>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }
    return r;
}

lineDiffInfo lineDiff::execute(std::string l1, std::string l2)
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
            std::printf("LIS %d %d %d\n",i,j,*k);
        }
    }

    vector<size_t> tail(LIS.size(), 0);  
    vector<size_t> LCSnode(LIS.size(), -1); 
    int length = 1;

    tail[0] = std::get<1>(LIS[0]);
    LCSnode[0] = 0;

    for(size_t i = 1; i < LIS.size(); ++i)
    {
        if(std::get<2>(LIS[i]) < tail[0]) 
        {
            tail[0] = std::get<2>(LIS[i]);
            LCSnode[0] = i;
            printf("case1 %d %d\n",std::get<2>(LIS[i]), tail[0]);
        }
        else if (std::get<2>(LIS[i]) > tail[length - 1]) 
        {
            tail[length++] = std::get<2>(LIS[i]);
            LCSnode[length-1] = i;
            printf("case2 %d %d\n",std::get<2>(LIS[i]), tail[length-2]);
        }
        else 
        {
            size_t id = CeilIndex(tail, -1, length-1, std::get<2>(LIS[i]));
            tail[id] = std::get<2>(LIS[i]);
            LCSnode[id] = i;
            printf("case3 %d %d\n",id,i);
        }
    }
    std::printf("%d\n",length);
    for(auto &i: LCSnode )
    {
        std::printf("%d, ", i);
    }

    lineDiffInfo result;
    result.setString(1, l1);
    result.setString(2, l2);
    
    return result;
}

