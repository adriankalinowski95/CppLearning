// Expressions.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

int& getIntRef(){
    static int val = 53;

    return val;
}

struct Bar {
    int m;
};



int main()
{
    //      expressinos
    //   glValue   rValue
    // lValue xValue prValue
    
    // czym jest glValue?
    // glvalue jest to wyrazenie, ktorego wynikiem jest referencja do jzu istniejacego obiektu albo gdy odnosnimy sie do obiektu przez jej nazwe

    // -------------------------------------
    // lvalue jest to kazde wyrazenie, ktore nie przenosi wartosci zmiennej i jest gvalue, jest tez lvalue - czyli w zasadzie zwykl referencje

    // wyrazenie te to lvalue, poniewaz jest glvalue(zwraca referencje do obiektu), ale tylko zwykla referencje(&), wiec jest nieprzenoszalne
    auto& intRef = getIntRef(); 

    // a tez jest lvalue, bo tyczy sie zmiennej ktora istnieje
    int a = 53;

    // lValue
    int& aRef = a;

    Bar bar;

    // to lvalue
    // bar
    auto& m = bar.m;
    // Łatwo wywnioskować, że jeżeli zwracany typ wyrażenia jest postaci T&, lub odnosi się przez nazwę do nazwanej zmiennej, to wyrażenie jest lvalue.

    // ---------------------------------------
    // xvalues
    // xvalues jest to, że zasoby obiektu mogą być ponownie użyte stąd nazwa - eXpiring values.   rvalue referencje.

    Bar bar2{};
    auto&& bar2RRef = static_cast<Bar&&>(bar2); // wyrażenie xvalue

    // bar2 lvalue
    // static_cast<Bar&&>(bar2) - wyrazenie jest xvalue bo zwraca obiekt, ktory jest ref i nadaje sie do ponownego uzycia

    // wywoalnie konstrutkora przenoszacego
    // bar2 nie nadaje sie juz do powonego uzycia, bo juz zostalo przeniesione do bar3
    Bar bar3(static_cast<Bar&&>(bar2));

    // Dzieje się tak z prostego powodu: Jeżeli obiekt, do którego membera próbujemy się dostać jest xvalue, czyli jego zasoby mogą zostać p
    // Nie dziala dla typow referencyjnych, ponieważ, takie typy z definicji sa zwyklymi referencjami, czyli nie powinnismy ich przenosic. Obiekt nie zarzadza czasem ich zycia Stąd prawdopodobnie nie powinniśmy przywłaszczać sobie jego zasobów.
    auto&& m= std::move(bar3).m;
    // tak samo dzieje sie da ptr oraz tablicy
    // std::move(arr)[0]; //rvalue referencja do pierwszego elementu tablicy
    
    // Podsumowując, xvalues to wszystkie wyrażenia, których wynik jest typu rvalue referencja.!!!!!!!!!!!

    // -------------------------------------------
    //  Nie pozostało nam więc nic innego jak wyrażenia zwracające wartości i jak nie trudno się domyślić są to właśnie wyrażenia prvalues.

    // struct Foo {};
    // Foo foo();
    // 
    // 5; // prvalue
    // Foo{}; // prvalue
    // foo(); // prvalue

    // PO prostu sa prvalue, poniewaz sa to wartosci ktore nie istnieja jeszcze, ale zwracaja obiekt, inaczej mowia sa to rrreferencje

   // “l - value” refers to a memory location that identifies an object.“r - value” refers to the data value that is stored at some address in memory.References in C++ are nothing but the alternative to the already existing variable.They are declared using the ‘& ’ before the name of the variable.
    int aa = 10;

    // Declaring lvalue reference
    int& lref = aa;

    // Declaring rvalue reference
    int&& rref = 20;


    struct Foo {
        void printMe() { std::cout << "foo" << std::endl; }
    };

    /**/

    Foo{}.printMe();

  //  Na pierwszy rzut oka wszystko gra.Wszyscy są przyzwyczajeni do tworzenia tymczasowych zmiennych, na których wykonują pewne operacje.Co jednak, jeśli powiem Wam, że operator . do działania(poprawnej kompilacji) potrzebuje po swojej lewej stronie glvalue ? Można to łatwo sprawdzić w standardzie :
  //A więc wiedząc tylko to, Foo{}.printMe(); nie powinno się skompilować, ponieważ wyrażenie po lewej stronie kropki jest prvalue, które glvalue nie jest.Jak to się więc dzieje, że program się kompiluje ?

  //Nie trudno się domyślić, że za tym wszystkim stoi właśnie konwersja prvalue na glvalue.A więc na czym to polega ?

   //Za każdym razem, kiedy kompilator spodziewa się glvalue, a dostaje wyrażenie prvalue, następuje process nazywany temporary materialization conversion(po polsku przetłumaczylibyśmy to prawdopodobnie jako konwersja materializacji zmiennych tymczasowych).Proces materializacji zmiennej tymczasowej polega na dwóch rzeczach : po pierwsze utworzeniu obiektu takiego jak tymczasowy, który będzie posiadał swój adres, a następnie zmianie wyrażenia na xvalue.
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
