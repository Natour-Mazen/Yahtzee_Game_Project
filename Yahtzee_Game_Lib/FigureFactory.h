#pragma once
#include "Figure.h"
#include "brelan/Brelan.h"
#include "carre/Carre.h"
#include "full/Full.h"
#include "petiteSuite/PetiteSuite.h"
#include "grandeSuite/GrandeSuite.h"
#include "yahtzee/Yahtzee.h"
#include "chance/Chance.h"


class FigureFactory {
public:
    static Figure* createBrelan(int value) {
        switch (value) {
        case 1: return new Brelan<1>();
        case 2: return new Brelan<2>();
        case 3: return new Brelan<3>();
        case 4: return new Brelan<4>();
        case 5: return new Brelan<5>();
        case 6: return new Brelan<6>();
        default: return nullptr;
        }
    }

    static Figure* createCarre(int value) {
        switch (value) {
        case 1: return new Carre<1>();
        case 2: return new Carre<2>();
        case 3: return new Carre<3>();
        case 4: return new Carre<4>();
        case 5: return new Carre<5>();
        case 6: return new Carre<6>();
        default: return nullptr;
        }
    }

    static Figure* createFull(int value1, int value2) {
        return new Full(value1, value2);
    }

    static Figure* createPetiteSuite() {
        return new PetiteSuite();
    }

    static Figure* createGrandeSuite() {
        return new GrandeSuite();
    }

    static Figure* createYahtzee(int value) {
        return new Yahtzee(value);
    }

    static Figure* createChance() {
        return new Chance();
    }
};

