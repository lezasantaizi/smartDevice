#ifndef PEAK_WINDOW
#define PEAK_WINDOW

#include <iostream>
#include <assert.h>
#include <vector>
#include "Sample.h"
#include "Utils.h"
using namespace  std;
class PeakWindow
{
	/**
	 * the samples' values in the window, contains the specific axis values
	 * */
private:
	vector<double> _sampleValues ;

	/**
	 * record the index of the first sample
	 * */
	int _startIndex ;

	/**
	 * record the index of the last sample
	 * */
	int _endIndex ;

	/**
	 * is positive or negative peak. Positive (+1), negative (-1), empty (0)
	 * */
	int _isPositive ;

	/**
	 * the axis index
	 * */
	int _axis ;

	/**
	 * the count of values
	 * */
	int _size;

	/**
	 * the absolute maximum value of the peak.
	 * */
	double _absMaxValue ;

	/**
	 * the absolute value to define the bandwidth threshold
	 * */
	double _absBandwidthThreshold ;

	/**
	 * the sample count above the bandwidth threshold
	 * */
	int _curBandwidthSampleCount ;
	
	/**
	 * the max sample count of all the bands above the bandThreshold
	 * */
	int _maxBandwidthSampleCount ;

	/**
	 * the band count above the bandwidth threshold
	 * */
	int _bandCount ;

	/**
	 * record the sample index which out of the band last time
	 * */
	int _lastOutBandIndex ;

	/**
	 * use to merge too bands as one if they are too near
	 * */
	static int _MIN_BAND_DISTANCE;

	/**
	 * record whether the latest sample is in the band
	 * */
	int _isInBand ;
	
	double _square_sum ; 

	/**
	 * calculate some features about a window, such as average score, standard
	 * deviation, etc.
	 * */
	vector<double> _features;
	void recordBand(double value) ;
	void Init();
	/**
	 * the window needs to be specified by the axis
	 * */
public:
	PeakWindow(void);
	~PeakWindow(void);
	PeakWindow(int axis) ;

	/**
	 * the window needs to be specified by the axis, and the positive threshold
	 * of bandwidth
	 * */
	PeakWindow(int axis, double absBrandwidthThreshold);

	/**
	 * Add the axis value to the window. The value should be the same property
	 * of the positive/negative of the current window
	 * 
	 * @param sample
	 *            the acceleration sample
	 * @param axis
	 *            the target axis of the sample
	 * @return if success, return true, otherwise return false.
	 * 
	 * */
	int addValue(Sample& sample, int axis) ;

	/**
	 * Add the value to the window. The value should be the same property of the
	 * positive/negative of the current window
	 * 
	 * @param value
	 *            the sample value
	 * @param index
	 *            the sample index in the whole activity
	 * @return if success, return true, otherwise return false.
	 * 
	 * */
	int addValue(double value, int index) ;

	/**
	 * Get the specific axis of the peak window
	 * */
	int axis();

	/**
	 * Get the positive (+1) or negative (-1) or empty property (0) of the
	 * window
	 */
	int isPositive() ;

	/**
	 * Get the size of the window
	 * */
	int size() ;

	/**
	 * Get the feature count
	 * */
	int featureCount() ;

	/**
	 * Get the start index of the window
	 * */
	int startIndex();
	
	/**
	 * Get the end index of the window
	 * */
	int endIndex();
	
	/**
	 * Get the max value of the window. If the window is positive, return max,
	 * else return min
	 * */
	double absMaxValue() ;

	/**
	 * Get the value by index
	 * */
	double getValue(int index);

	/**
	 * Get the feature value by index
	 * */
	double getFeature(int index);

	/**
	 * Get all the feature values
	 * */
	vector<double> getFeatures();

	/**
	 * Get the threshold of bandwidth
	 */
	double absBandwidthThreshold() ;

	/**
	 * Get the bandwidth
	 * */
	int bandwidth() ;

	/**
	 * Get the band count which bands above the bandwidth threshold
	 * */
	int bandCount() ;

	/**
	 * Get the square sum of the window
	 * */
	double squareSum();
	
	/**
	 * Set the threshold of bandwidth, and re-calculate the samples
	 * */
	void setAbsBandwidthThreshold(double absBandwidthThreshold);

	/**
	 * Handle the overdue situation, i.e. remove the first half of values
	 * */
	void handleOverdue() ;

	/**
	 * Clear the sample values, and reset all the recorded values
	 * */
	void clear() ;

	/**
	 * Get the similarity with other window
	 * 
	 * @throws Exception
	 * */
	double getSimilarity(PeakWindow window) ;

	/**
	 * Get the average window after merging the other window by different counts
	 * 
	 * @throws Exception
	 * */
	int averageWindow(PeakWindow otherWindow, int selfCount,
			int otherCount) ;

	/**
	 * Clone the window without copying the sample values
	 * */
	PeakWindow cloneProperties() ;

	/**
	 * calculate the features of the window
	 * */
	void calculateFeatures() ;

	/**
	 * record the band information
	 * */



};
#endif
