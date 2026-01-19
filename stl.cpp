#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<vector>
using namespace std;

enum stare {
	deschisa = 1,
	rezolvata = 2
};

class Petitie {
	string dataDepunere;
	stare starePetitie;
	bool areRaspuns; //0-nu; 1-da
	char* descriere;
	static int termen;

public:
	Petitie() {
		dataDepunere = "fara data";
		starePetitie = deschisa;
		areRaspuns = 0;
		descriere = nullptr;
	}

	Petitie(string dataDepunere, stare starePetitie, bool areRaspuns, const char* descriere) {
		this->dataDepunere = dataDepunere;
		this->starePetitie = starePetitie;
		this->areRaspuns = areRaspuns;
		if (descriere != nullptr) {
			this->descriere = new char[strlen(descriere) + 1];
			strcpy_s(this->descriere, strlen(descriere) + 1, descriere);
		}
	}

	Petitie(const Petitie& m) {
		this->dataDepunere = m.dataDepunere;
		this->starePetitie = m.starePetitie;
		this->areRaspuns = m.areRaspuns;
		if (m.descriere != nullptr) {
			this->descriere = new char[strlen(m.descriere) + 1];
			strcpy_s(this->descriere, strlen(m.descriere) + 1, m.descriere);
		}
		else {
			this->descriere = nullptr;
		}
	}

	Petitie& operator=(const Petitie& m) {
		if (this != &m) {
			if (this->descriere != nullptr) {
				delete[] this->descriere;
			}
			this->dataDepunere = m.dataDepunere;
			this->starePetitie = m.starePetitie;
			this->areRaspuns = m.areRaspuns;
			if (m.descriere != nullptr) {
				this->descriere = new char[strlen(m.descriere) + 1];
				strcpy_s(this->descriere, strlen(m.descriere) + 1, m.descriere);
			}
			else {
				this->descriere = nullptr;
			}
		}
		return *this;
	}

	virtual ~Petitie() {
		if (this->descriere != nullptr)
			delete[] this->descriere;
	}

	Petitie& operator~() {
		if (areRaspuns == 1)
			this->starePetitie = rezolvata;
		return *this;
	}
	
	virtual void ceva() {
		cout << "petitie normala";
	}

	stare getStare() {
		return starePetitie;
	}
};
int Petitie::termen = 30;

class PetitieUrgenta : public Petitie{
	//se adauga toate elementele din clasa petitie dar eu nu mai stau sa ii rescriu

	void ceva() override {
		cout << "Petitie Urgenta";
	}
};

int main() {
	Petitie p1("2024-05-10", deschisa, false, "Groapa pe strada");
	Petitie p2("2024-05-11", rezolvata, true, "Lumina stinsa");
	Petitie p3("2024-05-12", deschisa, false, "Zgomot nocturn");

	map<stare, vector<Petitie>> registru; //am facut un map care ordoneaza dupa stare, un vector de petitii
	registru[p1.getStare()].push_back(p1); //incepem sa grupam in fct de stare
	registru[p2.getStare()].push_back(p2);
	registru[p3.getStare()].push_back(p3);

	cout << "Petitii: " << endl;
	for (auto& pet : registru[rezolvata]) {
		cout << "o petitie rezolvata";		//sau putem afisa efectiv petitiile
	}
	for (auto& pet : registru[deschisa]) {
		cout << "o petitie deschisa";
	}
}
