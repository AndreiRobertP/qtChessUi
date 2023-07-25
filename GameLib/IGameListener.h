#pragma once
#include "EState.h"

class IGameListener {
public:
	virtual void OnStateChanged(EState state) = 0;
};