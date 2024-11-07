#include "Pch.hpp"
#include "Animation.hpp"

void Animation::run() {}

void Animation::reset() {
	done = false; firstCall = true;
}

bool Animation::isDone() {
	return done;
}


ConditionalAnimation::ConditionalAnimation(Func func, sf::Time refreshRate)
	: function(func)
{
	this->refreshRate = refreshRate;
}

// override
void ConditionalAnimation::run() {
	if (done)
		return;
	if (firstCall) {
		clock.restart();
		firstCall = false;
	}
	if (!done && clock.getElapsedTime() >= refreshRate) {
		function(&done);
		clock.restart();
	}
}


IterativeAnimation::IterativeAnimation(Func func, sf::Time refreshRate, int iters)
	: function(func), iters(iters)
{
	this->refreshRate = refreshRate;
}


// override
void IterativeAnimation::run() {
	if (done)
		return;
	if (firstCall) {
		clock.restart();
		firstCall = false;
	}
	if (completedIters == iters)
		done = true;
	if (!done && clock.getElapsedTime() >= refreshRate) {
		function();
		completedIters++;
		clock.restart();
	}
}
