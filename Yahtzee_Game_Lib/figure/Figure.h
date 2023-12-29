#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Figure
{
public:
    virtual ~Figure() {}

    /** Calculate the score for this figure with the current dices.
    *   @param diceValues : dices to calculate the score.
    *   @return : the score.
    **/
    virtual int calculateScore(const std::vector<int>& diceValues) = 0;

    /** Give the description of the Brelan.
    *   @return : the string of the description.
    **/
    virtual std::string getName() const = 0;

    /** Give the Id of this class.
    *   @return : the id of the class
    **/
    virtual short getId() const = 0;

    /** TODO
    **/
    virtual void serialize(std::ostream& out) const = 0;
    
    /** TODO
    **/
    virtual void deserialize(std::istream& in) = 0;
};

