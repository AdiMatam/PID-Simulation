#pragma once

#include "Pch.hpp"

class Animation {
protected:
	sf::Clock clock;
	sf::Time refreshRate;
	bool done = false;
	bool firstCall = true;

public:
	virtual void run();
	virtual void reset();
	virtual bool isDone();
};

class ConditionalAnimation : public Animation {
private:
	using Func = std::function<void(bool*)>;

	Func function;

public:
	ConditionalAnimation() = default;
	ConditionalAnimation(Func func, sf::Time refreshRate);
	virtual void run() override;
};

using DelayedCaller = ConditionalAnimation;

class IterativeAnimation : public Animation {
private:
	using Func = std::function<void()>;

	Func function;
	int iters;
	int completedIters = 0;

public:
	IterativeAnimation() = default;
	IterativeAnimation(Func func, sf::Time refreshRate, int iters);
	virtual void run() override;
};

class PathAnimation : public Animation {
private:
	using Func = std::function<void()>; // may change based on use case
	Func function;

public:
	PathAnimation() = default;
	PathAnimation(Func func, sf::Time refreshRate) {}
	virtual void run() override {}
};