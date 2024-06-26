// MoveAndOthers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

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

	Constructors(Constructors&& constructor) {
		std::cout << "(Constructors&&)" << std::endl;
	}

	Constructors& operator=(Constructors&& constructor) {
		std::cout << "(Constructors&&=)" << std::endl;

		return *this;
	}

	~Constructors() {
		std::cout << "destructor" << std::endl;
	}

	int val{5};
};

void fun(Constructors constructors) {

}

Constructors&& moveConstrucotrs() {
	// i tak obiekt jest tworzony tymaczoso, po czym usuwany, czyli generuje to o jedna mniej kopie
	return {};
}

Constructors coppyConstrucotrs() {
	return {};
}


class Test {
public:
	// w tym przykladzie zostanie wywoalny zwykly konstruktor kopiujacy, poniewaz pomimo takiego tyupu(a to znaczy dostania sie rvalue, constructors jest lvalue(ma alias czy tam zmienna itp), aby to naprawic trzeba dodac std::move();
	Test(Constructors&& constructors) : 
		m_constructors{ constructors }{}

	Constructors m_constructors;
};


class Test2 {
public:
	// ulepszona wersja z std::move
	Test2(Constructors&& constructors) :
		m_constructors{ std::move(constructors) } {}

	Constructors m_constructors;
};

int main()
{
	Constructors constructor{};

	// wywolanie konstruktora kopiujacego
	auto coppyConstructorExample = constructor;

	// wywoalnie konstruktora przenoszacego
	auto moveConstructorExample = std::move(constructor);

	// wywolanie konstrutkroa kopiujacego, poniewaz tam mamy doczynienia z zwyklym przekazaniem przez wartosc
	fun(moveConstructorExample);

	Constructors newConstructor1{};
	Constructors newConstructor2{};

	// wywolanie operatora przypisania
	newConstructor1 = newConstructor2;

	// wywolaine operatora przeniesienia
	newConstructor1 = std::move(newConstructor2);

	// konstruktor przenoszenia
	auto newConstructorMovedFromFunction = moveConstrucotrs();

	// operator przenoszenia
	newConstructorMovedFromFunction = moveConstrucotrs();

	// RVO
	auto byCoppyConstructors = coppyConstrucotrs();

	// W zasadize to move sluzy tylk o iwylacznie po to, żeby poniformowac że obiekt nadaje sie do przenoszenia. Np. mozna to zrobic w taki sosob, że tworzymy obiekty i sa r value(jedno stworzenie), po czym sa przenoszone

	Test test{{}};

	// obiekt tymczasowy zostal zmowowany a potem zostal wywoalny destruktor.
	Test2 test2{ {} };

	// podsumowujac - przy tworzeniu nowych obiektow zawsze jest uzywany move konstruktor(jezeli damy std::move(object))
	// jezeli chcemy uzywac operator move, to musimy juz do stworoznego obiektu przypisac wartosc rfrence(std::move(object))

	// zmienne tymczasowe, w rzeczywistosci nie sa r-value, ale l

	// Return Value Optimization (w skrócie RVO) 
	// Almost Always Auto - teoria mowiaca o tym ze zawsze powinnismy uzywac auto

	// w rzeczywistosci w pierwszej kolejnosc 
	//  Co jednak, jeśli powiem Wam, że operator . do działania (poprawnej kompilacji) potrzebuje po swojej lewej stronie glvalue? Można to łatwo sprawdzić w standardzie:
	// A więc wiedząc tylko to, Foo{}.printMe(); nie powinno się skompilować, ponieważ wyrażenie po lewej stronie kropki jest prvalue, które glvalue nie jest. Jak to się więc dzieje, że program się kompiluje?
	//Nie trudno się domyślić, że za tym wszystkim stoi właśnie konwersja prvalue na glvalue.A więc na czym to polega ?
	//Za każdym razem, kiedy kompilator spodziewa się glvalue, a dostaje wyrażenie prvalue, 
	// następuje process nazywany temporary materialization conversion(po polsku przetłumaczylibyśmy to prawdopodobnie jako konwersja materializacji zmiennych tymczasowych).Proces materializacji zmiennej tymczasowej polega na dwóch rzeczach : po pierwsze utworzeniu obiektu takiego jak tymczasowy, który będzie posiadał swój adres, a następnie zmianie wyrażenia na xvalue.
	// Powiedzieliśmy, że ten obiekt tymczasowy będzie posiadał swój adres w pamięci, ale ktoś może się doczepić, że przecież :
	// Foo{}.printMe();

	std::cout << "end of move tests" << std::endl;
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
