#ifndef ONLINE_SITUP
#define ONLINE_SITUP

#include "onlinesport.h"
class OnlineSitup :
	public OnlineSport
{
public:
	OnlineSitup(void);
	~OnlineSitup(void);
	/**
	 * min action time: 500ms, max action time 3000ms, max action interval
	 * 5000ms, pattern max size count 5, pattern similar threshold 0.2,
	 * bandwidthThreshold 0.2
	 * 
	 * @throws Exception
	 */
	OnlineSitup(int sampling_rate) ;

protected:
	int isPossibleValidAction(int axis) ;

	int checkCheat();

};

#endif

