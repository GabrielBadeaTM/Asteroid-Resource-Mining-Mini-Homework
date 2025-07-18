#pragma once

#include "Racheta.h"
#include "Asteroid.h"
#include "Resursa.h"

#include <string>
#include <vector>

using namespace std;

class Misiune{
    Racheta* rachetaFolosita;
    Asteroid* asteroidMinat;
    
    vector<float> cantitatiExtrase;     // kg
    vector<string> resturseExtrase;

    float combustibilConsumat;          // kg
    float costCombustibil;              // $
    float profitBrut;                   // $
    float profitNet;                    // $

    public:
    Misiune(Racheta* , Asteroid*);

    float getCantitateTotalaExtrasa() const;
    string getResurseExtrase() const;

    void realizeazaMisiune();
    float simuleazaMisiune() const;
    float calculProfitUpdate(string&, float);
    float calculProfit(string&, float) const;

    friend ostream& operator<<(ostream&, const Misiune&);
    friend void afiseazaMisiuneCSV(ostream&, const Misiune&);
};



