#include "Misiune.h"
#include "Asteroid.h"
#include "constants.h"

// #include <algorithm>
#include <cmath>

#pragma region Constructor
Misiune::Misiune(Racheta* _racheta, Asteroid* _asteroid)
    : rachetaFolosita(_racheta), asteroidMinat(_asteroid), combustibilConsumat(0), costCombustibil(0), profitBrut(0), profitNet(0) {
        // realizeazaMisiune();
    }

#pragma endregion
#pragma region Getteri
float Misiune::getCantitateTotalaExtrasa() const {
    float total = 0.0;
    for (const auto& cantitate : cantitatiExtrase) {
        total += cantitate;
    }
    return total;
}

string Misiune::getResurseExtrase() const {
    string rezultat;
    for (size_t i = 0; i < resturseExtrase.size(); ++i) {
        rezultat += resturseExtrase[i];
        if (i != resturseExtrase.size() - 1) {
            rezultat += "&";
        }
    }
    return rezultat;
}

#pragma endregion
#pragma region Setteri

#pragma endregion
#pragma region Alte Metode
float Misiune::simuleazaMisiune() const{
    float cargoCapacitate = rachetaFolosita->getCapacitate();
    float distanta = asteroidMinat->getDistanta();

    float profitCalculat = 0;
    float costCombustibilCalculat = 0;

    for (size_t i = 0; i < asteroidMinat->getResurse().size(); ++i) {
        string resursa = asteroidMinat->getResurse()[i];
        float cantitateTotala = asteroidMinat->getCantitatiTotale()[i];

        float cantitateExtrasa = min(cantitateTotala, cargoCapacitate);

        cargoCapacitate -= cantitateExtrasa;
        
        profitCalculat += calculProfit(resursa, cantitateExtrasa);

        if (cargoCapacitate <= 0) break;
    }

    costCombustibilCalculat = ((distanta * 2 * rachetaFolosita->getConsum1000()) / 1000) * rachetaFolosita->getPretCombustibil();

    profitCalculat -= costCombustibilCalculat;
    return profitCalculat;
}

void Misiune::realizeazaMisiune() {
    float cargoCapacitate = rachetaFolosita->getCapacitate();
    float distanta = asteroidMinat->getDistanta();

    for (size_t i = 0; i < asteroidMinat->getResurse().size(); ++i) {
        string resursa = asteroidMinat->getResurse()[i];
        float cantitateTotala = asteroidMinat->getCantitatiTotale()[i];

        float cantitateExtrasa = min(cantitateTotala, cargoCapacitate);

        asteroidMinat->setCantitateTotala(i,asteroidMinat->getCantitatiTotale()[i] - cantitateExtrasa);
        cargoCapacitate -= cantitateExtrasa;

        resturseExtrase.push_back(resursa);
        cantitatiExtrase.push_back(cantitateExtrasa);

        profitBrut += calculProfitUpdate(resursa, cantitateExtrasa);

        if (cargoCapacitate <= 0) break;
    }

    combustibilConsumat = (distanta * 2 * rachetaFolosita->getConsum1000()) / 1000;;
    costCombustibil = combustibilConsumat * rachetaFolosita->getPretCombustibil();

    profitNet = profitBrut - costCombustibil;

    rachetaFolosita->setNrMisiuniEfectuate(rachetaFolosita->getNrMisiuniEfectuate() + 1);
    rachetaFolosita->setProfitTotalBrut(rachetaFolosita->getProfitTotalBrut() + profitBrut);
    rachetaFolosita->setProfitTotalNet(rachetaFolosita->getProfitTotalNet() + profitNet);
    rachetaFolosita->setCostTotal(rachetaFolosita->getCostTotal() + costCombustibil);

    rachetaFolosita->calculeazaScorEficienta();
}

