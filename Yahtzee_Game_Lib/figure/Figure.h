#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Figure
{
public:
    virtual ~Figure() = default;

    /** Calculate the score for this figure with the current dices and keep the score.
    *   @param diceValues : dices to calculate the score.
    *   @return : the score.
    **/
    void calculateScore(const std::vector<int>& diceValues) {
        m_score = justCalculateScore(diceValues);
    }

    /** Give the description of the Brelan.
    *   @return : the string of the description.
    **/
    virtual std::string getName() const = 0;

    /** Give the Id of this class.
    *   @return : the id of the class
    **/
    virtual short getId() const = 0;

    /** Give the score of this class.
    *   @return : the score.
    **/
    int getScore() const {
        return m_score;
    }

    /** Save the figure in a out stream.
    **/
    virtual void serialize(std::ostream& out) const = 0;

    void deserializeScore(std::istream& in) {
        std::string ligne;

        getline(in, ligne);
        m_score = std::stoi(ligne.substr(ligne.find(":") + 1));
    }

protected:
    int m_score = 0;

    /** Calculate the score for this figure with the current dices.
    *   @param diceValues : dices to calculate the score.
    *   @return : the score.
    **/
    virtual int justCalculateScore(const std::vector<int>& diceValues) = 0;
};

