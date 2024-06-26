#pragma once

#include <iostream>

class TestAdaptee {
public:
	void anyMethod() {
		std::cout << "Call from test adaptee" << std::endl;
	}
};