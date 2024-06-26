// SequenceContainers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <deque>

// Kontener sekwencyjny - Elementy, ktore wrzucamy do kontenera są przechowywaan właśnie w takiej kolejnośći w jakiej je umieszczamy.
// W nich wystepuje tylko stala i linjowa zlozonosc!!!!!!!!!!!!

// Wspolne funkcje:
// front() - pobranie pierwszego elementu
// empty()
// max_size()
// iteratory begin i end() - begin wskaznuje na pierwszy element, end na element za ostatnim
// stale iteratory - iteratory na stale wartosci - bez modyfikacji. cbegin() i cend()
// swap - podmienia zawartosc kntenerow

// Array
// dostepne metody
// jak sa ulozone w pamieci
// jaka jest zlozonosc obliczeniowa operacji (stala lub linjowa)

// Vector
// CECHY:
// - jeden ciagly obszar pamieci
// - cache friendly - operacje beda sie bardzo szybko, dlatego ze elementy sa ulozone jeden po drugim
// ZMIENNE:
// size - ilosc elementow w wektorze
// capacity - pojemnosc wektora - wedlug jednej implementacji za kazdym razem jak sie konczy, wielkosc wektora sie podwaja.
// Capacity nie rosnie podczas dodawanie elemntow, ale jezeli size = capacity, moze pojawic sie realokacja, albo zalowaknie dodakowego kawalka w pamieci( o ile mozna).
// Czasami jest tak, że jezel inie mozemy zaalokowac jeszcze troche pamieci, to zaalokowujemy wiecj i przekopiopwujemy elementy.
// Czasami po realkoacjach iteratory sie zmieniaja (po przekopiowaaniu) i iteratory sie uniważnia, wiec trzeba jeszcze raz dostac dostep do iteratora.
// METODY:
// resize(size, constructor_param) - zmianaa wielkosci wektora i zaalokowania nowej pamieci (w tym wypelnienie constructor_param) - dziala na size
// reserve(size) - dziala na capacity. Jezeli wiesz ile elementow bedzie mial wektor, to mozesz tego uzyć!!!!!!!!!!
// shrink_to_fit() - skurcz, po wykonaniu metody capacity, ktore jest nie uzwane zostaje zwolnoione zmneijsza capacity do wielkosci size.
// ULOZENIE W PAMIECI
// Struktura zostanie wrzucona na STOS (begin, end, capacity) - 3 wskazniki
// size = end - begin
// capacity = capacity(ten ptr ze stosu) - begin    
// mozna tak robic, ponieważ wszystkie elementy sa ciagiem
// STERTA : wartosci sa na stercie i tam sa allokowane/rozszerzane itp.
// Przy kopiowaniu kopoujesz zarowno co jest na stercie i stosie
// 
// Dodanie leemntu w wektorze na koniec zawsze ma złozońość stałą O(1), bo zawsze wiemy gdzie jest koniec. Ale jezeli capacity = size, to musimy zwiekszyc pamiec, czasami przekopiowac, wiec jest lipa
// Dodanie na początek am O(n), bo musimy wszystkie leeementy przekopiowac
// 
// Wszystkie OPERACJE
// push_back - na poczatk musimy stworzyc element, a potem go przekazujemy (), zawsze go kopiuje lub przenosi
// emplace_back(args...) - od razu konstruje go w pamieci wektora, 
// przekazuejmy argumenty, na podstawie ktorej funkcja buduje nam konketny obiekt i wrzuca go na vektor (bardzo dobre, bo nie musi zawsze wywolywac konstrurora kopiujacego, tylko np. uzupelina obiekty juz wczesniej utworzone)
// - np. tworzy 20 elementow std::vector<int> v; v.resize(20, 0); v.emplace_back(53); - pierwszy element ma wartosc 53, po prostu jest podstawiany
// insert() - wsatwia elementy (it, val) lub (it, val, size) np. (begin(), 50), albo wrzcuamy z innego wektora vec.insert(vec.begin(), list.begin(), list.end());
// emplace()
// at() - rzci wyjatkiem []
// back/front
// size
// capacity
// reserve
// shrink_to_fit
// rbegin() i rend()
// stale iteratory (z crbegin()
// clear
// remove - metoda przygotowujaca do usuniecia - jset po za wektorem (w algorithm) remove, przenosi wszykie lementy, ktore nie sa przeznaczone do usuniecia.
// zwraca iterator na element do usuniecia (poczatek elementow ktore musza byc usuniete) 
// erease() - vec.erease(it, vec.end()); suuwa od iteratora do konca. vec.erease(std::remove(vec.begin(),vec.end9),4), vec.end());

