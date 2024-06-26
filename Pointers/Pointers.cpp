// Pointers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>


// unique_ptr
// Wskaźnik std::unique_ptr uosabia semantykę wyłącznego posiadania. Wskaźnik
// std::unique_ptr o wartości innej niż null zawsze posiada to, co wskazuje.Przenoszenie
// wskaźnika std::unique_ptr powoduje zmianę stanu posiadania z wskaźnika
// źródłowego na docelowy. (Wskaźnik źródłowy przyjmuje wartość null).

// W ramach destrukcji wskaźnik std::unique_ptr o wartości innej niż null niszczy
// swój zasób.Domyślnie destrukcja zasobu jest przeprowadzana przez zastosowanie
// instrukcji delete do wskaźnika surowego wewnątrz wskaźnika std::unique_ptr.

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor" << std::endl;
    }

    Base(int val) : m_val{ val } {}
    virtual void fun() {
        std::cout << "base " << m_val << std::endl;
    }

protected:
    int m_val;
};

class Delivered : public Base {
public:
    ~Delivered() {
        std::cout << "Delivered destructor " << std::endl;
    }

    Delivered(int val) : 
        Base(val) {}

    void fun() override {
        std::cout << "delivered " << m_val << std::endl;
    }
};

auto customDeleter = [](Base* base) {
    delete base;
};

std::unique_ptr<Base, decltype(customDeleter)> objectFactory() {
    std::unique_ptr<Base, decltype(customDeleter)> v(new Delivered{123}, customDeleter);

    return v;
}


class Widget : public std::enable_shared_from_this<Widget> {
public:
    // funkcja fabrykująca, która doskonale przekazuje argumenty
    // do prywatnego konstruktora
    template<typename... Ts>
    static std::shared_ptr<Widget> create(Ts&&... params) {
        return shared_from_this();
    }

private:
   // konstruktory
};


