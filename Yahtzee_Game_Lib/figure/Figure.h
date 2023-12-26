#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Figure
{
public:
    Figure(int ID = 0) : m_ID(ID){}
    virtual ~Figure() {}
    virtual int calculateScore(const std::vector<int>& diceValues) = 0;
    virtual std::string getName() const = 0;

    int getID() const;
protected:
    const int m_ID;
};

