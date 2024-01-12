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

    /**
	 * Provides the name of the figure.
	 * The choice to define this function instead of overloading the << operator
	 * is optimal for us as it enhances the readability of our code.
	 * @return : the string of the name.
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

    /**
	 * Save the figure in an output stream.
	 * This is a pure virtual function that needs to be implemented in derived classes.
	 **/
    virtual void serialize(std::ostream& out) const = 0;

    /**
	 * Deserialize the score from an input stream.
	 * The function reads a line from the input stream, extracts the score value after the colon,
	 * and assigns it to the member variable 'm_score'.
	 **/
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

