#include "Racheta.h"
#include "constants.h"

#pragma region Constructori
Racheta::Racheta(const string& _id, float _capacitate, float _consum1000, float _combustibilDisponibil, float _pretCombustibil)
    : id(_id), capacitate(_capacitate), consum1000(_consum1000), combustibilDisponibil(_combustibilDisponibil), pretCombustibil(_pretCombustibil),
      nrMisiuniEfectuate(0), profitTotalBrut(0), profitTotalNet(0), costTotal(0), scorEficienta(0) {
}

#pragma endregion
#pragma region Getteri
string Racheta::getId() const {
    return id;
}

float Racheta::getCapacitate() const {
    return capacitate;
}

float Racheta::getConsum1000() const {
    return consum1000;
}

float Racheta::getCombustibilDisponibil() const {
    return combustibilDisponibil;
}

float Racheta::getPretCombustibil() const {
    return pretCombustibil;
}

//----//

float Racheta::getMaxRange() const {
    return maxRange;
}

float Racheta::getFactorUtilitate() const {
    return factorUtilitate;
}

//----//

int Racheta::getNrMisiuniEfectuate() const {
    return nrMisiuniEfectuate;
}

float Racheta::getProfitTotalBrut() const {
    return profitTotalBrut;
}

float Racheta::getProfitTotalNet() const {
    return profitTotalNet;
}

float Racheta::getCostTotal() const {
    return costTotal;
}

float Racheta::getScorEficienta() const {
    return scorEficienta;
}

#pragma endregion
#pragma region Setteri
void Racheta::setId(const string& _id) {
    id = _id;
}

void Racheta::setCapacitate(float _capacitate) {
    capacitate = _capacitate;
    calculeazaScorUtilitate();
}

void Racheta::setConsum1000(float _consum1000) {
    consum1000 = _consum1000;
    calculeazaMaxRange();
}

void Racheta::setCombustibilDisponibil(float _combustibilDisponibil) {
    combustibilDisponibil = _combustibilDisponibil;
    calculeazaMaxRange();
}

void Racheta::setPretCombustibil(float _pretCombustibil) {
    pretCombustibil = _pretCombustibil;
    calculeazaScorUtilitate();
}

//----//

void Racheta::setNrMisiuniEfectuate(int _nrMisiuniEfectuate) {
    nrMisiuniEfectuate = _nrMisiuniEfectuate;
}

void Racheta::setProfitTotalBrut(float _profitTotalBrut) {
    profitTotalBrut = _profitTotalBrut;
}

void Racheta::setProfitTotalNet(float _profitTotalNet) {
    profitTotalNet = _profitTotalNet;
}

void Racheta::setCostTotal(float _costTotal) {
    costTotal = _costTotal;
}

#pragma endregion
#pragma region Alte Metode
void Racheta::addMissionStatus(float _profitBrutMisiune, float _profitNetMisiune, float _costTotalMisiune) {
    nrMisiuniEfectuate++;

    profitTotalBrut += _profitBrutMisiune;
    profitTotalNet += _profitNetMisiune;
    costTotal += _costTotalMisiune;

    if (nrMisiuniEfectuate > 0) {
        scorEficienta = profitTotalNet / nrMisiuniEfectuate;
    }
}

void Racheta::calculeazaMaxRange() {
    maxRange = (combustibilDisponibil * 1000) / (consum1000 * 2); //impartim la doi pt ca trebuie drum dus intors
}

void Racheta::calculeazaScorUtilitate(){
    factorUtilitate = (pretCombustibil != 0) ? (capacitate / pretCombustibil) : INF; // nu cred ca e cazul oricum ;)
}

void Racheta::calculeazaScorEficienta() {
    if (nrMisiuniEfectuate == 0) {
        scorEficienta = 0;
    } else {
        scorEficienta = profitTotalNet / nrMisiuniEfectuate;
    }
}

#pragma endregion
#pragma region IO
// Operator citire din fișier
ifstream& operator>>(ifstream& in, Racheta& racheta) {
    string line;
    if (getline(in, line)) {
        stringstream ss(line);
        string id;
        float capacitate, consum1000, combustibilDisponibil, pretCombustibil;

        getline(ss, id, ';');
        ss >> capacitate;
        ss.ignore();  // Ignorăm ';'
        ss >> consum1000;
        ss.ignore();  // Ignorăm ';'
        ss >> combustibilDisponibil;
        ss.ignore();  // Ignorăm ';'
        ss >> pretCombustibil;

        // Setăm valorile citite
        racheta.setId(id);
        racheta.setCapacitate(capacitate);
        racheta.setConsum1000(consum1000);
        racheta.setCombustibilDisponibil(combustibilDisponibil);
        racheta.setPretCombustibil(pretCombustibil);

        // Inițializăm restul valorilor
        racheta.setNrMisiuniEfectuate(0);
        racheta.setProfitTotalBrut(0);
        racheta.setProfitTotalNet(0);
        racheta.setCostTotal(0);
        racheta.calculeazaScorEficienta();

    }
    return in;
}

vector<Racheta> citesteRacheteDinFisier(const string& fisierRachete) {
    ifstream in(fisierRachete);
    if (!in.is_open()) {
        cerr << "Nu s-a putut deschide fisierul pentru rachete: " << fisierRachete << endl;
        return {};
    }

    vector<Racheta> rachete;
    string line;

    // Sărim peste linia de titlu
    getline(in, line);

    Racheta racheta;
    while (in >> racheta) {
        rachete.push_back(racheta);
    }

    return rachete;
}

ostream& operator<<(ostream& out, const Racheta& racheta) {
    out << "ID: " << racheta.getId() 
        << ", Capacitate: " << racheta.getCapacitate() << " kg"
        << ", Consum: " << racheta.getConsum1000() << " kg/1000 km"
        << ", Combustibil disponibil: " << racheta.getCombustibilDisponibil() << " kg"
        << ", Pret combustibil: " << racheta.getPretCombustibil() << " $/kg"
        << ", Nr. misiuni efectuate: " << racheta.getNrMisiuniEfectuate()
        << ", Profit brut total: " << racheta.getProfitTotalBrut() << " $"
        << ", Profit net total: " << racheta.getProfitTotalNet() << " $"
        << ", Cost total: " << racheta.getCostTotal() << " $"
        << ", Scor eficienta: " << racheta.getScorEficienta()
        << ", Km ramasi: " << racheta.getMaxRange() << " km"
        << ", Factor utilitate: " << racheta.getFactorUtilitate();
    return out;
}

// Fucntii de scris linii in CSV
void afiseazaProfitTotalCSV(ofstream& out, const Racheta& racheta) {
    out << racheta.id << ";" << racheta.profitTotalBrut << ";"
        << racheta.costTotal << ";" << racheta.profitTotalNet << endl;
    return;
}

void afiseazaClasamentRachetaCSV(ofstream& out, const Racheta& racheta, int loc) {
    out << loc << ";"
        << racheta.id << ";"
        << racheta.profitTotalNet << ";"
        << racheta.nrMisiuniEfectuate << ";"
        << racheta.scorEficienta << endl;
    return;
}
#pragma endregion
