#ifndef ONLINE_SPORT
#define ONLINE_SPORT
#include "Sport.h"
#include "PatternList.h"
class OnlineSport : public Sport{
	/**
	 * when the window is too small, the window should be discard
	 * */
private :
	static int _MAX_DISCARD_SAMPLE_COUNT ;

	/**
	 * the max window sample count, only no bigger than it is a valid peak
	 * window
	 * */
	int _max_window_sample_count;

	/**
	 * the min window sample count, only no less than it is a valid peak window
	 * */
	int _min_window_sample_count;

	/**
	 * the overall lists of patterns on each axis
	 * */
	PatternList* _patternLists[3];

	/**
	 * whether the last sample is a possible valid action based on rules.
	 * */
	int _isPossibleValidActions[3] ;

	/**
	 * the similarity scores of the pattern
	 * */
	double _pattern_similarity_scores[3];
	int receiveSample(Sample& sample, int axis);

		/**
	 * Judge whether current two windows construct a valid action
	 * 
	 * @param axis
	 *            the specific axis for the target two windows
	 * */
	int isValidAction(int axis) ;
	void Init();
protected:
		/**
	 * the first peak windows on each axis
	 * */
	PeakWindow* _firstWindows[3];

	/**
	 * the second peak windows on each axis
	 * */
	PeakWindow* _secondWindows[3];


	
	/**
	 * Use rule based method to filter the possible valid action
	 * */
	virtual int isPossibleValidAction(int axis) ;

	/**
	 * check whether the activity is cheat, if yes, clean the action count
	 * */
	virtual int checkCheat() ;

	/**
	 * @param sampleRate
	 *            sampling rate of the g-sensor
	 * @param minActionMilliSeconds
	 *            the minimum milliseconds needed for a valid action
	 * @param maxActionMilliSeconds
	 *            the maximum milliseconds needed for a valid action
	 * @param maxPatternSize
	 *            the maximum pattern size a the pattern list
	 * @param patternSimilarThreshold
	 *            the similarity threshold between two patterns
	 * */

public:
	OnlineSport();
	~OnlineSport();
	OnlineSport(int samplingRate, int minActionMilliSeconds,int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
		int maxPatternSize, double patternSimilarThreshold);

	/**
	 * @param sampleRate
	 *            sampling rate of the g-sensor
	 * @param minActionMilliSeconds
	 *            the minimum milliseconds needed for a valid action
	 * @param maxActionMilliSeconds
	 *            the maximum milliseconds needed for a valid action
	 * @param maxPatternSize
	 *            the maximum pattern size a the pattern list
	 * @param patternSimilarThreshold
	 *            the similarity threshold between two patterns
	 * @param absBandwidthThreshold
	 *            the abs bandwidth threshold valid to judge the band
	 * */
	OnlineSport(int samplingRate, int minActionMilliSeconds,
			int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
			int maxPatternSize, double patternSimilarThreshold,
			double absBandwidthThreshold) ;

	/**
	 * API: receive the sample
	 * */

	virtual int receiveSample(Sample& sample, bool useMinusAvg);

	/**
	 * Receive the sample value by specific axis
	 * */




	/**
	 * I need the string to debug the output result
	 * */
	string getDebugString() ;

	/**
	 * set the possible valid action count
	 * */
	void resetIsPossibleValidActions() ;


	/**
	 * clear the number of the patterns
	 * */
	void zeroClearing() ;
};
#endif