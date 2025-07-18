#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class Racheta {
    string id;

    float capacitate;                        // kg
    float consum1000;                        // kg/1000km
    float combustibilDisponibil;             // kg
    float pretCombustibil;                   // $/kg
    
    float maxRange;                          // km
    float factorUtilitate;

    //---StatusTotal---//
    int nrMisiuniEfectuate;
    float profitTotalBrut;                   // $
    float profitTotalNet;                    // $
    float costTotal;                         // $
    float scorEficienta;

public:
    Racheta(const string& _id = "R0", float _capacitate = 0, float _consum1000 = 0, 
        float _combustibilDisponibil = 0, float _pretCombustibil = 0);

    // Getteri
    string getId() const;
    float getCapacitate() const;
    float getConsum1000() const;
    float getCombustibilDisponibil() const;
    float getPretCombustibil() const;

    float getMaxRange() const;
    float getFactorUtilitate() const;

    int getNrMisiuniEfectuate() const;
    float getProfitTotalBrut() const;
    float getProfitTotalNet() const;
    float getCostTotal() const;
    float getScorEficienta() const;

    // Setteri
    void setId(const string&);
    void setCapacitate(float);
    void setConsum1000(float);
    void setCombustibilDisponibil(float);
    void setPretCombustibil(float);

    void setNrMisiuniEfectuate(int);
    void setProfitTotalBrut(float);
    void setProfitTotalNet(float);
    void setCostTotal(float);

    void addMissionStatus(float, float, float);
    void calculeazaMaxRange();
    void calculeazaScorUtilitate();
    void calculeazaScorEficienta();

    friend ifstream& operator>>(ifstream&, Racheta&);
    friend ostream& operator<<(ostream&, const Racheta&);
    friend void afiseazaProfitTotalCSV(ofstream&, const Racheta&);
    friend void afiseazaClasamentRachetaCSV(ofstream&, const Racheta&, int);
};

vector<Racheta> citesteRacheteDinFisier(const string& fisierRachete);
