#pragma once

#include <iostream>
#include "ITempObject.h"

class TempObjectTwo : public ITempObject {
public:
	void doSmth() override {
		std::cout << "TempObjectTwo" << std::endl;
	}
};