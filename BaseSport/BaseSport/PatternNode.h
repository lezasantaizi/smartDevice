#ifndef PATTERN_NODE
#define PATTERN_NODE

#include "PeakWindow.h"
class PatternNode
{
private:
	/**
	 * a valid action needs two window
	 * */
	PeakWindow _firstWindow;

	/**
	 * a valid action needs two window
	 * */
	PeakWindow _secondWindow;

	/**
	 * the count that is similar to the node
	 * */
	int _count;

	/**
	 * the next node in the list
	 * */
	PatternNode* _next;

	/**
	 * the former node in the list
	 * */
	PatternNode* _former;
	
	/**
	 * the index of the last sample
	 * */
	int _last_sample_index;

	/**
	 * Constructor: I think there should be two windows for a valid action
	 * */
public:
	PatternNode(void);
	~PatternNode(void);
	PatternNode(PeakWindow firstWindow, PeakWindow secondWindow) ;

	/**
	 * Get the action count of the same pattern
	 * */
	int size() ;

	/**
	 * Get the similarity with other window
	 * 
	 * @throws Exception
	 * */
	double getSimilarity(PeakWindow firstWindow, PeakWindow secondWindow);

	/**
	 * Average the other similar window
	 * 
	 * @throws Exception
	 * */
	int averageWindow(PeakWindow firstWindow, PeakWindow secondWindow);

	/**
	 * Get the next node
	 * */
	PatternNode* nextNode() ;

	/**
	 * Get the former node
	 * */
	PatternNode* formerNode() ;

	/**
	 * Get the last end index of the sample
	 * */
	int endIndex();
	
	/**
	 * set the next node
	 * */
	void setNextNode(PatternNode* next) ;

	/**
	 * set the former node
	 * */
	void setFormerNode(PatternNode* former) ;

	/**
	 * zero clearing the number of the node
	 * */
	void zeroClearing();


};

#endif