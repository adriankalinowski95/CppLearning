#pragma once

#include "ITestFactory.h"
#include "TempObjectOne.h"

class TestOneFactory : public ITestFactory {
public:
	std::shared_ptr<ITempObject> createObject() {
		return std::make_shared<TempObjectOne>();
	}
};