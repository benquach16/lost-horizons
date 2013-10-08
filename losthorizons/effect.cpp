#include "stdafx.h"
#include "effect.h"

std::vector<Effect*> Effect::allEffects;

//constructor
Effect::Effect(int lengthInMilliseconds) : lengthInMilliseconds(lengthInMilliseconds), totalTime(timer->getTime() + lengthInMilliseconds)
{
	allEffects.push_back(this);
}

Effect::~Effect()
{
}

bool Effect::run()
{
	//check if the effect has run out of time
	return timer->getTime() < totalTime;
}
