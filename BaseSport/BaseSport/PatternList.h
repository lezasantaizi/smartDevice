#ifndef PATTERN_LIST
#define PATTERN_LIST

#include "PatternNode.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include "Utils.h"
using namespace  std;
class PatternList
{
private:
	int _count;
	int _maxSize;
	int _max_interval_sample_count;
	double _similarThreshold;
	double _last_similarity ;
	PatternNode* _head ;
	PatternNode* _tail ;
	void Init();

public:
	PatternList(void);
	~PatternList(void);
	PatternList(int maxSize, int max_interval_milliseconds,double similarThreshold) ;

	/**
	 * Get the max size of the list
	 * */
	int maxSize() ;

	/**
	 * Get the size of the list
	 * */
	int size() ;

	/**
	 * Get the valid action count
	 * */
	int getActionCount() ;

	/**
	 * check whether the action is a valid action. If yes, add the current
	 * similar action count by 1. If no, add to the list as a candidate pattern
	 * for the following accumulation.
	 * 
	 * @return the valid action count
	 * */
	int add(PeakWindow* firstWindow, PeakWindow* secondWindow);

	/**
	 * Swap two consecutive nodes
	 * 
	 * @throws Exception
	 * */
	void swap(PatternNode* firstNode, PatternNode* secondNode);

	/**
	 * delete the specified node.
	 * */
	void deleteAll(PatternNode* node) ;
	
	/**
	 * get the last similarity score of the pattern, used for debug
	 * */
	double getLastSimilarityScore();

	
	/**
	 * zero clearing the nodes of the list
	 * */
	void zeroClearing() ;


};

#endif