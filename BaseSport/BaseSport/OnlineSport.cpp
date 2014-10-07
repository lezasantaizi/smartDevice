#include "OnlineSport.h"

//int OnlineSport::_MAX_DISCARD_SAMPLE_COUNT = 2;

OnlineSport::OnlineSport()
{

}

OnlineSport::~OnlineSport()
{

}
OnlineSport::OnlineSport(int samplingRate, int minActionMilliSeconds,int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
			int maxPatternSize, double patternSimilarThreshold)
{
	OnlineSport(samplingRate, minActionMilliSeconds, maxActionMilliSeconds,
		minActionIntervalMillseSeconds, maxPatternSize,
		patternSimilarThreshold, 0.0);
}