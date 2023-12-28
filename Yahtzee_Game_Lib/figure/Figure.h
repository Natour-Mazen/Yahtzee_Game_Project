#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Figure
{
public:
    virtual ~Figure() {}
    virtual int calculateScore(const std::vector<int>& diceValues) = 0;
    virtual std::string getName() const = 0;

    virtual short getId() const = 0;
protected:
};

