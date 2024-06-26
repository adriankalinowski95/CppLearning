// TemplatesAndForwarding.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>

// rozpatrywania r/l value i perfect forwardingu.
// przy rvalue jest tak, że jezeli je odstajemy to wiemy ze dana zmienna moze byc movowana - my gdy piszemy taki kod, po prostu informujemy ze do danej funkcji o takiej parametrze mozemy zrobic move, po to, zeby zoptymalizowac kod
// perfect forwarding - templatowa metoda, polegajaca na tym, że przekazujemy do tworzymy funkcje, ktora przyjmie wszystkie typy - dodatkowo zawiera informajce o tym, czy to bylo r value czy l value
// swietnie do tego nadaja sie forward, bo on potrafi wyluskac te dane i stwierdzic, czy zmienna ktora przekazalismy nadaje sie do movawania, cz ynie.

// Jezeli parametr szablonu funkcji am typ T%% dla dedukwanego typu T albo jezeli obiekt jest zadeklarowany przy uzyciu auto&& ten parametr lub obiekt jest odwolaniem uniwersalnym
// Jezeli deklaruacja typu nie ma dokladine formy typ%% lub jesli dedukcja typu nie wystpuje(nie jest to template), oznacza odwolanie do r wartosci
// odwolanie uniwersalne odpowiadaja odwolaniom do r wartosci, jezeli sa inicjowane rwartoscami. Odpowiadaj odwolaniam do l-wartosci jezeli sa inicjowane l-wartoscami.


template <typename T>
void universalReference(T&& val) {

}

class Constructors {
public:
	Constructors() {
		std::cout << "()" << std::endl;
	}

	Constructors(const Constructors& constructor) {
		std::cout << "(const Constructors& constructor)" << std::endl;
	}

	Constructors& operator=(const Constructors& constructor) {
		std::cout << "(Constructors&=)" << std::endl;

		return *this;
	}

	Constructors(Constructors&& constructor) noexcept {
		std::cout << "(Constructors&&)" << std::endl;
	}

	Constructors& operator=(Constructors&& constructor) {
		std::cout << "(Constructors&&=)" << std::endl;

		return *this;
	}

	~Constructors() {
		std::cout << "destructor" << std::endl;
	}

	int val{ 5 };
};


Constructors getConstructorsWithMove(Constructors&& onstructors) {
	return std::move(onstructors);
}

void tempFunWithLRef(Constructors& constructors) {
	std::cout << "lref!" << std::endl;
}

Constructors getByRvo() {

	Constructors constructors{};
	
	// nie potrzeba robic std::move(constructors), bo w zasadzie rvo robi to za nas
	// do funkcji przekazuje adres obiektu gdzie jest tworzony, i ta zmienna lokalna jest tam wpisywana
	// warunki:
	// Kompilatory powinny pomijac kopiowanie (lub przenoszenie) lokalnych obiektow w funkcji, ktore zwraca przez artosc, jesli:
	// 1. Typ obiektu lokalnego jest taki sam jak zwracany przez funkcje
	// 2. Obiekt lokalny jest tym co jest zwracane
	// Oba warunki sa spelnione w tescie, czyli kompialtor uzyje rvo
	// nie mozna robic std::move(constructors), poniewaz obiekt nie spelnia drugieg punktu - nie bedzie lokalnym,a refrenecja do lokalnego
	return constructors;
}
// stosuj std::move do odwolnad do r-wartosci a std::forward do odwolnan uniersalnych przy kazdym ich uzyciu
// to samo dotyczy odwolnan do r-watosci i odwolan uniwersalnych zwracanych przez funkcje zwracajace prez wartosc - czyli jezeli przekazemy typ R&& do funkcji i chcemy go potem zwtrocic to uzywajmy std::mvoe lub std::forward (dla uniwersalnego przekazania)
// nigdy nie stosuj std::move ani std::forward do obiektow lokalnych jesli w przeciwnym przypadku podlegalby optymalizacji wartosci zwracanej RVO

// przyklad z perfect fowardogiiem
// funkcja przyjumej uniwersal reference, po to zeby rozpoznawac czy obiekt, ktory przekazujemy nadaje sie do skopiowania, czy do przeniesienia
template <typename T>
void addToVector(T&& value, std::vector<Constructors>& values) {
	values.push_back(std::forward<T>(value));
}

// WAZNE!!!!! przykladoo int na short jest konwertowany w wyniku promocji, wiec uniwersal reference bedzie przed promocja!!! moze to rodzic problemy - przyklad

