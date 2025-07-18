#pragma once

#include "Resursa.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <algorithm>
#include <numeric>

using namespace std;

class Asteroid {
    string id;

    vector<string> resurse;                 // nume
    vector<float> cantitatiTotale;          // kg
    float distanta;                         // km

public:
    static vector<Resursa>* resurseBazaDeDate;

    Asteroid(const string& _id = "A0", float _distanta = 0);

    // Getteri
    string getId() const;
    float getDistanta() const;
    vector<string> getResurse() const;
    vector<float> getCantitatiTotale() const;

    // Setteri
    void setId(const string&);
    void setDistanta(float);
    void setCantitateTotala(int, float);
    void addResursa(const string&, float, float);

    bool isEmpty() const;

    friend ostream& operator<<(ostream&, const Asteroid&);

    void sorteazaResurseDupaPretCurent();
};

vector<Asteroid> citesteAsteroiziDinFisier(const string& fisierAsteroizi);
