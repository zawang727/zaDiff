#pragma once
#include <string>
#include "printUtils.h"

class lineDiff
{
public:
    lineDiff() = default;
    ~lineDiff() = default;

    vector<std::tuple<size_t, size_t, size_t>> execute(std::string l1, std::string l2);
};