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
        switch (value1) {
        case 1: return (value2 == 2) ? new Full<1, 2>() : nullptr;
        case 2: return (value2 == 1) ? new Full<2, 1>() : nullptr;
        case 3: return (value2 == 4) ? new Full<3, 4>() : nullptr;
        case 4: return (value2 == 3) ? new Full<4, 3>() : nullptr;
        case 5: return (value2 == 6) ? new Full<5, 6>() : nullptr;
        case 6: return (value2 == 5) ? new Full<6, 5>() : nullptr;
        default: return nullptr;
        }
    }

    static Figure* createPetiteSuite() {
        return new PetiteSuite();
    }

    static Figure* createGrandeSuite() {
        return new GrandeSuite();
    }

    static Figure* createYahtzee(int value) {
        switch (value) {
        case 1: return new Yahtzee<1>();
        case 2: return new Yahtzee<2>();
        case 3: return new Yahtzee<3>();
        case 4: return new Yahtzee<4>();
        case 5: return new Yahtzee<5>();
        case 6: return new Yahtzee<6>();
        default: return nullptr;
        }
    }

    static Figure* createChance() {
        return new Chance();
    }
};

