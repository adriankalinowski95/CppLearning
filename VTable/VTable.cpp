// VTable.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

class BaseNonVirtual {
    public:
        void fun() {
            std::cout << "non virtual base fun" << std::endl;
    }
};

class DeliveredNonVirtual : public BaseNonVirtual {
public:
    void fun() {
        std::cout << "non virtual delivered fun" << std::endl;
    }
};

class Base {
public:
    virtual void fun() {
        std::cout << "virtual base fun" << std::endl;
    }

    virtual void fun2() {
        std::cout << "virtual base fun2" << std::endl;
    }
};

class Delivered : public Base {
public:
    void fun() {
        std::cout << "virtual delivered fun" << std::endl;
    }

    void fun2() {
        std::cout << "virtual delivered fun2" << std::endl;
    }
};

int main()
{
    DeliveredNonVirtual deliveredNonVirtual{};
    Delivered delivered{};
    
    // wielkosc 1, dlatego ze nie ma pol virtualnych
    std::cout << "sizeof non virtual delivered" << sizeof(deliveredNonVirtual) << std::endl;

    // wielkosc 8, poniewaz dodatkowo posiada base ma funkcje virtualna, ktora przed wywoalniem jest sprawdzana i jezeli istnieje, to wyowlanie suzka, czy posiada funkcje virutalna, a potem ja wywoluje.
    // klasa posiada vpointer, ktory wskazuje na vtable
    std::cout << "sizeof virtual delivered" << sizeof(delivered) << std::endl;

    BaseNonVirtual& baseNonVirtual = dynamic_cast<BaseNonVirtual&>(deliveredNonVirtual);
    Base& base= dynamic_cast<Base&>(delivered);

    // wielkosc 1, dlatego ze nie ma pol virtualnych
    std::cout << "sizeof non virtual base" << sizeof(baseNonVirtual) << std::endl;

    // wielkosc 8, poniewaz dodatkowo posiada base ma funkcje virtualna, ktora przed wywoalniem jest sprawdzana i jezeli istnieje, to wyowlanie suzka, czy posiada funkcje virutalna, a potem ja wywoluje.
    // klasa posiada vpointer, ktory wskazuje na vtable
    std::cout << "sizeof virtual base" << sizeof(base) << std::endl;

    baseNonVirtual.fun();
    base.fun();
    base.fun2();
    // RAX: 0x000000F9D7F6F568
    // .text:00007FF78A5469BE call    j_ ? fun@BaseNonVirtual@@QEAAXXZ; BaseNonVirtual::fun(void)
    // .text:00007FF78A5469C3 mov     rax, [rbp + 150h + var_E8]
    // .text : 00007FF78A5469C7 mov     rax, [rax]
    // .text : 00007FF78A5469CA mov     rcx, [rbp + 150h + var_E8]
    // .text : 00007FF78A5469CE call    qword ptr[rax]
    // .text : 00007FF78A5469D0 mov     rax, [rbp + 150h + var_E8]
    // .text : 00007FF78A5469D4 mov     rax, [rax]
    // .text : 00007FF78A5469D7 mov     rcx, [rbp + 150h + var_E8]
    // .text : 00007FF78A5469DB call    qword ptr[rax + 8]

    // pod rax jest 000000F9D7F6F568  00007FF78A54AD88  .rdata:const Delivered::`vftable'
    // pod [rax] jest vtable ktora wyglada tak:
    // 00007FF78A54AD88  00007FF78A541249  Delivered::fun(void)
    // 00007FF78A54AD90  00007FF78A54149C  Delivered::fun2(void)
    // 00007FF78A54AD98  0000000000000000
    // czyli kompilator tworzy juz autoamtycznie dostep do vptr, a potem do vtable, tam szuka odpowiedniej funkcji i ja wywoluje
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
