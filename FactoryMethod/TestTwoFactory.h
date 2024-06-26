#pragma once

#include "ITestFactory.h"
#include "TempObjectTwo.h"

class TestTwoFactory : public ITestFactory {
public:
	std::shared_ptr<ITempObject> createObject() {
		return std::make_shared<TempObjectTwo>();
	}
};