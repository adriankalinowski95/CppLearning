#include <iostream>
#include "TestOneFactory.h"
#include "TestTwoFactory.h"

// Normally, we should inject the factory and using her to creating object.
// She always must be a interface.
void tempObjectCaller(ITestFactory& factory) {
    auto object = factory.createObject();
    object->doSmth();
}

int main()
{
    TestOneFactory factoryOne{};
    TestTwoFactory factoryTwo{};
    tempObjectCaller(factoryOne);
    tempObjectCaller(factoryTwo);

    return 0;
}