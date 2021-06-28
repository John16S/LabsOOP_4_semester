#include <iostream>
#include <ctime>;
using namespace std;

/* Class instrumenti dlya sozdaniye programmnoe obespe4eniye */
class instrumenti_PO
{
private:
	char* official_name = NULL;
	int year;
	char* kod_name; // kodovoe nazvaniye
	double version; // versia
	char* realize_data; // data vihoda

public:
	instrumenti_PO(); // Constructor po umol4aniyu
	instrumenti_PO(char* Of_name, int Year, char* Kod_nazvaniye, double vers, char* real_data); // Constructor s parametri
	~instrumenti_PO(); // destructor
	instrumenti_PO(const instrumenti_PO& s); // kopiruyushiy constructor

	void copy(const instrumenti_PO& s); // metod kopirovaniye

	int get_year() const; // Metod vozvrashayushiy zna4eniye pole year

	virtual void set_all();	// Izmeneniye poley objecta classa
	virtual void get_all();

	instrumenti_PO& operator=(const instrumenti_PO& po); // operator prisvaivaniye
	bool operator>(instrumenti_PO& s);
	friend ostream& operator<<(ostream& out, const instrumenti_PO& s);

	/*	- СС vizivaetcay, kogda noviy object sozdayetcya iz sushestvuyushego
		objecta, kak kopiya sushestvuyushego objecta.
		- AO vizivaetcay, kogda oba objecta uzhe sozdani i mi prisvaevaem
		odin drugomu. primer: a = b	*/
};

/* Conteyner-class v vide Steka*/
class conteiner {
private:
	struct Stack {
		instrumenti_PO* Data = NULL;
		Stack* Next = NULL;
	};
	Stack* top;

public:
	conteiner(); // constructor po umol4aniyu
	~conteiner(); // deconstructor po umol4aniyu
	void Push(instrumenti_PO* PO); // metod dobavleniye objecta v stek
	void Pop(); // metod udaleniye objecta iz steka
	void Get_po(); // metod vivoda poley objecta v steke
	void Search() const; // metod dlya poiska
	void Compare() const; // metod sravneniye
	void Sorting(); // metod dlya sortirovaniye elementov steka
};

/* proizvodniy class - instrumenti dlya web-development */
class instrumenti_web :public instrumenti_PO {
private:
	char* prog_lang;
public:
	instrumenti_web() :instrumenti_PO(), prog_lang() {}
	instrumenti_web(char* Of_name, int Year, char* Kod_nazvaniye,
		double vers, char* Real_data, char* prog_lang)
		:instrumenti_PO(Of_name, Year, Kod_nazvaniye, vers, Real_data),
		prog_lang(prog_lang) {}

	void set_all();
	void get_all();
};

/* proizvodniy class - PO dlya oper_system */
class PO_for_OS :public instrumenti_web {
private:
	char* Oper_system;
public:
	PO_for_OS() :instrumenti_web(), Oper_system() {}
	PO_for_OS(char* Of_name, int Year, char* Kod_nazvaniye,
		double vers, char* Real_data, char* prog_lang, char* op_sys)
		:instrumenti_web(Of_name, Year, Kod_nazvaniye, vers, Real_data, prog_lang),
		Oper_system(Oper_system) {}

	void set_all();
	void get_all();
};

/* proizvodniy class - PO dlya Ustroistvo */
class PO_for_device :public PO_for_OS {
private:
	char* device;
public:
	PO_for_device() :PO_for_OS(), device() {}
	PO_for_device(char* Of_name, int Year, char* Kod_nazvaniye,
		double vers, char* Real_data, char* prog_lang, char* op_sys, char* Device)
		:PO_for_OS(Of_name, Year, Kod_nazvaniye, vers, Real_data, prog_lang, op_sys),
		device(device) {}

	void set_all();
	void get_all();
};

int main() {
	srand(time(NULL));

	instrumenti_PO a1;
	instrumenti_web a2;
	PO_for_OS a3;
	PO_for_device a4;

	a1.set_all(); cout << "_____________________________________________" << endl;
	a2.set_all(); cout << "_____________________________________________" << endl;
	a3.set_all(); cout << "_____________________________________________" << endl;
	a4.set_all(); cout << "_____________________________________________" << endl;

	conteiner st;
	st.Push(&a1);
	st.Push(&a2);
	st.Push(&a3);
	st.Push(&a4);
	system("cls");

	st.Get_po();
	system("pause");
	system("cls");

	cout << "Search: " << endl;
	st.Search();
	system("pause");
	system("cls");

	cout << "Compare: " << endl;
	st.Compare();
	system("pause");
	system("cls");

	cout << "Sorted: " << endl;
	st.Sorting();
	st.Get_po();

	system("pause");
	return 0;
}

/*----------------------------------------------------------*/
			/* Constructors of "intrumenti_PO" class */
