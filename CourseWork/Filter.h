#pragma once
#include "Note.h"

class Filter
{
private:
	std::function<bool(Note)> filterCallback;
public:
	Filter(std::function<bool(Note)> filter);
};

