#ifndef SAMPLE_BL
#define SAMPLE_BL
//======================================================================
//
//        All rights reserved
//
//        filename :***
//        description :
//
//        created by XiaomingRen

//
//======================================================================
#include <iostream>
#include <assert.h>
#include <vector>
using namespace  std;
class Sample {
public:
	Sample();
	~Sample();
	/**
	 * the index of the sample, start from 1
	 * */

	int index;

	/**
	 * acceleration amplitude, i.e. sqrt (x^2 + y^2 + z^2)
	 * */
	double A;

	/**
	 * the axis value on each axis, there are 4 more self-defined axis
	 * */
	double AxisValues[7] ;

	/**
	 * the alternative sample whose axis each minus average on each axis
	 * */
	Sample* MinusAvgSample;

	/**
	 * average axis value of each axis
	 * */
	static double AverageAxisValues[3] ;

	/**
	 * Description: Create new sample by minus average axis score
	 * 
	 * @param index
	 *            : the index of the sample for the activity
	 * @param x
	 *            : acceleration value of x axis
	 * @param y
	 *            : acceleration value of y axis
	 * @param z
	 *            : acceleration value of z axis
	 * @param time_stamp
	 *            : time stamp of the sample
	 */
	Sample(int idx, double x, double y, double z) ;

	/**
	 * Reset the average axis value count
	 * */
	static void resetAverageAxisValues() ;

	/**
	 * Get the minus avg sample
	 * */
	Sample* GetMinusAvgSample() ;
};
#endif