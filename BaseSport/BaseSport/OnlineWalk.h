#ifndef ONLINE_WALK
#define ONLINE_WALK

#include "onlinesport.h"
class OnlineWalk :public OnlineSport
{
public:
	OnlineWalk();
	~OnlineWalk();
	
	/**
	 * min action time: 200ms, max action time 3000ms, max action interval
	 * 5000ms, pattern max size count 5, pattern similar threshold 0.2,
	 * bandwidthThreshold 0.2
	 * 
	 * @throws Exception
	 */
	OnlineWalk(int sampling_rate);

protected:
	int isPossibleValidAction(int axis) ;

	int checkCheat() ;

};
#endif