// Array - wszystko na stosie - nie da sie powiekszyc, chyba ze zaalokowac nowa tablice
// at - rzuci wyjatek 
// nie ma zadnych elementow dodatkowych.
// rozmiar wiemu na podstawie leementow szablonoych - wszystko kompilator robi
// sizeof (10 * wielkosc parametru)
// Tablice mogą zostać użyte do obliczeń na etapie kompilacji, gdy zadeklarujesz je jako constexpr
// Cechy:
// - caly jest contexprowy, wiec moze byc wypelniany w czasie kompilacji
// - cache friendly
// - wrapper na zwykle tablice
// Funkcje: 
// - data() - zwraca zwykly wskaznik na tablice
// back/front
// size
// iteratory/stale/rbegin/rend
// fill(wypelnic kontenre takim samym element)

// List
// Cechy:
// - na stosie head(), tail(), size() 
// - na stercie inne elementy
// - elementy trzymaja next i previos
// - elementy wskazuja na null, jezeli nie maja next lub previous
// - nie mozemy dostawac sie bezposrednnio do elementow
// - najlepiej uzywac jezeli trzymamy wielkie elementy JAKIES KLASY
// - NIE JEST CACHE FRIENDLY
// Metody:
// - push_back, emplaceback, push_front, emplace_front, insert, emplace
// - dostep do elementu tylko PRZEZ ITERATORY!!!!!!!!!!!!!!
// - sort()
// - reverse()
// - unique()
// - remove() - faktycznie usunie elementy
// - erease(wlacznie ztym it, wylacznie z tym) - tez usuwa, ale przyjmuje iteratory
// - std::advance(it, 3) - it +=3 - przechodzi o 3, 
// 
// Dodanie elementu do listy 


// Forward list
// CECHY
// - lista jednokierunkowa
// - zasada ddzialania ta sama
// - pojedynczy element (czyli na następny) zamiast tak jak jest w liscie na stercie element i wskaznik na next i previous
// - na stosie tylko begin
// METODY
// - push_front, emplace_front,insert_after, emplace_after
// - front()
// - before_begin()
// - erease_after
// - cbefore_begin()




// Deqeue - kolejka dwukeirunkowa
// CECHY:
// - HYBRYDA LISTY I WEKTORA
// - CHUNKIN + TABLICA TRZYMAJACA ADRESY DO CHUNKOW
// - DANE ZALADOWANE Z JEDNEGO KAWALKA CACHE FRIENDLY
// - SZYBKIE DODAWANIE/USUWANIE Z POCZATKU I KONCA
// - PRZESUWA ELEMENTY
// - SZYBKI ODCZYT I MODYFIKACJA
// - Elementy na stercie, chunki po 4 elementy
// - Na stercie trzyma kolejna strukture(moze to byc wektor), ktora wskazuje na male tablice o stalym rozmiarze
// - deque (wielkosc 48 w x64)
// na ttosie:
// - begin, end,size, capacity? 
// Metody:
// shrink_to_fit
//


// Stos/sterta - stos zaczyna sie od dolu pamięci i adresy rosna w górę
// Sterta - duzo wiecje pamieci niz stos, ale jest jej wiecje. Trzeba tam pamiec allokowac. Niektore kontenery alokuje pamiec na stosie/stercie.

