#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Produs {
	char* denumire;
	int cantitate;
	float pret;

public:
	Produs() {
		denumire = nullptr;
		cantitate = 0;
		pret = 0;
	}

	Produs(const char* denumire, int cantitate, float pret) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
		else
			this->denumire = nullptr;
		this->cantitate = cantitate;
		this->pret = pret;
	}

	Produs(const Produs& p) {
		if (p.denumire != nullptr) {
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);
		}
		else
			this->denumire = p.denumire;
		this->cantitate = p.cantitate;
		this->pret = p.pret;
	}

	Produs& operator=(const Produs& p) {
		if (this != &p) {
			if (this->denumire != nullptr) {
				delete[] this->denumire;
			}
			if (p.denumire != nullptr) {
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);
			}
			else
				this->denumire = p.denumire;
			this->cantitate = p.cantitate;
			this->pret = p.pret;
		}
		return *this;
	}

	~Produs() {
		if (this->denumire != nullptr) {
			delete[] this->denumire;
		}
	}

	float getValoare() {
		return pret * cantitate;
	}

	void serializare(ofstream& f) {
		int lungime;
		if (denumire != nullptr) {
			lungime = strlen(denumire);
			f.write((char*)&lungime, sizeof(lungime));
			f.write(denumire, lungime + 1);
		}
		else {
			lungime = 0;
			f.write((char*)&lungime, sizeof(lungime));
		}
		f.write((char*)&cantitate, sizeof(cantitate));
		f.write((char*)&pret, sizeof(pret));
	}

	void deserializare(ifstream& f) {
		int lungime = 0;
		f.read((char*)&lungime, sizeof(lungime));
		delete[] denumire;
		if (lungime > 0) {
			denumire = new char[lungime + 1];
			f.read(denumire, lungime + 1);
		}
		else
			denumire = nullptr;
		f.read((char*)&cantitate, sizeof(cantitate));
		f.read((char*)&pret, sizeof(pret));
	}

	friend ostream& operator<<(ostream& out, Produs p);
	friend istream& operator>>(istream& in, Produs& p);
	friend ofstream& operator<<(ofstream& f, Produs p);
	friend ifstream& operator>>(ifstream& f, Produs& p);
};

ostream& operator<<(ostream& out, Produs p) {
	if (p.denumire != nullptr)
		out << p.denumire << endl;
	else
		out << "N/A" << endl;
	out << p.cantitate << endl;
	out << p.pret << endl;;
	return out;
}

istream& operator>>(istream& in, Produs& p) {
	char buffer[100];
	in.get(buffer, 99);
	if (p.denumire != nullptr)
		delete[] p.denumire;
	if (buffer != nullptr) {
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);
	}
	in >> p.cantitate;
	in >> p.pret;
	in.ignore();
	return in;
}

ofstream& operator<<(ofstream& f, Produs p) {
	if (f.is_open()) {
		if (p.denumire != nullptr)
			f << p.denumire << endl;
		else
			f << "N/A" << endl;
		f << p.cantitate << endl;
		f << p.pret << endl;
	}
	return f;
}

ifstream& operator>>(ifstream& f, Produs& p) {
	if (f.is_open()) {
		char buffer[100];
		f.get(buffer, 99);
		if (p.denumire != nullptr)
			delete[] p.denumire;
		if (buffer != nullptr) {
			p.denumire = new char[strlen(buffer) + 1];
			strcpy_s(p.denumire, strlen(buffer) + 1, buffer);
		}
		f >> p.cantitate;
		f >> p.pret;
		f.ignore();
	}
	return f;
}

class Magazin {
	string nume;
	char* patron;
	int nrProduse;
	Produs* produse;
	const int suprafata;
	static string oras;

public:
	Magazin() :suprafata(0){
		nume = "N/A";
		patron = nullptr;
		nrProduse = 0;
		produse = nullptr;
	}

