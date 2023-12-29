#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Figure
{
public:
    virtual ~Figure() {}
    virtual int calculateScore(const std::vector<int>& diceValues) = 0;
    virtual std::string getName() const = 0;
    virtual short getId() const = 0;
    virtual void serialize(std::ostream& out) const = 0;
    virtual void deserialize(std::istream& in) = 0;
};