float Misiune::calculProfitUpdate(string& resursa, float cantitateExtrasa) {
    float profit = 0.0;
    
    for (auto& res : *(Asteroid::resurseBazaDeDate)) {
        if (res.getNume() == resursa) {
            float cantitateRamasaPanaLaMark = PRICE_MARK - fmod(res.getCantitateTotalaExtrasa(), PRICE_MARK);
            
            res.setCantitateTotalaExtrasa(res.getCantitateTotalaExtrasa() + cantitateExtrasa);

            if (cantitateExtrasa <= cantitateRamasaPanaLaMark) {
                profit += cantitateExtrasa * res.getPretCurent();
            } else {
                profit += cantitateRamasaPanaLaMark * res.getPretCurent();
                cantitateExtrasa -= cantitateRamasaPanaLaMark;
                res.updatePretCurent();

                while (cantitateExtrasa >= PRICE_MARK) {
                    profit += PRICE_MARK * res.getPretCurent();
                    cantitateExtrasa -= PRICE_MARK;
                    res.updatePretCurent();
                }

                if (cantitateExtrasa > 0) {
                    profit += cantitateExtrasa * res.getPretCurent();
                }
            }

            res.setProfitBrutObtinul(res.getProfitBrutObtinul() + profit);
            break; // Resursa a fost găsită, ieșim din buclă
        }
    }
    return profit;
}

float Misiune::calculProfit(string& resursa, float cantitateExtrasa) const {
    float profit = 0.0;
    float pretVanzare;
    
    for (auto& res : *(Asteroid::resurseBazaDeDate)) {
        if (res.getNume() == resursa) {
            float cantitateRamasaPanaLaMark = PRICE_MARK - fmod(res.getCantitateTotalaExtrasa(), PRICE_MARK);
            pretVanzare = res.getPretCurent();
            
            if (cantitateExtrasa <= cantitateRamasaPanaLaMark) {
                profit += cantitateExtrasa * pretVanzare;
            } else {
                profit += cantitateRamasaPanaLaMark * pretVanzare;
                cantitateExtrasa -= cantitateRamasaPanaLaMark;
                res.updatePretSpecificat(pretVanzare);

                while (cantitateExtrasa >= PRICE_MARK) {
                    profit += PRICE_MARK * pretVanzare;
                    cantitateExtrasa -= PRICE_MARK;
                    res.updatePretSpecificat(pretVanzare);
                }

                if (cantitateExtrasa > 0) {
                    profit += cantitateExtrasa * pretVanzare;
                }
            }

            break; // Resursa a fost găsită, ieșim din buclă
        }
    }
    return profit;
}

#pragma endregion
#pragma region IO
ostream& operator<<(ostream& out, const Misiune& misiune) {
    out << "Misiune:\n";
    out << "  Racheta ID: " << misiune.rachetaFolosita->getId() << "\n";
    out << "  Asteroid ID: " << misiune.asteroidMinat->getId() << "\n";
    out << "  Resurse extrase:\n";
    for (size_t i = 0; i < misiune.resturseExtrase.size(); ++i) {
        out << "    - " << misiune.resturseExtrase[i]
            << ", Cantitate extrasa: " << misiune.cantitatiExtrase[i] << " kg\n";
    }
    out << "  Combustibil consumat: " << misiune.combustibilConsumat << " kg\n";
    out << "  Cost combustibil: " << misiune.costCombustibil << " $\n";
    out << "  Profit brut: " << misiune.profitBrut << " $\n";
    out << "  Profit net: " << misiune.profitNet << " $\n";

    return out;
}

void afiseazaMisiuneCSV(ostream& out, const Misiune& misiune){
    out << misiune.rachetaFolosita->getId()<< ";"
        << misiune.asteroidMinat->getId() << ";"
        << misiune.getResurseExtrase() << ";"
        << misiune.getCantitateTotalaExtrasa() << ";"
        << misiune.combustibilConsumat << ";"
        << misiune.costCombustibil << ";"
        << misiune.profitBrut << ";"
        << misiune.profitNet << "\n";
    return;
}

#pragma endregion