	Magazin(string nume, const char* patron, int nrProduse, const Produs* produse, int suprafata) :suprafata(suprafata) {
		this->nume = nume;
		if (patron != nullptr) {
			this->patron = new char[strlen(patron) + 1];
			strcpy_s(this->patron, strlen(patron) + 1, patron);
		}
		else
			this->patron = nullptr;
		this->nrProduse = nrProduse;
		if (nrProduse > 0 && produse != nullptr) {
			this->produse = new Produs[nrProduse];
			for (int i = 0; i < nrProduse; i++)
				this->produse[i] = produse[i];
		}
		else {
			this->produse = nullptr;
			this->nrProduse = 0;
		}
	}

	Magazin(const Magazin& m) :suprafata(m.suprafata){
		this->nume = m.nume;
		if (m.patron != nullptr) {
			this->patron = new char[strlen(m.patron) + 1];
			strcpy_s(this->patron, strlen(m.patron) + 1, m.patron);
		}
		else
			this->patron = nullptr;
		this->nrProduse = m.nrProduse;
		if (m.nrProduse > 0 && m.produse != nullptr) {
			this->produse = new Produs[m.nrProduse];
			for (int i = 0; i < m.nrProduse; i++)
				this->produse[i] = m.produse[i];
		}
		else {
			this->produse = nullptr;
			this->nrProduse = 0;
		}
	}

	Magazin& operator=(const Magazin& m) {
		if (this != &m) {
			this->nume = m.nume;
			if (this->patron != nullptr)
				delete[] this->patron;
			if (m.patron != nullptr) {
				this->patron = new char[strlen(m.patron) + 1];
				strcpy_s(this->patron, strlen(m.patron) + 1, m.patron);
			}
			else
				this->patron = nullptr;
			this->nrProduse = m.nrProduse;
			if (this->produse != nullptr)
				delete[] this->produse;
			if (m.nrProduse > 0 && m.produse != nullptr) {
				this->produse = new Produs[m.nrProduse];
				for (int i = 0; i < m.nrProduse; i++)
					this->produse[i] = m.produse[i];
			}
			else {
				this->produse = nullptr;
				this->nrProduse = 0;
			}
		}
		return *this;
	}

	~Magazin() {
		if (this->patron != nullptr)
			delete[] this->patron;
		if (this->produse != nullptr)
			delete[] this->produse;
	}

	float getValoareTotala() {
		float total = 0;
		for (int i = 0; i < nrProduse; i++)
			total = total + produse[i].getValoare();
		return total;
	}

	void serializare() {
		ofstream f("magazin.bin", ios::binary | ios::out);
		int lungime = 0;
		lungime = nume.length();
		f.write((char*)&lungime, sizeof(lungime));
		f.write(nume.c_str(), lungime + 1);
		if (patron != nullptr) {
			lungime = strlen(patron);
			f.write((char*)&lungime, sizeof(lungime));
			f.write(patron, lungime + 1);
		}
		else {
			lungime = 0;
			f.write((char*)&lungime, sizeof(lungime));
		}
		if (nrProduse > 0 && produse != nullptr) {
			f.write((char*)&nrProduse, sizeof(nrProduse));
			for (int i = 0; i < nrProduse; i++)
				produse[i].serializare(f);
		}
		else {
			lungime = 0;
			f.write((char*)&lungime, sizeof(lungime));
		}
		f.close();
	}

	void deserializare() {
		ifstream f("magazin.bin", ios::binary | ios::in);
		int lungime = 0;
		f.read((char*)&lungime, sizeof(lungime));
		char* p = new char[lungime + 1];
		f.read(p, lungime + 1);
		nume = p;
		delete[] p;
		p = nullptr;
		lungime = 0;
		delete[] patron;
		f.read((char*)&lungime, sizeof(lungime));
		if (lungime > 0) {
			patron = new char[lungime + 1];
			f.read(patron, lungime + 1);
		}
		else {
			patron = nullptr;
		}
		f.read((char*)&nrProduse, sizeof(nrProduse));
		delete[] produse;
		if (nrProduse > 0) {
			produse = new Produs[nrProduse];
			for (int i = 0; i < nrProduse; i++)
				produse[i].deserializare(f);
		}
		else {
			produse = nullptr;
		}
		f.close();
	}

