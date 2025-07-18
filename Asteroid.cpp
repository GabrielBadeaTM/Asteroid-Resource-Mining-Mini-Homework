#include "Asteroid.h"

#pragma region Constructori
Asteroid::Asteroid(const string& _id, float _distanta): id(_id), distanta(_distanta) {}

#pragma endregion
#pragma region Getteri
string Asteroid::getId() const {
    return id;
}

float Asteroid::getDistanta() const {
    return distanta;
}

vector<string> Asteroid::getResurse() const {
    return resurse;
}

vector<float> Asteroid::getCantitatiTotale() const {
    return cantitatiTotale;
}

#pragma endregion
#pragma region Setteri
void Asteroid::setId(const string& _id) {
    id = _id;
}

void Asteroid::setDistanta(float _distanta) {
    distanta = _distanta;
}

void Asteroid::setCantitateTotala(int _index, float _cantitate){
    if(static_cast<size_t>(_index) < cantitatiTotale.size() && _index > -1) cantitatiTotale[_index] = _cantitate;
    else cerr << "Index in afara marginilor ;)";
}

// Adăugăm o resursă pe baza randamentului de extractie
void Asteroid::addResursa(const string& _resursa, float _cantitate, float _randament) {
    resurse.push_back(_resursa);
    cantitatiTotale.push_back(_cantitate*_randament/100);
}
#pragma endregion
#pragma region Alte Metode
bool Asteroid::isEmpty() const {
    for (size_t i = 0; i < resurse.size(); ++i) {
        if (cantitatiTotale[i] > 0) {
            return false;
        }
    }
    return true;
}

#pragma endregion
#pragma region IO
vector<Asteroid> citesteAsteroiziDinFisier(const string& fisierAsteroizi) {
    ifstream in(fisierAsteroizi);
    if (!in.is_open()) {
        cerr << "Nu s-a putut deschide fisierul pentru asteroizi: " << fisierAsteroizi << endl;
        return {};
    }

    vector<Asteroid> asteroizi;
    string line;

    // Sărim peste linia de titlu
    getline(in, line);

    string idCurent;
    Asteroid asteroid;

    while (getline(in, line)) {
        stringstream ss(line);
        string id, resursa;
        float cantitate, randament, distanta;

        // Citirea valorilor din linie
        getline(ss, id, ';');
        getline(ss, resursa, ';');
        ss >> cantitate;
        ss.ignore();  // Ignorăm ';'
        ss >> randament;
        ss.ignore();  // Ignorăm ';'
        ss >> distanta;

        // Dacă este un nou asteroid, adăugăm cel vechi în vector
        if (id != idCurent) {
            if (!idCurent.empty()) {
                asteroizi.push_back(asteroid);
            }
            idCurent = id;
            asteroid = Asteroid(id, distanta);
        }

        // Adăugăm resursa curentă la asteroidul activ
        asteroid.addResursa(resursa, cantitate, randament);
    }

    // Adăugăm ultimul asteroid în vector
    if (!idCurent.empty()) {
        asteroizi.push_back(asteroid);
    }

    return asteroizi;
}

ostream& operator<<(ostream& out, const Asteroid& asteroid) {
    out << "Asteroid ID: " << asteroid.getId() << endl;
    out << "  Distanță: " << asteroid.getDistanta() << " km" << endl;
    for (size_t i = 0; i < asteroid.getResurse().size(); ++i) {
        out << "  Resursa: " << asteroid.getResurse()[i]
            << ", Cantitate: " << asteroid.getCantitatiTotale()[i] << " kg";
    }
    return out;
}

#pragma endregion

vector<Resursa>* Asteroid::resurseBazaDeDate = nullptr;

void Asteroid::sorteazaResurseDupaPretCurent() {
    vector<size_t> indices(resurse.size());
    iota(indices.begin(), indices.end(), 0);

    sort(indices.begin(), indices.end(), [this](size_t a, size_t b) {
        float pretCurentA = 0;
        float pretCurentB = 0;

        for (const auto& resursa : *resurseBazaDeDate) {
            if (resursa.getNume() == resurse[a]) {
                pretCurentA = resursa.getPretCurent();
            }
            if (resursa.getNume() == resurse[b]) {
                pretCurentB = resursa.getPretCurent();
            }
        }

        return pretCurentA > pretCurentB;
    });

    vector<string> resurseSortate;
    vector<float> cantitatiTotaleSortate;

    for (size_t idx : indices) {
        resurseSortate.push_back(resurse[idx]);
        cantitatiTotaleSortate.push_back(cantitatiTotale[idx]);
    }

    resurse = std::move(resurseSortate);
    cantitatiTotale = std::move(cantitatiTotaleSortate);
}
