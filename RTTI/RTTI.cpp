// RTTI.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <typeinfo>

class BaseNotVirtual {

};

class DeliveredNotVirtual : public BaseNotVirtual {

};

class Base {
public:
    virtual ~Base() = default;
};

class Delivered : public Base {
public:

};

// Dziedzicznie wirtualne jest specjalnym przypadkiem w dziedziczeniu wielobazowym, które stosuje się, gdy z jakiegoś powodu jedna z klas staje się wielokrotnie przodkiem (bezpośrednio lub pośrednio) innej klasy. Np.
// Zatem jeśli chcemy wyraźnie wskazać, że jakaś klasa jest bazową dla wszystkich potomków, to przy w deklaracji musimy dodać słowo kluczowe virtual przy nazwie klasy z której dziedziczymy. 
// Wówczas zniknie niejednoznaczność odwołań do jej składowych, natomiast jej pola zostaną umieszczone w klasie pochodnej tylko raz. W przykładzie poniżej rozmiar Klasy to 1kB + kilka bajtów, bez dziedziczenia wirtualnego byłoby to ponad 2kB, oraz oczywiście wywołanie metody wyswietl (używając takiego zapisu) byłoby niemożliwe.
// w przypadku takiego dziedzieczenia, pola klasy zostana mieszczone tylko raz (np. z jednej klasy bazowej), unikniemy wted niejednoznacznosci

int main()
{
    // Omowie dzialnie typeid w kontekscie obiektow polimorficznych i nie polimorficznych
    DeliveredNotVirtual deliveredNotVirtual{};
    BaseNotVirtual& baseNotVirtual = dynamic_cast<BaseNotVirtual&>(deliveredNotVirtual);
    
    // typeid jest wyolywany w czasie kompilacji, wiec nie ma tutaj mowy o dzialaniu runtimeowy - dzieje sie tka poniewaz typy sa niepolimorficzne
    // zwraca Class BaseNotVirtual
    std::cout << "typeinfo for base not virtual reference: " << typeid(baseNotVirtual).name() << std::endl;

    // zwraca class DeliveredNotVirtual
    std::cout << "typeinfo for delivered not virtual reference: " << typeid(deliveredNotVirtual).name() << std::endl;

    Delivered delivered{};
    Base& base = dynamic_cast<Base&>(delivered);

    //  tutaj juz typeid potrafi rozpoznac co tam jest pod spodem i zwraca class Delivered
    std::cout << "typeinfo for base virtual reference: " << typeid(base).name() << std::endl;

    // zwraca class Delivered
    std::cout << "typeinfo for delivered virtual reference: " << typeid(delivered).name() << std::endl;

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