	friend ostream& operator<<(ostream& out, Magazin m);
	friend istream& operator>>(istream& in, Magazin& m);
	friend ofstream& operator<<(ofstream& f, Magazin m);
	friend ifstream& operator>>(ifstream& f, Magazin& m);
};
string Magazin::oras = "Bucuresti";

ostream& operator<<(ostream& out, Magazin m) {
	out << m.nume << endl;
	if (m.patron != nullptr)
		out << m.patron << endl;
	else
		out << "N/A" << endl;
	if (m.nrProduse > 0 && m.produse != nullptr) {
		out << m.nrProduse << endl;
		for (int i = 0; i < m.nrProduse; i++)
			out << m.produse[i] << endl;
	}
	else {
		out << 0 << endl;
		out << endl;
	}
	out << m.suprafata << endl;
	out << m.oras << endl;
	return out;
}

istream& operator>>(istream& in, Magazin& m) {
	getline(in, m.nume);
	char buffer[100];
	in.getline(buffer, 100);
	if (m.patron != nullptr)
		delete[] m.patron;
	m.patron = new char[strlen(buffer) + 1];
	strcpy_s(m.patron, strlen(buffer) + 1, buffer);
	in >> m.nrProduse;
	if (m.produse != nullptr)
		delete m.produse;
	if (m.nrProduse > 0) {
		m.produse = new Produs[m.nrProduse];
		for (int i = 0; i < m.nrProduse; i++)
			in >> m.produse[i];
	}
	in >> const_cast<int&>(m.suprafata);
	return in;
}

ofstream& operator<<(ofstream& f, Magazin m) {
	if (f.is_open()) {
		f << m.nume << endl;
		if (m.patron != nullptr)
			f << m.patron << endl;
		else
			f << "N/A" << endl;
		if (m.nrProduse > 0 && m.produse != nullptr) {
			f << m.nrProduse << endl;
			for (int i = 0; i < m.nrProduse; i++)
				f << m.produse[i] << endl;
		}
		else {
			f << 0 << endl;
			f << endl;
		}
		f << m.suprafata << endl;
		f << m.oras << endl;
	}
	return f;
}

ifstream& operator>>(ifstream& f, Magazin& m) {
	if (f.is_open()) {
		getline(f, m.nume);
		char buffer[100];
		f.getline(buffer, 100);
		if (m.patron != nullptr)
			delete[] m.patron;
		m.patron = new char[strlen(buffer) + 1];
		strcpy_s(m.patron, strlen(buffer) + 1, buffer);
		f >> m.nrProduse;
		if (m.produse != nullptr)
			delete[] m.produse;
		if (m.nrProduse > 0) {
			m.produse = new Produs[m.nrProduse];
			for (int i = 0; i < m.nrProduse; i++) {
				f.ignore();
				f >> m.produse[i];
			}
		}
		f >> const_cast<int&>(m.suprafata);
	}
	return f;
}

int main() {
	Produs b("branza", 12, 2.5);
	cout << b << endl;
	cout << "testam fisierul text" << endl;
	ofstream f("produs.txt", ios::out);
	f << b;
	Produs b2;
	ifstream g("produs.txt", ios::in);
	g >> b2;
	cout << b2 << endl;
	Produs b3;
	cout << "testam serializarea" << endl;
	ofstream l("produs.bin", ios::binary| ios::out);
	b2.serializare(l);
	l.close();
	ifstream t("produs.bin", ios::binary| ios::in);
	b3.deserializare(t);
	t.close();
	cout << b3 << endl;
	cout << b.getValoare();

	cout << "magazine:" << endl << endl << endl;
	Produs lista[] = { b, b2, b3 };
	Magazin m("Lidl", "lidal", 3, lista, 100);
	cout << m;
	cout << "testam fisierul text" << endl;
	ofstream h("magazin.txt", ios::out);
	h << m;
	Magazin m3;
	ifstream k("magazin.txt", ios::in);
	k >> m3;
	cout << m3;
	cout << "serializare" << endl;
	m3.serializare();
	Magazin m4;
	m4.deserializare();
	cout << m4;
}