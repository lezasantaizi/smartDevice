#ifndef ALGORITHM_BL
#define ALGORITHM_BL
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
#include<fstream>
#include "Sample.h"
#include "Utils.h"

using namespace  std;
class Sport {
public:
    /**
     * the sample rate of the accelerometer.
     * */
    int samplingRate;

    /**
     * activity name
     * */
    string name;

    /**
     * customize description of the sport
     * */
    string description;

    /**
     * on left or right hand does the user wear the gear
     * */
    string hand;

    /**
     * whether the user reverse the direction of the gear
     * */
    string side;

    /**
     * the start time of the whole activity
     * */
    //Date start_time;

    /**
     * the whole recorded samples of the activity
     * */
    vector<Sample> Samples;
	    /**
     * the window size when split the samples into windows
     * */
    double WindowSize;

    /**
     * splitting the samples into windows by window size
     * */
    //vector<SampleWindow> Windows;
	Sport();
	~Sport();

	Sport(int sampling_rate) ;

    /**
     * split the samples into windows, each window contains a specified sample
     * count
     * 
     * @param sample_count
     *            a window has specified sample count samples
     * @param overlap_ratio
     *            the overlap ratio between adjacent windows
     * @throws Exception
     *             parameter out of range exception
     * @author Haocheng Wu
     * @create 2014-8-20
     */
void SplitSamplesByCount(int sample_count, double overlap_ratio);

    /**
     * add the samples into Samples ArrayList
     * 
     * @param useMinusAvg
     *            : whether record the sample by minus the average values
     * */
int receiveSample(Sample sample, int useMinusAvg);

    /**
     * Get the action count. The number should be minus the reset num
     * */
int getActionCount() ;

    /**
     * Get the sample count. The number should be minus the reset sample num
     * */
int getSampleCount() ;

    /**
     * reset the current valid count to 0
     * */
void resetActionCount() ;

    /**
     * get the basic features on each axis. The first dimension is each axis,
     * the second dimension is the different features
     * */
double** getBasicFeatures() ;

    /**
     * Parse the input lines into a single activity
     * 
     * @param activity_lines
     *            : lines which contain a single activity
     * @return the parsed activity
     * @author Xiaoming Ren
     * @create 2014-8-20
     */
static Sport Parse(vector<string> activity_lines,int sampling_rate) ;

    /**
     * Parse the input file into an activity list
     * 
     * @param input_file
     *            : the path of the input file
     * @return the list of activity contains in the file.
     * @author Xiaoming Ren
     * @create 2014-8-20
     */
static vector<Sport> Parse(string input_file, int sampling_rate) ;
protected:
    /**
     * get the valid action count
     * */


	int _valid_action_count ;

    /**
     * record the reset number of last time, the current valid count should
     * minus it
     * */
    int _last_reset_action_num ;

    /**
     * the overall sample count received by the activity
     * */
    int _sample_count ;

    /**
     * record the reset number of the sample count, the current sample count
     * should minus the reset sample count
     * */
    int _last_reset_sample_num ;



    /**
     * some basic features of the sport, such as standard deviation
     * */
    double _basic_features[3][10] ;//[Utils::MaxAxisCount][Utils::BasicFeatureCount]

 

    /**
     * calculate some basic features from the overall sport perspective, such as
     * Please input the original sample, not the minus avg sample.
     * */
void calculateFeatureByNewSample(Sample sample) ;
};


#endif