int main()
{
    // VECTOR zadania:
    // zad 1.
    std::vector<int> vec{1, 2, 4, 5, 6};
    vec.erase(vec.begin());
    // lub vec.erase(vec.begin(), vec.begin() + 1);
    vec.push_back(12);
    vec.emplace(vec.begin(), 1);

    std::cout << "vector size: " << vec.size() << " capacity:" << vec.capacity() << std::endl;
    for (const auto& el : vec) {
        std::cout << el << std::endl;
    }

    vec.clear();
    
    std::cout << "vector size: " << vec.size() << " capacity:" << vec.capacity() << std::endl;
    
    vec.shrink_to_fit();


    std::vector<int> vec2{};
    std::cout << "vector2 size: " << vec2.size() << " capacity:" << vec2.capacity() << std::endl;
    vec2.resize(10, 5);
    std::cout << "vector2 size: " << vec2.size() << " capacity:" << vec2.capacity() << std::endl;
    vec2.reserve(20);
    std::cout << "vector2 size: " << vec2.size() << " capacity:" << vec2.capacity() << std::endl;
    vec2.shrink_to_fit();
    std::cout << "vector2 size: " << vec2.size() << " capacity:" << vec2.capacity() << std::endl;

    // SKONCZYLEM NA ARRAY(LEKCJA 0X7)
    
    // ARRAY zadania:
    // array zwraca true, gdy wielkosc == 0 czyli begin == end (wielkosc == 0)
    std::array<int, 0> emptyArray{};
    
    // return TRUE
    std::cout << "Is empty array empty? " << emptyArray.empty() << std::endl;

    std::array<int, 4> normalNotInitializedArray;
    
    // Return FALSE
    std::cout << "4 elemnts array without initializated " << normalNotInitializedArray.empty() << std::endl;

    std::array<int, 10> arrWith5{};
    arrWith5.fill(5);
    arrWith5[3] = 3;

    std::array<int,10> anotherArray{};
    anotherArray = arrWith5;

    for (const auto& el : arrWith5) {
        std::cout << el << " "; 
    }
    
    std::cout << std::endl;

    for (const auto& el : anotherArray) {
        std::cout << el << " ";
    }

    // LIST
    std::list<int> list1 {0,1,2,3,4,5};

    for (const auto& el : list1) {
        std::cout << el << " ";
    }

    std::cout << std::endl;

    auto element3 = list1.begin();
    std::advance(element3, 2);
    auto element4 = (element3);
    std::advance(element4, 1);

    list1.erase(element3, element4);

    list1.push_front(10);
    list1.push_back(10);
    
    for (const auto& el : list1) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    auto th4Pos = list1.begin();
    std::advance(th4Pos, 3);

    list1.insert(th4Pos, 20);

    int counter = 0;
    std::array<int, 10> v{};
    for (const auto el : list1) {
        v[counter] = el;
        counter++;
    }


    for (const auto& el : list1) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::forward_list<int> forwardList {0, 1, 2, 3, 4, 5};

    for (const auto& el : forwardList) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    auto begin = forwardList.begin();
    std::advance(begin, 1);

    auto afterThat = forwardList.begin();
    std::advance(afterThat, 3);

    forwardList.erase_after(begin, afterThat);
    for (const auto& el : forwardList) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    begin = forwardList.begin();
    std::advance(begin, 2);
    forwardList.insert_after(begin, 20);

    for (const auto& el : forwardList) {
        std::cout << el << " ";
    }
    std::cout << std::endl;


    std::deque<int> deque{};
    deque.push_back(0);
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);

    for (const auto& el : deque) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    deque.erase(deque.begin() + 1, deque.begin() + 2);
    deque.erase(deque.begin() + 3, deque.begin() + 4);

    deque.push_front(30);
    deque.push_back(30);

    deque.insert(deque.begin() + 3, 20);

    for (const auto& el : deque) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
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
