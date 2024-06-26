#pragma once

#include <iostream>
#include "ITempObject.h"

class TempObjectOne : public ITempObject {
public:
	void doSmth() override {
		std::cout << "TempObjectOne" << std::endl;
	}
};