#pragma once
#include <string>
#include "printUtils.h"

class lineDiff
{
public:
    lineDiff() = default;
    ~lineDiff() = default;

    static vector<std::tuple<size_t, size_t, size_t>> executeGetDiff(std::string l1, std::string l2);
    static size_t executeGetIdenticalNumber(std::string l1, std::string l2);
    template <typename T>
    static vector<T> LISSolver(vector<T> input); // return id in input array
};