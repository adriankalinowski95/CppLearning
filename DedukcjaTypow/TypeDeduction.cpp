// DedukcjaTypow.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

// deklaracja typow
// w templatach w zaleznosci od ich typu przekazanych roznie rozpoznajemy typ oraz typename template <T> - t oznacza typ, a paramtype o calosc po lewej
//  template<typename T> 
// void fun(ParamType param) 
// wywolanie wyglada tak: fun(expr);

//  - ParamType to wskaźnik lub typ referencyjny, ale nie jest odwołaniem uniwersalnym.
//  (Odwołania uniwersalne są opisane w punkcie 24. Teraz wystarczy wiedzieć,
//    że istnieją i różnią się od odwołań do l - wartości i odwołań do r - wartości).
//  - ParamType to odwołanie uniwersalne.
//  - ParamType nie jest ani wskaźnikiem, ani odwołaniem.


// Przypadek 1: ParamType to odwołanie lub wskaźnik, ale nie odwołanie uniwersalne
// 1. Jeśli typ wyrażenia expr to odwołanie, zignoruj jego referencyjność.
// 2. Następnie dopasuj do wzorca typ wyrażenia expr względem ParamType, aby wyznaczyć T.

template <typename T>
void f1(T& param) {

}


// Przypadek 2: ParamType jest odwołaniem uniwersalnym
// Jezeli expr to l-param, to zarówno T jak i ParamType jest deklarowany jako odwolanie do l-wartosci. Jest to jedyna sytuacja gdzie T jest dedukowany jako odwolanie.
// Po drugie, chociaz ParamType jest deklarowany przy uzyciu sklady dnia Rwartosci, to typ jest dedukowany jako odwolanie do l-wartosci.
// Dedukckcja typow rozroznia odowlania do lwartosci od odwolan do rwartosci

template <typename T>
void f2(T&& param) {

}

// Przypadek 3: ParamType nie jest ani wskaźnikiem, ani odwołaniem

template <typename T>
void f3(T param) {

}

// 1. Jezeli typ expr jest referencja, to ignorujemy ja
// 2. Const i VOlatile tez igonrujemy, ponieważ jest to kopia. Mozemy ja bezpieczenie modyfikowac.


// zwraca auto, a ze auto jest zwykle(bez referencjI) to zwraca zwykle T, vo jest problemme., bo tutaj chcielibsmy zwrocic referencje do T (T&)
template<typename Container, typename Index> // C++14;
auto authAndAccess(Container& c, Index i) // nie całkiem
{ // prawidłowo
  //  authenticateUser();
    return c[i]; // zwracany typ dedukowany z c[i]
}

// aby to zrobic musimy napisac cos takiego
// tu zwraca T&
template<typename Container, typename Index> // C++14;
decltype(auto) authAndAccess(Container& c, Index i) // nie całkiem
{ // prawidłowo
  //  authenticateUser();
    return c[i]; // zwracany typ dedukowany z c[i]
}

/*

const int i = 0;                // decltype(i) to const int
bool f(const Widget& w);        // decltype(w) to const Widget&
                                // decltype(f) to bool(const Widget&)
struct Point {
int x, y;                       // decltype(Point::x) to int
};                              // decltype(Point::y) to int
Widget w;                       // decltype(w) to Widget
if (f(w)) …                     // decltype(f(w)) to bool
template<typename T> // uproszczona wersja std::vector











*/

int main()
{
    int x = 23;
    const int cx = x;
    const int& rx = x;


    f1(x); // T to int, typ param to int&
    f1(cx); // T to const int, param to const int&
    f1(rx); // T to const int, param to const int&

    // gdy zmodyfkuje T& na const T& zachowanie bedzie analogiczne. T dalej bedzie takie same, ale w pierwszym przypadku (x) type param bedzie const int&
    // z wskaznikami jest analogicznie.

    f2(x);  // T to int&, typ param to int&
    f2(cx);  // T to const int&, paramtype to const int&
    f2(rx);  // T to const int&, paramtype to const int&
    f2(23);  // T to int,  paramtype to int&&

    f3(x);  // T to int, type param to int
    f3(cx); // T to int, type param to int
    f3(rx); // T to int, type param to int

    // w przypadku const char *, wlasciwosc const dalej zostaje

    // podobnie jak w 
    auto&& uref1 = x; // x to l-wartość typu int, więc typ uref1 to int&
    auto&& uref2 = cx; // cx to l-wartość typu const int, więc typ uref2 to const int&
    auto&& uref3 = 27; // 27 to r-wartość typu int, więc typ uref3 to int&&

    auto x3 = { 27 }; // typ to std::initializer_list<int>,

    //auto x5 = { 1, 2, 3.0 }; // błąd! nie można wydedukować T dla std::initializer_list<T>

    //
    // - Dedukcja typów auto zwykle przebiega tak samo jak dedukcja typów w szablonach,
    // ale w dedukcji typów auto założono, że inicjator klamrowy reprezentuje
    // std::initializer_list, inaczej niż w dedukcji typów w szablonach.
    // - Słowo kluczowe auto określające typ zwracany przez funkcję lub parametr
    // w wyrażeniu lambda powoduje dedukcję typów w szablonie, a nie dedukcję
    // typów auto.

    // Punkt 3: decltype

    // Wprzeciwieństwie do tego, co dzieje się podczas dedukcji typów w szablonach
    //    i auto (patrz punkty 1 i 2), instrukcje decltype zwykle powtarzają dokładnie typ
    //    nazwy lub wyrażenia, które podamy :

   // -Instrukcja decltype prawie zawsze pozwala otrzymać typ zmiennej lub
   //     wyrażenia bez żadnych modyfikacji.
   //     - W przypadku wyrażeń stanowiących l - wartości typu T, ale innych niż
   //     nazwy, instrukcja decltype zawsze zgłasza typ T& .
   //     - Język C++14 obsługuje instrukcję decltype(auto), która podobnie jak auto
   //     powoduje dedukcję typu na podstawie jego inicjatora, ale przeprowadza
   //     ją przy użyciu reguł decltype.




    std::cout << "End!\n";
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