/*----------------------------------------------------------*/
instrumenti_PO::instrumenti_PO() { // Constructor po umol4aniyu
	char Default[] = "default";

	this->official_name = new char[strlen(Default) + 1];
	strcpy_s(this->official_name, strlen(Default) + 1, Default);

	year = 0;

	this->kod_name = new char[strlen(Default) + 1];
	strcpy_s(this->kod_name, strlen(Default) + 1, Default);

	version = 0;

	this->realize_data = new char[strlen(Default) + 1];
	strcpy_s(this->realize_data, strlen(Default) + 1, Default);
}

instrumenti_PO::instrumenti_PO(char* Of_name, int Year, char* Kod_nazvaniye, double vers, char* Real_data) { // konstructor s parametri
	official_name = new char[strlen(Of_name) + 1];
	strcpy_s(official_name, strlen(Of_name) + 1, Of_name);

	year = Year;

	kod_name = new char[strlen(Kod_nazvaniye) + 1];
	strcpy_s(kod_name, strlen(Kod_nazvaniye) + 1, Kod_nazvaniye);

	version = vers;

	realize_data = new char[strlen(Real_data) + 1];
	strcpy_s(realize_data, strlen(Real_data) + 1, Real_data);
}

instrumenti_PO::~instrumenti_PO() { // Dodestructor
	if (official_name != NULL) delete[] official_name;
	if (kod_name != NULL) delete[] kod_name;
	if (realize_data != NULL) delete[] realize_data;
}

instrumenti_PO::instrumenti_PO(const instrumenti_PO& po) { // kopiruyushiy constructor
	official_name = new char[strlen(po.official_name) + 1];
	strcpy_s(official_name, strlen(po.official_name) + 1, po.official_name);

	year = po.year;

	kod_name = new char[strlen(po.kod_name) + 1];
	strcpy_s(kod_name, strlen(po.kod_name) + 1, po.kod_name);

	version = po.version;

	realize_data = new char[strlen(po.realize_data) + 1];
	strcpy_s(realize_data, strlen(po.realize_data) + 1, po.realize_data);
}

void instrumenti_PO::copy(const instrumenti_PO& po) { //metod kopirovaniye poley odnogo objecta v drugoy
	if (official_name != NULL) delete[] official_name;
	if (po.official_name != NULL) {
		official_name = new char[strlen(po.official_name) + 1];
		strcpy_s(official_name, strlen(po.official_name) + 1, po.official_name);
	}

	year = po.year;

	if (kod_name != NULL) delete[] kod_name;
	if (po.kod_name != NULL) {
		kod_name = new char[strlen(po.kod_name) + 1];
		strcpy_s(kod_name, strlen(po.kod_name) + 1, po.kod_name);
	}

	version = po.version;

	if (realize_data != NULL) delete[] realize_data;
	if (po.realize_data != NULL) {
		realize_data = new char[strlen(po.realize_data) + 1];
		strcpy_s(realize_data, strlen(po.realize_data) + 1, po.realize_data);
	}
}

int instrumenti_PO::get_year() const { // Metod vozvrashayushiy zna4eniye pole year
	return year;
}

void instrumenti_PO::set_all() {
	char name[25], kod[20], r_date[25];
	int ye;
	double ver;

	cout << "Enter Name: "; cin >> name;
	if (this->official_name != NULL) delete[] this->official_name;
	this->official_name = new char[strlen(name) + 1];
	strcpy_s(this->official_name, strlen(name) + 1, name);

	ye = rand() % 11 + 2011;
	this->year = ye;

	cout << "Kodovoe nazvaniye: "; cin >> kod;
	if (this->kod_name != NULL) delete[] this->kod_name;
	this->kod_name = new char[strlen(kod) + 1];
	strcpy_s(this->kod_name, strlen(kod) + 1, kod);

	this->version = (rand() % 10) / 5.0 + 1.1;

	cout << "Realize date: "; cin >> r_date;
	if (this->realize_data != NULL) delete[] this->realize_data;
	this->realize_data = new char[strlen(r_date) + 1];
	strcpy_s(this->realize_data, strlen(r_date) + 1, r_date);
}

void instrumenti_PO::get_all() {
	cout << "Official_name: " << official_name << endl;
	cout << "Year: " << year << endl;
	cout << "Kodovoe nazvaniye: " << kod_name << endl;
	cout << "Version: " << version << endl;
	cout << "Realize date: " << realize_data << endl;
}

instrumenti_PO& instrumenti_PO::operator=(const instrumenti_PO& po) { //metod kopirovaniye poley odnogo objecta v drugoy
	if (this != &po) {
		if (official_name != NULL) delete[] official_name;
		if (po.official_name != NULL) {
			official_name = new char[strlen(po.official_name) + 1];
			strcpy_s(official_name, strlen(po.official_name) + 1, po.official_name);
		}

		year = po.year;

		if (kod_name != NULL) delete[] kod_name;
		if (po.kod_name != NULL) {
			kod_name = new char[strlen(po.kod_name) + 1];
			strcpy_s(kod_name, strlen(po.kod_name) + 1, po.kod_name);
		}

		version = po.version;

		if (realize_data != NULL) delete[] realize_data;
		if (po.realize_data != NULL) {
			realize_data = new char[strlen(po.realize_data) + 1];
			strcpy_s(realize_data, strlen(po.realize_data) + 1, po.realize_data);
		}
		return *this;
	}
}

