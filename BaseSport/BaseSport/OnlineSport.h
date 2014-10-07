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
	PatternList _patternLists[3];

	/**
	 * whether the last sample is a possible valid action based on rules.
	 * */
	int _isPossibleValidActions[3] ;
//
//	/**
//	 * the similarity scores of the pattern
//	 * */
//	double _pattern_similarity_scores[3];
//
//protected:
//		/**
//	 * the first peak windows on each axis
//	 * */
//	PeakWindow _firstWindows[3];
//
//	/**
//	 * the second peak windows on each axis
//	 * */
//	PeakWindow _secondWindows[3];
//
//	/**
//	 * @param sampleRate
//	 *            sampling rate of the g-sensor
//	 * @param minActionMilliSeconds
//	 *            the minimum milliseconds needed for a valid action
//	 * @param maxActionMilliSeconds
//	 *            the maximum milliseconds needed for a valid action
//	 * @param maxPatternSize
//	 *            the maximum pattern size a the pattern list
//	 * @param patternSimilarThreshold
//	 *            the similarity threshold between two patterns
//	 * */
//
//public:
//	OnlineSport();
//	~OnlineSport();
//	OnlineSport(int samplingRate, int minActionMilliSeconds,
//			int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
//			int maxPatternSize, double patternSimilarThreshold)
//			{
//		this(samplingRate, minActionMilliSeconds, maxActionMilliSeconds,
//				minActionIntervalMillseSeconds, maxPatternSize,
//				patternSimilarThreshold, 0.0D);
//	}
//
//	/**
//	 * @param sampleRate
//	 *            sampling rate of the g-sensor
//	 * @param minActionMilliSeconds
//	 *            the minimum milliseconds needed for a valid action
//	 * @param maxActionMilliSeconds
//	 *            the maximum milliseconds needed for a valid action
//	 * @param maxPatternSize
//	 *            the maximum pattern size a the pattern list
//	 * @param patternSimilarThreshold
//	 *            the similarity threshold between two patterns
//	 * @param absBandwidthThreshold
//	 *            the abs bandwidth threshold valid to judge the band
//	 * */
//	public OnlineSport(int samplingRate, int minActionMilliSeconds,
//			int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
//			int maxPatternSize, double patternSimilarThreshold,
//			double absBandwidthThreshold) throws Exception {
//		super(samplingRate);
//		this._min_window_sample_count = (minActionMilliSeconds * samplingRate / 1000);
//		this._max_window_sample_count = (maxActionMilliSeconds * samplingRate / 1000);
//		for (int i = 0;; i++) {
//			if (i >= Utils.MaxAxisCount)
//				return;
//			this._firstWindows[i] = new PeakWindow(i, absBandwidthThreshold);
//			this._secondWindows[i] = new PeakWindow(i, absBandwidthThreshold);
//			this._patternLists[i] = new PatternList(maxPatternSize,
//					minActionIntervalMillseSeconds, patternSimilarThreshold);
//		}
//	}
//
//	/**
//	 * API: receive the sample
//	 * */
//	@Override
//	public boolean receiveSample(Sample sample, boolean useMinusAvg)
//			throws Exception {
//		Sample usedSample = useMinusAvg ? sample.GetMinusAvgSample() : sample;
//		_sample_count = sample.index;
//
//		// calculate the overall basic features by input sample
//		calculateFeatureByNewSample(sample);
//
//		boolean isValid = false;
//		this._valid_action_count = 0;
//
//		for (int j = 0; j < Utils.MaxAxisCount; j++) {
//
//			if (!isValid)
//				isValid = receiveSample(usedSample, j);
//
//			if (this._valid_action_count < this._patternLists[j]
//					.getActionCount())
//				this._valid_action_count = this._patternLists[j]
//						.getActionCount();
//		}
//
//		return isValid;
//	}
//
//	/**
//	 * Receive the sample value by specific axis
//	 * */
//	private boolean receiveSample(Sample sample, int axis) throws Exception {
//		// second window is not empty: then try to add to second window
//		if (this._secondWindows[axis].isPositive() != 0) {
//			// if cannot add to second window
//			if (!this._secondWindows[axis].addValue(sample, axis)) {
//				// discard the second window if it is too small
//				if (this._secondWindows[axis].size() < _MAX_DISCARD_SAMPLE_COUNT) {
//					this._secondWindows[axis].clear();
//					receiveSample(sample, axis);
//				}
//
//				// discard the first and second window if it is small
//				else if (this._secondWindows[axis].size() < this._min_window_sample_count) {
//
//					this._firstWindows[axis].clear();
//					this._secondWindows[axis].clear();
//					this._firstWindows[axis].addValue(sample, axis);
//				}
//
//				// A VALID ACTION CANDIDATE!
//				else {
//					boolean isValid = isValidAction(axis);
//					this._firstWindows[axis].clear();
//					this._secondWindows[axis].clear();
//					receiveSample(sample, axis);
//					return isValid;
//				}
//			}
//
//			// if can add to the second window
//			// A VALID ACTION CANDIDATE if exceed maximum sample count
//			else if (this._secondWindows[axis].size() >= this._max_window_sample_count) {
//				boolean isValid = isValidAction(axis);
//				this._firstWindows[axis].clear();
//				this._secondWindows[axis].clear();
//				return isValid;
//			}
//		}
//
//		// second window is empty: then try to add to first window
//		// if cannot add to first window
//		else if (!this._firstWindows[axis].addValue(sample, axis)) {
//
//			// if first window is too small then discard it
//			if (this._firstWindows[axis].size() < this._min_window_sample_count) {
//				this._firstWindows[axis].clear();
//				this._firstWindows[axis].addValue(sample, axis);
//			} else {
//				this._secondWindows[axis].addValue(sample, axis);
//			}
//		}
//
//		// if first window exceed maximum sample count, handle the overdue
//		else if (this._firstWindows[axis].size() >= this._max_window_sample_count) {
//			this._firstWindows[axis].handleOverdue();
//		}
//
//		return false;
//	}
//
//	/**
//	 * Judge whether current two windows construct a valid action
//	 * 
//	 * @param axis
//	 *            the specific axis for the target two windows
//	 * */
//	private boolean isValidAction(int axis) throws Exception {
//		if (isPossibleValidAction(axis)) {
//			this._firstWindows[axis].calculateFeatures();
//			this._secondWindows[axis].calculateFeatures();
//
//			int formerActionCount = this._patternLists[axis].getActionCount();
//			int currentActionCount = this._patternLists[axis].add(
//					this._firstWindows[axis], this._secondWindows[axis]);
//
//			this._isPossibleValidActions[axis] = true;
//			this._pattern_similarity_scores[axis] = this._patternLists[axis]
//					.getLastSimilarityScore();
//
//			return currentActionCount != formerActionCount;
//		} else {
//			this._isPossibleValidActions[axis] = false;
//		}
//
//		return false;
//	}
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
//					+ Double.toString(this._patternLists[k].getActionCount() / 10.0);
//
//		// whether is possible action on each axis
//		for (int k = 0; k < Utils.MaxAxisCount; ++k)
//			sample_line += "\t" + (this._isPossibleValidActions[k] ? "1" : "0");
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
//			this._isPossibleValidActions[i] = false;
//			this._pattern_similarity_scores[i] = 0;
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
//		this._last_reset_sample_num = this._sample_count;
//		this._last_reset_action_num = 0;
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