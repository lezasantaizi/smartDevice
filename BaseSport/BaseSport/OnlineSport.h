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
	int receiveSample(Sample sample, int axis);

		/**
	 * Judge whether current two windows construct a valid action
	 * 
	 * @param axis
	 *            the specific axis for the target two windows
	 * */
	int isValidAction(int axis) ;

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
			double absBandwidthThreshold) :Sport(samplingRate);

	/**
	 * API: receive the sample
	 * */

	int receiveSample(Sample sample, int useMinusAvg);

	/**
	 * Receive the sample value by specific axis
	 * */



//
//	/**
//	 * I need the string to debug the output result
//	 * */
//	public String getDebugString() {
//		String sample_line = "";
//
//		// valid action count on each axis
//		for (int k = 0; k < Utils.MaxAxisCount; ++k)
//			sample_line += "\t"
//					+ Double.toString(_patternLists[k].getActionCount() / 10.0);
//
//		// whether is possible action on each axis
//		for (int k = 0; k < Utils.MaxAxisCount; ++k)
//			sample_line += "\t" + (_isPossibleValidActions[k] ? "1" : "0");
//
//		// pattern similarity score on each axis
//		for (int k = 0; k < Utils.MaxAxisCount; ++k)
//			sample_line += "\t"
//					+ Double.toString(_pattern_similarity_scores[k] * 10);
//
//		// max std / 
//		double min_std = Math.min(
//				Math.min(_basic_features[0][0], _basic_features[1][0]),
//				_basic_features[2][0]);
//		double max_std = Math.max(
//				Math.max(_basic_features[0][0], _basic_features[1][0]),
//				_basic_features[2][0]);
//		sample_line += "\t" + Double.toString(max_std / min_std);
//		
//		return sample_line;
//	}
//
//	/**
//	 * set the possible valid action count
//	 * */
//	public void resetIsPossibleValidActions() {
//		for (int i = 0; i < Utils.MaxAxisCount; i++) {
//			_isPossibleValidActions[i] = false;
//			_pattern_similarity_scores[i] = 0;
//		}
//	}
//
//	/**
//	 * Use rule based method to filter the possible valid action
//	 * */
//	protected abstract boolean isPossibleValidAction(int axis);
//
//	/**
//	 * check whether the activity is cheat, if yes, clean the action count
//	 * */
//	protected abstract boolean checkCheat();
//
//	/**
//	 * clear the number of the patterns
//	 * */
//	public void zeroClearing() {
//		
//		_last_reset_sample_num = _sample_count;
//		_last_reset_action_num = 0;
//		
//		for (int i = 0; i < Utils.MaxAxisCount; ++i) {
//			_patternLists[i].zeroClearing();
//
//			for (int j = 0; j < Utils.BasicFeatureCount; ++j)
//				_basic_features[i][j] = 0;
//		}
//	}
};
#endif