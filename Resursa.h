#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class Resursa {
    string nume;
    float pretMinim;
    float pretCurent;
    float pretMaxim;

    //---StatusTotal---//
    float cantitateTotalaExtrasa;
    float profitBrutObtinul;

public:
    Resursa(const string& _nume = "Generic_Resource", float _pretMinim = 0, float _pretMaxim = 0);

    // Getteri
    string getNume() const;
    float getPretMinim() const;
    float getPretCurent() const;
    float getPretMaxim() const;
    float getCantitateTotalaExtrasa() const;
    float getProfitBrutObtinul() const;

    // Setteri
    void setNume(const string&);
    void setPretMinim(float);
    void setPretCurent(float);
    void setPretMaxim(float);
    void setCantitateTotalaExtrasa(float);
    void setProfitBrutObtinul(float);

    void updatePretCurent();
    void updatePretSpecificat(float&);

    friend ifstream& operator>>(ifstream&, Resursa&);
    friend ostream& operator<<(ostream&, const Resursa&);
    friend void afiseazaProfitPeResurseCSV(ostream&, const Resursa&);

};

vector<Resursa> citesteResurseDinFisier(const string& fisierResurse);
