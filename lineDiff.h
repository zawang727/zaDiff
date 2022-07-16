#pragma once
#include <string>
#include "printUtils.h"

class lineDiff
{
public:
    lineDiff() = default;
    ~lineDiff() = default;

    vector<std::tuple<size_t, size_t, size_t>> executeGetDiff(std::string l1, std::string l2);
    size_t executeGetIdenticalNumber(std::string l1, std::string l2);
};