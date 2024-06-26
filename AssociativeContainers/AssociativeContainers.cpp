// AssociativeContainers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

// w kontenerach asocjacyjnych sa elementy ulozone w okreslonej kolejnosci - maja jakies zaleznosci pomiedzy elemntami - 
// uporzadkowae - sa utworozone za pomoca drzew binarny, maja logarytmiczne przeszukiwane - przewaznie red/black map
// SET
// MULTIESET
// MAP
// MULTIMAP

// nieuporzadkowane - szybkie przeszukiwanie o zlozonosci stalych - PESYMISTYCZNIE LINIOWA - zrobione z map hashujacych
// UNORDED_SET
// UNORDED_MULTISET
// UNORDED_MAP
// UNORDERED_MULTI_MAP
// hashmapy obliczane funkcje skrotu, look up mapy i ma tam kubelki


// MAP/MULTIMAP:
// CECHY
// - nie cache friendly
// - drzewa czerowono/czarne
// - w mapie nie mamy duplikatow klucza
// - w multimapie mozemy duplikowac klucze
// - wszystko ma zlozonosc logarytmiczna 0(log n)
// - dodawanie/usuwanei szybkie
// IDEALNE DO WYSZUKIWANIA ELEMENTOW, ALE NIE MUSIMY ZA DUZO WSTAWIAC
// - mapy mozemy zastapic poprzez std::vector<std::pair<V,K>>
// METODY:
// insert/emplace/emplmace_hint
// dodawanie insert_or_assign. try_emplace, []
// dostep at/[]
// size/empty
// brak dostepu do pierwzego/ostatnieog
// iteratory normalne rbegin/rend, cbegin, cend, crbegin, crend
// clear
// erease
// swap
// count
// find
// containts dopiero od 20
// na stercie : n * sizeof(std::pair) + 2 * sizeof(X*)) gdzie X to element 
// na stosie root, comppaator(do porowywania), allocator(do dodawania elementow)
// to sa iteratory bidirectors


// MULTIMAP - key + vector<T>

// SET 

int main()
{
    std::cout << "Hello World!\n";
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
