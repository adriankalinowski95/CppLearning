// Cast.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

class Test2 {
public:
    Test2(int val) : m_val{ val } {}

    int getVal() {
        return m_val;
    }

private:
    int m_val;
};

class Test1 {
public:
    Test1(int val) : m_val{ val } {}
    Test1(Test2& test) : m_val{test.getVal()} {}
private:
    int m_val;
};


class BaseNonVirtual {
public:
    BaseNonVirtual(int val) : m_val{ val } {}

protected:
    int m_val;
};

class DeliveredNonVirtual : public BaseNonVirtual {
public:
    DeliveredNonVirtual(int val) : 
        BaseNonVirtual{ val } {}
};

class Base {
public:
    Base(int val) : m_val { val } {}

    int getVal() {
        return m_val;
    }

private:
    int m_val;
};

class Delivered : public Base {
public:
    Delivered(int val) : 
        Base{ val } {}
};

class BaseVirtual {
public:
    virtual ~BaseVirtual() = default;
    BaseVirtual(int val) : m_val{ val } {}

    int getVal() {
        return m_val;
    }

private:
    int m_val;
};

class DeliveredVirtual : public BaseVirtual {
public:
    DeliveredVirtual(int val) :
        BaseVirtual{ val } {}
};


int main() {
   //  static_cast - rzutowanie statyczne dzialajace podczas kompilacji.Potrafi zamieniac zmienne z uwzglednieniem wartosci - nie bezposrednio bitowe
   double doubleValue = 25.43;
   int intVal = static_cast<int>(doubleValue);
   
   // static_cast pozwala rzutowac obiekty, ktore posiadaja rzutowanie explicity (jawna konwersja) 
   Test2 test2{25};
   Test1 test1 = static_cast<Test1>(test2);

   // static_cast pozwala na rzutowanie obietkow zarowno w gore jak i w dol MUSI BYC REFERENCJA/PTR
   DeliveredNonVirtual delivered1{23};
   // w gore
   BaseNonVirtual& base1 = static_cast<BaseNonVirtual&>(delivered1);

   // w dol
   DeliveredNonVirtual& deliveredCast = static_cast<DeliveredNonVirtual&>(base1);

   int intVal2 = static_cast<int>(23);

   // Nie mozna rzutowac jezeli nie ma wyrobionej konwersji



   // const_cast sluzy do rzutowania zarowno na const jak i na usuwaniu const lub volatile
   const int intConstVal{23};

   
   int intNonConst = static_cast<int>(intConstVal);

   const int intConstVal2 = static_cast<const int>(intNonConst);

   // optymalizacja na niego nie dziala, zawsze jet zapisywany w pamieci i nie wplywa na niego optymalizacja
   volatile int volatileInt = 43;
   volatileInt = 32;
   // moze rzutowac ale tylko na ptr
   int* nonVolatileInt = const_cast<int*>(&volatileInt);

   // -----------------------------------------------------------------------------------------
   // dynamic_cast rzutowanie w gore i w dol, tylko w sposob dynamiczny podczas dzialania programu
   Delivered delivered2{23};
   // w ta strone mozna
   Base* base2 = dynamic_cast<Base*>(&delivered2);

   // w ta nie, bo nie ma elementow virtualnych!!!
   // Delivered* delivered3 = dynamic_cast<Delivered*>(base2);

   DeliveredVirtual delivered3{ 23 };
   // w ta strone mozna bo jest wirttualny
   BaseVirtual* base3 = dynamic_cast<BaseVirtual*>(&delivered3);

   // w dol mozna, bo jest wirtalny
   DeliveredVirtual* delivered4 = dynamic_cast<DeliveredVirtual*>(base3);


   // rzutowanie w dol - jezeli nie uda nam sie zrzutowac to zwroci nullptr
   Delivered* delivered5 = dynamic_cast<Delivered*>(base3);
   if (delivered5 == nullptr) {
        std::cout << "dobre zachowanie!, poniewaz delivered nie dziedizczy po baseVirtual" << std::endl;
   }

   // gdy to zrobimy dla referencji to rzuci exception
   try {
       Delivered& delivered6 = dynamic_cast<Delivered&>(*base3);
   }
   catch (std::bad_cast& exception) {
       std::cout << "bad cast! " << exception.what()  << std::endl;
   }

   // tutaj mozemy dostac czysty pointer, dobra sprawa tak na prawde
   void* ptr = dynamic_cast<void*>(base3);

   // ---------------------------------------------------------------------------------------------------------
   // reinterpret_cast sluzy do rzutowania na rrozne typy z zachowaniem jego bitow - bezj akiej konwerwersji jak to jest w static_cast
   // Operator reinterpret_cast służy do rzutowania wskaźników na zmienne typu całkowitego lub do zamiany typu wskaźników.
   float* wf = new float;
   // zmienna typu float zajmuje 4 bajty pamięci
   *wf = 33.2;
   int* wi = reinterpret_cast<int*>(wf);
   // zmienna int zajmuje również 4 bajty pamięci
   std::cout << "float: " << *wf << " ---> int: " << *wi << std::endl;
   // ten sam układ bitów, ale inna interpretacja

   long int adres = 0x7fff85a697f0;
   double dbl = 1;
   // ustawienie wskaźnika na adres
   long int* wsk = reinterpret_cast<long int*>(adres);
   std::cout << "Wskaźnik wsk wskazuje na: " << wsk << std::endl;
   // przypisanie wskaźnikowi nowego adresu
   wsk = reinterpret_cast<long int*>(&dbl);
   std::cout << " Teraz wsk wskazuje na: " << wsk << std::endl;


   // uzyskanie adresu
   int intval2 {23};
   long int ptrToIntVal2 = reinterpret_cast<long int>(&intval2);

   const char *c_strVal ="abcd";

   int* intrPtrFromCstrVal = reinterpret_cast<int*>(const_cast<char*>(c_strVal));

   std::cout << "int val after reintpret cast " << intrPtrFromCstrVal << std::endl;
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