int main()
{
    std::cout << "Hello World!\n";

    auto object = objectFactory();
    object->fun();

    auto objectByMake = std::make_unique<Delivered>(6666);
    objectByMake->fun();

    // Delivered destructor
    // Base destructor


    /*
        Obecność licznika odwołań ma wpływ na wydajność:
         Wskaźniki std::shared_ptr mają rozmiar dwóch wskaźników surowych,
        ponieważ wewnętrznie zawierają wskaźnik surowy do zasobu oraz wskaźnik
        surowy do licznika odwołań do zasobu8.
         Pamięć licznika odwołań musi być dynamicznie przydzielana. Koncepcyjnie
        licznik odwołań jest skojarzony z wskazywanym obiektem, ale wskazywane
        obiekty nic o tym nie wiedzą. Dlatego nie mają miejsca na przechowywanie
        licznika odwołań. (W miły sposób wynika z tego, że dowolny obiekt – nawet
        o typie wbudowanym – może być zarządzany przez wskaźniki std::shared_ptr).
        Punkt 21 zawiera objaśnienie, że możemy uniknąć kosztu dynamicznego
        przydziału pamięci, tworząc wskaźnik std::shared_ptr za pomocą funkcji
        std::make_shared, ale istnieją sytuacje, gdy nie da się jej użyć. Tak czy owak,
        licznik odwołań jest przechowywany jako dynamicznie alokowane dane.
         Zwiększanie i zmniejszanie licznika odwołań musi być atomowe, ponieważ
        w różnych wątkach mogą występować równoczesne odczyty i zapisy. Na przykład
        w jednym wątku wskaźnik std::shared_ptr do pewnego zasobu może
        wykonywać destruktor (stąd zmniejsza licznik odwołań do wskazywanego
        obiektu), a z kolei w innym wątku inny wskaźnik std::shared_ptr do tego samego
        zasobu może być kopiowany (w ten sposób zwiększając ten sam licznik
        odwołań). Operacje atomowe są zwykle wolniejsze niż operacje nieatomowe,
        więc chociaż liczniki odwołań mają zwykle rozmiar jednego słowa, należy
        założyć, że operacje odczytu i zapisu w tych licznikach są względnie kosztowne.
    */

    // std::shared_ptr<Widget> // typ deletera nie jest
    //     spw(new Widget, loggingDel); // częścią typu wskaźnika

    // (control block).
    // std::shared_ptr<T>
    // Wskaznik do T                        -> Obiekt T
    // Wskaznik do bloku kontrolnego    
    //
    // Blok kontrolny
    // Licznik odwołan
    // Licznik słabych odwołan
    // Inne dane (np.niestandardowy deleter, alokator itp.)

    // Funkcja std::make_shared (patrz punkt 21) zawsze tworzy blok kontrolny.
    // Sporządza nowy obiekt do wskazania, więc w momencie wywołania funkcji
    // std::make_shared na pewno nie ma bloku kontrolnego dotyczącego tego obiektu

    // Blok kontrolny jest tworzony, gdy wskaźnik std::shared_ptr jest tworzony
    // na podstawie wskaźnika posiadania wyłącznego(czyli std::unique_ptr lub
    // std::auto_ptr).Wskaźniki posiadające wyłącznie nie korzystają z bloków
    // kontrolnych, więc nie powinno być żadnego bloku kontrolnego dotyczącego
    // wskazywanego obiektu. (W ramach konstrukcji wskaźnik std::shared_ptr
    // przejmuje posiadanie wskazywanego obiektu, więc wskaźnik wcześniej posiadający
    // wyłącznie ma nadawaną wartość null).


    // Kiedy konstruktor std::shared_ptr jest wywoływany z wskaźnikiem surowym,
    // tworzy blok kontrolny.Jeżeli chcemy utworzyć wskaźnik std::shared_ptr
    // na podstawie obiektu, który już miał blok kontrolny, przypuszczalnie jako argument
    // konstruktora przekażemy obiekt std::shared_ptr lub std::weak_ptr(patrz
    //     punkt 20), a nie wskaźnik surowy.Konstruktory wskaźników std::shared_ptr
    // przyjmujące argumenty std::shared_ptr lub std::weak_ptr nie tworzą nowych
    // bloków kontrolnych, ponieważ mogą polegać na przekazywaniu przez wskaźniki
    // inteligentne wszystkich niezbędnych bloków kontrolnych.


    // Konsekwencją tych reguł jest to, że utworzenie więcej niż jednego wskaźnika
    // std::shared_ptr na podstawie pojedynczego wskaźnika surowego przypomina
    // darmową przejażdżkę akceleratorem cząstek o niezdefiniowanym zachowaniu,
    // ponieważ wskazywany obiekt będzie miał wiele bloków kontrolnych.Wiele bloków
    // kontrolnych oznacza wiele liczników odwołań, a wiele liczników odwołań oznacza,
    // że obiekt będzie niszczony wielokrotnie(raz dla każdego licznika odwołań).Oznacza
    // to, że taki kod jest bardzo, bardzo zły :


    auto pw = new Delivered(232); // pw to wskaźnik surowy
    
    std::shared_ptr<Base> spw1(pw, customDeleter); // tworzenie bloku
    // kontrolnego dla *pw
    
    std::shared_ptr<Base> spw2(pw, customDeleter); // tworzenie drugiego
    // bloku kontrolnego
    // dla *pw!

    spw1->fun();


    //  Wskaźniki std::shared_ptr zapewniają wygodę zbliżoną do samoczynnego
    // odzyskiwania pamięci w przypadku zarządzania cyklem życia współdzielonych,
    // arbitralnych zasobów.
    //  W porównaniu ze wskaźnikiem std::unique_ptr, obiekty std::shared_ptr
    // są dwukrotnie większe, pociągają za sobą nadmiarowość związaną z blokami
    // kontrolnymi i wymagają atomowych manipulacji licznikiem odwołań.
    //  Domyślnie niszczenie zasobów odbywa się za pomocą instrukcji delete, ale
    // są też obsługiwane niestandardowe deletery.Typ deletera nie ma wpływu
    // na typ wskaźnika std::shared_ptr.
    //  Należy unikać tworzenia wskaźników std::shared_ptr na podstawie zmiennych,
    // których typem jest wskaźnik surowy.

    auto weak = std::weak_ptr<Base>(spw1);

    if (!weak.expired()) {
        auto shared = weak.lock();

        shared->fun();
    }

    //  Stosuj obiekty std::weak_ptr w przypadku wskaźników przypominających
    // obiekty std::shared_ptr, które mogą zawisnąć.
    //  Potencjalne przypadki użycia wskaźników std::weak_ptr obejmują buforowanie,
    // listy obserwatorów oraz zapobieganie cyklom wskaźników
    // std::shared_ptr.


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

