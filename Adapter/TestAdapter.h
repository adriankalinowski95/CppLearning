#pragma once

#include "IBaseClass.h"
#include "TestAdaptee.h"

class TestAdapter : public IBaseClass {
public:
	TestAdapter(TestAdaptee& testAdaptee):
		m_adaptee{ testAdaptee } {}

	void doSmthing() override {
		std::cout << "Adapter was called" << std::endl;

		m_adaptee.anyMethod();
	}

private:
	TestAdaptee& m_adaptee;
};