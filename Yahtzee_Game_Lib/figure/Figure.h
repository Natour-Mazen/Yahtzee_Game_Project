#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Figure
{
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const = 0;
    virtual std::string getName() const = 0;
    virtual ~Figure() {}
    static const int ID = 0;
};