bool instrumenti_PO::operator>(instrumenti_PO& s) { //peregruzka operatora sravneniya ">"
	return year > s.year;
}

ostream& operator<<(ostream& out, const instrumenti_PO& s) { // peregruzka operatora "cout <<";
	out << "____________________________________________\n";
	out << "Official_name: " << s.official_name << endl;
	out << "Year: " << s.year << endl;
	out << "Kodovoe nazvaniye: " << s.kod_name << endl;
	out << "Version: " << s.version << endl;
	out << "Realize date: " << s.realize_data << endl;
	return out;
}
/*========================================================================*/

/*----------------------------------------------------------*/
			/* Constructors of "conteiner" class */
/*----------------------------------------------------------*/
conteiner::conteiner() {
	top = NULL;
}

conteiner::~conteiner() {
	Stack* tmp = top;
	while (tmp != NULL) {
		top = top->Next;
		delete(tmp);
		tmp = top;
	}
	delete(top);
}

void conteiner::Push(instrumenti_PO* PO) {
	Stack* tmp = new Stack;
	tmp->Next = top;
	top = tmp;
	top->Data = PO;
}

void conteiner::Pop() {
	Stack* tmp = top;
	top = top->Next;
	delete(tmp);
}

void conteiner::Get_po() {
	Stack* tmp = top;
	cout << "_______________________\n";
	while (tmp != NULL) {
		tmp->Data->get_all();
		cout << "_______________________\n";
		tmp = tmp->Next;
	}
}

void conteiner::Compare() const {
	int YEAR;
	cout << "Enter year: "; cin >> YEAR;
	Stack* tmp = top;
	cout << "_______________________\n";
	while (tmp != NULL) {
		if (tmp->Data->get_year() >= YEAR) {
			tmp->Data->get_all();
			cout << "_______________________\n";
		}
		tmp = tmp->Next;
	}
}

void conteiner::Sorting()
{
	Stack* tmp = top;
	int g = 0;
	while (tmp != NULL) {
		g++;
		tmp = tmp->Next;
	}
	int size = g;

	instrumenti_PO** mas = new instrumenti_PO * [size];
	g = 0;
	tmp = top;
	while (tmp != NULL) {
		mas[g++] = tmp->Data;
		tmp = tmp->Next;
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (mas[i]->get_year() < mas[j]->get_year()) {
				instrumenti_PO* tmp = mas[i];
				mas[i] = mas[j];
				mas[j] = tmp;
			}
		}
	}

	tmp = top;
	while (tmp != NULL) {
		top = top->Next;
		delete(tmp);
		tmp = top;
	}

	for (int i = 0; i < size; i++) {
		Push(mas[i]);
	}
	delete[] mas;
}

void conteiner::Search() const
{
	int YEAR;
	cout << "Enter year: "; cin >> YEAR;
	Stack* tmp = top;
	cout << "_______________________\n";
	while (tmp != NULL) {
		if (tmp->Data->get_year() == YEAR) {
			tmp->Data->get_all();
			cout << "_______________________\n";
		}
		tmp = tmp->Next;
	}
}
/*===================================================================*/


/*----------------------------------------------------------*/
	/* Constructors of conteiner "Instrumenti_web" class*/
/*----------------------------------------------------------*/
void instrumenti_web::set_all() {
	instrumenti_PO::set_all();

	char new_lang[25];
	cout << "Enter New_Prog_lang: "; cin >> new_lang;
	if (this->prog_lang != NULL) delete[] this->prog_lang;
	this->prog_lang = new char[strlen(new_lang) + 1];
	strcpy_s(this->prog_lang, strlen(new_lang) + 1, new_lang);
}

void instrumenti_web::get_all() {
	instrumenti_PO::get_all();
	cout << "New_Prog_Lang: " << prog_lang << endl;
}
/*===================================================================*/


/*----------------------------------------------------------*/
		/* Constructors of "PO_for_OS" class */
/*----------------------------------------------------------*/
void PO_for_OS::set_all() {
	instrumenti_web::set_all();

	char PO_OS[25];
	cout << "Enter oper_system: "; cin >> PO_OS;
	if (this->Oper_system != NULL) delete[] this->Oper_system;
	this->Oper_system = new char[strlen(PO_OS) + 1];
	strcpy_s(this->Oper_system, strlen(PO_OS) + 1, PO_OS);
}

void PO_for_OS::get_all() {
	instrumenti_web::get_all();
	cout << "Oper_system: " << Oper_system << endl;
}
/*===================================================================*/


/*----------------------------------------------------------*/
			/* Constructors of "PO_for_Device" class */
/*----------------------------------------------------------*/
void PO_for_device::set_all() {
	PO_for_OS::set_all();

	char Dev[25];
	cout << "Device: "; cin >> Dev;
	if (this->device != NULL) delete[] this->device;
	this->device = new char[strlen(Dev) + 1];
	strcpy_s(this->device, strlen(Dev) + 1, Dev);
}

void PO_for_device::get_all() {
	PO_for_OS::get_all();
	cout << "Device: " << device << endl;
}
/*===================================================================*/