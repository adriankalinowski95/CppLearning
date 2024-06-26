#include <iostream>
#include "TestAdapter.h"

void methodDemandingBaseClass(IBaseClass& baseClass) {
    baseClass.doSmthing();
}

int main() {
    TestAdaptee adaptee{};
    TestAdapter adapter{ adaptee };

    methodDemandingBaseClass(adapter);

    std::cout << "Hello World!\n";
}