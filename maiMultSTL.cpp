#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

enum tipFirzerie {
	salon, clasica, barbershop
};

class Serviciu {
public:
	virtual ~Serviciu(){}

	virtual int calculPret() = 0;
	virtual string getNume() = 0;
};

class Tuns :public Serviciu {
	int pret;
public:
	Tuns() {
		pret = 0;
	}

	~Tuns() {}

	int calculPret() override {
		return 10;
	}

	string getNume() override {
		return "Tuns";
	}
};

class Frezat :public Serviciu {
	int pret;
public:
	Frezat() {
		pret = 0;
	}

	~Frezat() {}

	int calculPret() override {
		return 15;
	}

	string getNume() override {
		return "Frezat";
	}
};

class Barbierit :public Serviciu {
	int pret;
public:
	Barbierit() {
		pret = 0;
	}

	~Barbierit() {}

	int calculPret() override{
		return 20;
	}

	string getNume() override {
		return "Barbierit";
	}
};

class Frizerie {
	char* denumire;
	tipFirzerie tip;
	int nrFrizeri;
	static int lungimeMinimaDenumire;
	
	//vector de pointeri
	vector<Serviciu*> servicii;
	
public:
	Frizerie() {
		denumire = nullptr;
		nrFrizeri = 0;
		tip = salon;
	}

	Frizerie(const char* denumire, tipFirzerie tip, int nrFrizeri, vector<Serviciu*> servicii) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
		else
			this->denumire = nullptr;
		this->tip = tip;
		this->nrFrizeri = nrFrizeri;
		this->servicii = servicii;
	}

	Frizerie(const Frizerie& f) {
		if (f.denumire != nullptr) {
			this->denumire = new char[strlen(f.denumire) + 1];
			strcpy_s(this->denumire, strlen(f.denumire) + 1, f.denumire);
		}
		else
			this->denumire = nullptr;
		this->tip = f.tip;
		this->nrFrizeri = f.nrFrizeri;
		this->servicii = f.servicii;
	}

	Frizerie& operator=(const Frizerie& f) {
		if (this != &f) {
			if (this->denumire != nullptr)
				delete[] this->denumire;
			if (f.denumire != nullptr) {
				this->denumire = new char[strlen(f.denumire) + 1];
				strcpy_s(this->denumire, strlen(f.denumire) + 1, f.denumire);
			}
			else
				this->denumire = nullptr;
			this->tip = f.tip;
			this->nrFrizeri = f.nrFrizeri;
			this->servicii = f.servicii;
		}
		return *this;
	}

	~Frizerie() {
		if (this->denumire != nullptr)
			delete[] this->denumire;
		for (auto s : servicii) {	
			delete s;
		}
		servicii.clear();
	}

	static void setLungiemMinima(int lungime) {
		lungimeMinimaDenumire = lungime;
	}

	int getLungimeMinima() {
		return lungimeMinimaDenumire;
	}

	void setDenumire(const char* denumire){
		if (strlen(denumire) >= lungimeMinimaDenumire) {
			if (this->denumire != nullptr)
				delete[] this->denumire;
			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
	}

	string getDenumire() {
		if (this->denumire != nullptr) {
			string copie = this->denumire;
			return copie;
		}
		else
			return "N/A";
	}

	void serializare() {
		ofstream f("frizerie.bin", ios::binary);
		int lungime = 0;
		if (denumire != nullptr) {
			lungime = strlen(denumire);
			f.write((char*)&lungime, sizeof(lungime));
			f.write(denumire, lungime + 1);
		}
		else {
			lungime = 0;
			f.write((char*)&lungime, sizeof(lungime));
		}
		f.write((char*)&tip, sizeof(tip));
		f.write((char*)&nrFrizeri, sizeof(nrFrizeri));
		f.close();
	}

	void deserializare() {
		ifstream f("frizerie.bin", ios::binary);
		int lungime = 0;
		f.read((char*)&lungime, sizeof(lungime));
		delete[] denumire;
		if (lungime > 0) {
			denumire = new char[lungime + 1];
			f.read(denumire, lungime + 1);
		}
		else {
			denumire = nullptr;
		}
		f.read((char*)&tip, sizeof(tip));
		f.read((char*)& nrFrizeri, sizeof(nrFrizeri));
		f.close();
	}

	int calculPretTotal(){
		int pretTotal = 0;
		for (auto s : servicii) {
			pretTotal = pretTotal + s->calculPret();
		}
		return pretTotal;
	}

	void operator+=(Serviciu* s) {
		servicii.push_back(s);
	}

	void operator-=(Serviciu* s) {
		for (auto i = servicii.begin(); i != servicii.end(); ++i) {
			if ((*i)->getNume() == s->getNume()) {
				servicii.erase(i);
				break;
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Frizerie& f) {
		if (f.denumire != nullptr)
			out << f.denumire << endl;
		else
			out << "null" << endl;
		out << f.tip << endl;
		out << f.nrFrizeri << endl;
		return out;
	}
};
int Frizerie::lungimeMinimaDenumire = 1;

int main() {
	Frizerie f1;
	Serviciu* s1 = new Tuns();
	Serviciu* s2 = new Barbierit();
	Serviciu* s3 = new Frezat();
	vector<Serviciu*> servicii = { s1,s2,s3 };
	Frizerie f2("la mihai", tipFirzerie::barbershop, 3, servicii);
	Frizerie f3 = f2;
	Frizerie::setLungiemMinima(5);
	f3.setDenumire("el saloon");
	cout << f3.getDenumire() << endl;

	cout << f1.getDenumire() << " " << f2.getDenumire() << endl;
	cout << f1.getLungimeMinima() << endl;

	f2.serializare();
	Frizerie f4;
	f4.deserializare();
	cout << f4 << endl;

	cout << f2.calculPretTotal() << endl;
	f2 += s1;
	cout << f2.calculPretTotal() << endl;
	f2 -= s1;
	cout << f2.calculPretTotal() << endl;

	map<string, int> catalog;
	catalog["Tuns"] = 35;
	catalog["Frezat"] = 25;
	catalog["Barbierit"] = 10;

	string serviciuCautat = "Tuns";
	cout << serviciuCautat << " costa " << catalog[serviciuCautat] << endl;
}
