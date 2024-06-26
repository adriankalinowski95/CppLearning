#pragma once

#include <memory>
#include "ITempObject.h"

class ITestFactory {
public:
	virtual std::shared_ptr<ITempObject> createObject() = 0;
};