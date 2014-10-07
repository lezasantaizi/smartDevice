#pragma once
#include "onlinesport.h"
class OnlineRopeSkipping :
	public OnlineSport
{
public:
	OnlineRopeSkipping(void);
	~OnlineRopeSkipping(void);

	/**
	 * min action time: 100ms, max action time 1000ms, max action interval
	 * 3000ms, pattern max size count 5, pattern similar threshold 0.2,
	 * bandwidthThreshold 0.2
	 * 
	 * @throws Exception
	 */
	OnlineRopeSkipping(int sampling_rate);

protected:
	int isPossibleValidAction(int axis) ;

	int checkCheat() ;

};

