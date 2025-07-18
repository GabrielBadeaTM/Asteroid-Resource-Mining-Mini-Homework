#include "Resursa.h"

#pragma region Constructori
Resursa::Resursa(const string& _nume, float _pretMinim, float _pretMaxim)
    : nume(_nume), pretMinim(_pretMinim), pretCurent(_pretMinim), pretMaxim(_pretMaxim), cantitateTotalaExtrasa(0) {}
#pragma endregion
#pragma region Getteri
string Resursa::getNume() const {
    return nume;
}

float Resursa::getPretMinim() const {
    return pretMinim;
}

float Resursa::getPretCurent() const {
    return pretCurent;
}

float Resursa::getPretMaxim() const {
    return pretMaxim;
}

float Resursa::getCantitateTotalaExtrasa() const {
    return cantitateTotalaExtrasa;
}

float Resursa::getProfitBrutObtinul() const {
    return profitBrutObtinul;
}

#pragma endregion
#pragma region Setteri
void Resursa::setNume(const string& _nume) {
    nume = _nume;
}

void Resursa::setPretMinim(float _pretMinim) {
    pretMinim = _pretMinim;
}

void Resursa::setPretCurent(float _pretCurent) {
    pretCurent = _pretCurent;
}

void Resursa::setPretMaxim(float _pretMaxim) {
    pretMaxim = _pretMaxim;
}

void Resursa::setCantitateTotalaExtrasa(float _cantitateTotalaExtrasa) {
    cantitateTotalaExtrasa = _cantitateTotalaExtrasa;
}

void Resursa::setProfitBrutObtinul(float _profitBrutObtinul) {
    profitBrutObtinul = _profitBrutObtinul;
}

#pragma endregion
#pragma region Alte Metode
void Resursa::updatePretCurent() {
    pretCurent = pretCurent * 0.9f;
    if (pretCurent < pretMinim) {
        pretCurent = pretMinim;
    }
}

void Resursa::updatePretSpecificat(float& _pretSpecificat) {
    _pretSpecificat = _pretSpecificat * 0.9f;
    if (_pretSpecificat < pretMinim) {
        _pretSpecificat = pretMinim;
    }
}

#pragma endregion
#pragma region IO
// Operator citire din fișier
ifstream& operator>>(ifstream& in, Resursa& resursa) {
    string line;
    if (getline(in, line)) {
        stringstream ss(line);
        string numeResursa;
        float pretMinim, pretMaxim;

        getline(ss, numeResursa, ';');
        ss >> pretMinim;
        ss.ignore();  // Ignorăm ';'
        ss >> pretMaxim;

        resursa.setNume(numeResursa);
        resursa.setPretMinim(pretMinim);
        resursa.setPretMaxim(pretMaxim);

        resursa.setPretCurent(pretMaxim);
        resursa.setCantitateTotalaExtrasa(0);
        resursa.setProfitBrutObtinul(0); 
    }
    return in;
}

vector<Resursa> citesteResurseDinFisier(const string& fisierResurse) {
    ifstream in(fisierResurse);
    if (!in.is_open()) {
        cerr << "Nu s-a putut deschide fisierul pentru resurse: " << fisierResurse << endl;
        return {};
    }

    vector<Resursa> resurse;
    string line;

    getline(in, line); // Sărim peste linia de titlu

    Resursa resursa;
    while (in >> resursa) {
        resurse.push_back(resursa);
    }

    return resurse;
}

ostream& operator<<(ostream& out, const Resursa& resursa) {
    out << "Nume: " << resursa.getNume()
        << ", Pret minim: " << resursa.getPretMinim()
        << ", Pret maxim: " << resursa.getPretMaxim() 
        << ", Pret curent: " << resursa.getPretCurent()
        << ", Cantitate totala extrasa: " << resursa.getCantitateTotalaExtrasa()
        << ", Profit brut obtinut: " << resursa.getProfitBrutObtinul();
    return out;
}

void afiseazaProfitPeResurseCSV(ostream& out, const Resursa& resursa){
    out << resursa.nume << ";" << resursa.cantitateTotalaExtrasa << ";" << resursa.profitBrutObtinul << "\n";
    return;
}
#pragma endregion
