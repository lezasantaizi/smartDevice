#include "Sample.h"

Sample::Sample()
{

	MinusAvgSample = NULL;
	
}

double Sample::AverageAxisValues[3] = {0};
Sample::~Sample()
{
	if(MinusAvgSample != NULL) 
		delete MinusAvgSample;
	MinusAvgSample = NULL;
	
}

Sample::Sample(int idx, double x, double y, double z) {

	MinusAvgSample = NULL;
	index = idx;
	A = sqrt(x * x + y * y + z * z);

	AxisValues[0] = x;
	AxisValues[1] = y;
	AxisValues[2] = z;

	// projection on (1, 1, 1)
	AxisValues[3] = (x + y + z) / sqrt(3);

	// projection on (-1, 1, 1)
	AxisValues[4] = (-x + y + z) / sqrt(3);

	// projection on (-1, -1, 1)
	AxisValues[5] = (-x - y + z) / sqrt(3);

	// projection on (1, -1, 1)
	AxisValues[6] = (x - y + z) / sqrt(3);
}

void Sample::resetAverageAxisValues() {
	for (int i = 0; i < 3; ++i)
		AverageAxisValues[i] = 0;
}
//
void Sample::GetMinusAvgSample(Sample& TempSample) {
	if (MinusAvgSample == NULL) {
		AverageAxisValues[0] += (AxisValues[0] - AverageAxisValues[0])
			/ index;
		AverageAxisValues[1] += (AxisValues[1] - AverageAxisValues[1])
			/ index;
		AverageAxisValues[2] += (AxisValues[2] - AverageAxisValues[2])
			/ index;

		MinusAvgSample = new Sample(index, 
			AxisValues[0] - AverageAxisValues[0], 
			AxisValues[1] - AverageAxisValues[1],
			AxisValues[2] - AverageAxisValues[2]);
	}
	TempSample = *MinusAvgSample;
}