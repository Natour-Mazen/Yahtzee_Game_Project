#pragma once
#include "../player/Joueur.h"
#include "../figure/Figure.h"

class IA : public Joueur {
public:
    IA();
    void chooseFigure();
    double calculateExpectedValue(std::shared_ptr<Figure>& figure);
    double estimatePotentialScore(std::shared_ptr<Figure>& figure, int round);
    int remainingRounds();
};


