#include "OnlineSitup.h"


OnlineSitup::OnlineSitup(void)
{
}


OnlineSitup::~OnlineSitup(void)
{
}

OnlineSitup::OnlineSitup(int sampling_rate):OnlineSport(sampling_rate, 500, 3000, 5000, 5, 0.35, 0.2)  {
	//super(sampling_rate, 500, 3000, 5000, 5, 0.35, 0.2);
}

int OnlineSitup::isPossibleValidAction(int axis) {
	PeakWindow* firstWindow = _firstWindows[axis];
	PeakWindow* secondWindow = _secondWindows[axis];

	if (
		// different values
			firstWindow->isPositive() * secondWindow->isPositive() < 0

			// max value limits
			&& firstWindow->absMaxValue() >= 0.3
			&& secondWindow->absMaxValue() >= 0.3

			// bandwidth limits
			&& firstWindow->bandwidth() >= 10
			&& secondWindow->bandwidth() >= 10)
			return true;
	else
		return false;
}

int OnlineSitup::checkCheat() {
	// TODO Auto-generated method stub
	return false;
}