template <typename T>
void doSmth(T&& ref) {
	//...
}

void doSmth(int ref) {
	//..
}

// i teraz
// gdy stworzymy zmienna short val i przekazemy do funkcji, to wybierze dosmth z uniwersal ref zamiast tej z intem
// nie laczyc uniwersal reference z przeciazanimi funkcji !!!!!!!!!!!!!!!!!!
//
// jezeli wystapienie funkcji szablonowej i zwyklej funkcji tak samo pasuje do kodu, to kompilator wybierze ta zwykla


// przyklad z konstruktorem
// NIE ROBIC TAK!!!!
// W tym przypadku zostal wygenerowany konsturktor kopiujacy, ktory ma paraemtr const Per& per
// Jezeli przekazemy obiekt nie const, to wywoalmy konsturko z uniwersal refenrece, zamiast kopujacego!!!!!!!!!!!!!!!
class Per {
public:
	template <typename T>
	Per(T&& v) {}
};

template <typename T>
void univrsalReferenceTag(T&& val, std::false_type) {
	// tutaj mozemy sobie robic to z perfect fowardingiem std::forward
	std::cout << "universal refernece tag" << std::endl;
}

void univrsalReferenceTag(int val, std::true_type) {
	// tutaj sobie elegankco obsluguejmy
	std::cout << "val tag" << std::endl;
}

// uniwersal reference z tag dispatchem:
template <typename T>
void universalReference2(T&& val) {
	univrsalReferenceTag(std::forward<T>(val), std::is_integral<typename std::remove_reference_t<T>>::type());
}

// najwiekszy problem w tym jest to, że w konsturktroach kopiujacych mamy element const, przez co gdy przekazemy nie const parametr, to wywolamy uniwersal reference

// SFINAE - substition failure is not error - blad podstawienie nie jest bledem - mechanizm polegajacy na tym, ze jezeli nie da sie podstawic typu do danej definicji wybiera inna - przyklad

// chcielibysmy zeby funkcja ta przyjmowala 
class Per2 {
public:
	// enable if_t zwraca typ, jezeli go nie ma(czyli tak na prawde wartosc przekazana do parametru enable_if_t<tutaj_wartosc>, byla false, to nie ma zadnego typu (false definicja nei ma typu), wiec jest pustka, a tym smym nie pasuje do tej 
	// is integral sprawdza czy typ przekazany jest pdobony int lub jego promocja, 
	template <
	typename T,
	typename = std::enable_if_t<
		!std::is_integral_v<std::remove_reference_t<T>>
	>
	>
	Per2(T&& v) {
		std::cout << "universal reference constructor" << std::endl;
	}

	Per2(int val)  {
		std::cout << "int constructor" << std::endl;
	}

};

// PODSUMOWANIE:
// Jezeli mamy uniwersal reference zawsze musiym stosotwac std::forward, po to ,zeby wykonac albo pzeniesienie (zrzutwoac typ na &&), albo zwykly konstruktor kopiujacy
// jezeli w parametrze mamy jakis obiekt, ap otem go zwracamy, tez powinnismy uzyc std::forward do zwracania
// uniwersalna referencja potrafi rozoznawac czy przekazany obiekt jest r czy l refernece
// laczy sie z std::forward
// nie zwracajmy z std;:move dla obiektow lokalnych bo robi za nas to RVO

int main()
{
    std::cout << "Hello World!\n";

	// w tym przypadku, zmienna zostanie utworzona za pomoca move construcota, poniewaz go posiada. Gdyby tego nie miala, zostala by utworzona za pomoca copy construcora
	// Fajny trick polega na tym, że jezeli damy gdzies rvalue, a dana funkcja nie posiada tego to i tak zostanie zrutwoanaa na lvalue ref
	auto initializationByMovConstructor = getConstructorsWithMove({});

	auto rvoTest = getByRvo();

	std::vector<Constructors> cunstroctorVec;
	Constructors lValConstrucotr{};

	// przekazujemy lvalref, czyli obiekt zostanie skopiowany
	addToVector(lValConstrucotr, cunstroctorVec);

	// przekazujemy rvalref, czyli obiekt zostanie przeniesiony
	addToVector(Constructors{}, cunstroctorVec);


	// rozowiazanie problemy z przeciazeniami
	int val{};

	universalReference2(val);
	universalReference2(53);
	universalReference2("abc");

	short shortVal = 43;
	Per2 shortPer2{ shortVal };

	Per2 stringPEr{"abc"};

	std::cout << "END!" << std::endl;;
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
