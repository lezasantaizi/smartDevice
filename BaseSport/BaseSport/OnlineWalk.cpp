#include "OnlineWalk.h"


OnlineWalk::OnlineWalk()
{
}

OnlineWalk::~OnlineWalk()
{
}

OnlineWalk::OnlineWalk(int sampling_rate):OnlineSport(sampling_rate, 200, 500, 1000, 5, 0.35, 0.1)  {
	//super
}
int OnlineWalk::isPossibleValidAction(int axis) {
	PeakWindow* firstWindow = _firstWindows[axis];
	PeakWindow* secondWindow = _secondWindows[axis];

	if (
		// different values
			firstWindow->isPositive() * secondWindow->isPositive() < 0

			// max value limits
			&& (firstWindow->absMaxValue() >= 0.3 || secondWindow->absMaxValue() >= 0.3)

			// bandwidth limits
			&& (firstWindow->bandwidth() >= 5 || secondWindow->bandwidth() >= 5))
			return true;
	else
		return false;
}

int OnlineWalk::checkCheat() {
	return false;
}