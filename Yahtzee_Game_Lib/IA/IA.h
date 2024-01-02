#pragma once
#include "../player/Joueur.h"
#include "../figure/Figure.h"

class IA : public Joueur {
public:
    IA();
    void chooseFigure(const std::vector<int>& diceValues);
};


