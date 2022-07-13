#pragma once
#include <string>
#include "printUtils.h"

class lineDiff
{
public:
    lineDiff() = default;
    ~lineDiff() = default;

    lineDiffInfo execute(std::string l1, std::string l2);
};