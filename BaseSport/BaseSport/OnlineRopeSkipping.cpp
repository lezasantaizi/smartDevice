#include "OnlineRopeSkipping.h"


OnlineRopeSkipping::OnlineRopeSkipping(void)
{
}


OnlineRopeSkipping::~OnlineRopeSkipping(void)
{
}

OnlineRopeSkipping::OnlineRopeSkipping(int sampling_rate):OnlineSport(sampling_rate, 100, 1000, 3000, 5, 0.35, 0.2){
	//super(sampling_rate, 100, 1000, 3000, 5, 0.35, 0.2);
}

int OnlineRopeSkipping::isPossibleValidAction(int axis) {
	PeakWindow* firstWindow = _firstWindows[axis];
	PeakWindow* secondWindow = _secondWindows[axis];

	if (
		// different values
			firstWindow->isPositive() * secondWindow->isPositive() < 0

			// max value limits
			&& (firstWindow->absMaxValue() >= 0.3 || secondWindow
			->absMaxValue() >= 0.3)

			// bandwidth limits
			&& firstWindow->bandwidth() <= 10
			&& secondWindow->bandwidth() <= 10)
			return true;
	else
		return false;
}

int OnlineRopeSkipping::checkCheat() {

	if (getActionCount() <= 10)
		return false;

	// check the standard deviation of each axis
	double min_std = min(
		min(_basic_features[0][0], _basic_features[1][0]),
		_basic_features[2][0]);
	double max_std = max(
		max(_basic_features[0][0], _basic_features[1][0]),
		_basic_features[2][0]);

	// I saw the data, found that when max is 2 times larger than min, it is
	// highly possible to be the cheat
	return (max_std / min_std) >= 2;
}