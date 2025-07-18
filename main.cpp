#include "Resursa.h"
#include "Racheta.h"
#include "Asteroid.h"
#include "Misiune.h"

#include "constants.h"

#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Nu s-au specificat suficiente fisiere CSV ca argumente." << endl;
        return 1;
    }

    #pragma region In
    string fisierRachete = argv[1];
    string fisierAsteroizi = argv[2];
    string fisierResurse = argv[3];

    ofstream misiuniCSV("misiuni.csv");
    misiuniCSV << "ID Rachetă;ID Asteroid;Resursă;Cantitate extrasă (kg);Combustibil consumat (kg);Cost combustibil ($);Profit brut ($);Profit net ($)\n";
    
    ofstream profitTotalCSV("profit_total.csv");
    ofstream profitPeResursaCSV("profit_resursa.csv");
    ofstream clasamentRacheteCSV("clasament_rachete.csv");

    vector<Resursa> resurse = citesteResurseDinFisier(fisierResurse);
    Asteroid::resurseBazaDeDate = &resurse;
    vector<Racheta> rachete = citesteRacheteDinFisier(fisierRachete);
    vector<Asteroid> asteroizi = citesteAsteroiziDinFisier(fisierAsteroizi);
    #pragma endregion

    for(auto& asteroid : asteroizi){
        asteroid.sorteazaResurseDupaPretCurent();
    }

    #pragma region Abordare 1
    sort(rachete.begin(), rachete.end(), [](const Racheta& a, const Racheta& b) {
        return a.getFactorUtilitate() > b.getFactorUtilitate();
    });
    
    sort(asteroizi.begin(), asteroizi.end(), [](const Asteroid& a, const Asteroid& b) {
        return a.getDistanta() < b.getDistanta();
    });
    
    size_t asteroidIndex = 0;

    for (auto& racheta : rachete) {
        while (asteroidIndex < asteroizi.size()) {
            Asteroid& asteroid = asteroizi[asteroidIndex];

            float disanta = asteroid.getDistanta();

            if (racheta.getMaxRange() < disanta) {
                break;
            }

            Misiune misiune(&racheta, &asteroid);
            if(misiune.simuleazaMisiune() > 0){
                misiune.realizeazaMisiune();
                afiseazaMisiuneCSV(misiuniCSV, misiune);
                    asteroid.sorteazaResurseDupaPretCurent();

            }
            else{
                // cout << "Racheta curenta nu face profit pe misiune\n";
                bool found = false;
                for(auto& rachetaDiferita : rachete){
                    if(rachetaDiferita.getMaxRange() > disanta){
                        // cout << "Exista alta racheta care poate ajunge la asteroid\n";
                        Misiune altaMisiune(&rachetaDiferita, &asteroid);
                        if(altaMisiune.simuleazaMisiune() > 0){
                            found = true;
                            // cout << "Acea alta racheta face profit pe acest asteroid\n\n";
                            altaMisiune.realizeazaMisiune();
                            afiseazaMisiuneCSV(misiuniCSV, altaMisiune);
                                asteroid.sorteazaResurseDupaPretCurent();
                        }
                    }
                }
                if(!found) {
                    asteroidIndex++; 
                    // cout << "Nici o alta racheta nu face profit pe asteroid sau nu ajunge la el\n\n";
                    }
            }

            // Verificăm dacă asteroidul a fost golit complet după misiune
            if (asteroid.isEmpty()) {
                asteroidIndex++; // Trecem la următorul asteroid
            } else {
                // Dacă asteroidul nu este gol, racheta va reveni la el
                continue;
            }
        }
    }
    #pragma endregion

    // #pragma region Abordare 2
    // size_t asteroidIndex = 0;
    // while (asteroidIndex < asteroizi.size()) {
    //     Asteroid& asteroid = asteroizi[asteroidIndex];

    //     Racheta* rachetaCeaMaiBuna = nullptr;
    //     float profitMaxim = -INF;
        
    //     for (auto& racheta : rachete) {
    //         float distanta = asteroid.getDistanta();

    //         if (racheta.getMaxRange() < distanta) {
    //             continue;
    //         }

    //         Misiune misiune(&racheta, &asteroid);
    //         float profit = misiune.simuleazaMisiune();

    //         if (profit > profitMaxim) {
    //             profitMaxim = profit;
    //             rachetaCeaMaiBuna = &racheta;
    //         }
    //     }

    //     if (rachetaCeaMaiBuna != nullptr && profitMaxim >= 0) {
    //         Misiune misiune(rachetaCeaMaiBuna, &asteroid);
    //         misiune.realizeazaMisiune();
    //         afiseazaMisiuneCSV(misiuniCSV, misiune);

    //         if (asteroid.isEmpty()) {
    //             asteroidIndex++;
    //         }
    //         asteroid.sorteazaResurseDupaPretCurent();

    //     } else {
    //         asteroidIndex++;
    //     }
    // }
    // #pragma endregion

    #pragma region Out
    profitTotalCSV << "ID Rachetă;Profit brut ($);Cost total combustibil ($);Profit net ($)\n";
    for (const auto& racheta : rachete) {
        afiseazaProfitTotalCSV(profitTotalCSV, racheta);
    }
    profitPeResursaCSV << "Resursă;Cantitate extrasă (kg);Profit brut ($)\n";
    for (const auto& resursa : resurse) {
        afiseazaProfitPeResurseCSV(profitPeResursaCSV, resursa);
    }
    clasamentRacheteCSV << "Loc;ID Rachetă;Profit net ($);Număr misiuni;Scor eficiență\n";
    int loc = 1;
    for (const auto& racheta : rachete) {
        afiseazaClasamentRachetaCSV(clasamentRacheteCSV, racheta, loc++);
    }
    #pragma endregion

    return 0;
}
