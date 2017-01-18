#ifndef TIME_H
#define TIME_H

class Time
{
public:
	static double time;
	static double deltaTime;

	static double GetTime();
	static void SetTime(float t);
	static void Timestep(float dt);

private:
	enum TimeState
	{
		previous,
		current
	};

	double accumulator;
	double t;
};

#endif
