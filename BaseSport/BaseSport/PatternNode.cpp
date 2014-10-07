#include "PatternNode.h"


PatternNode::PatternNode(void)
{
}


PatternNode::~PatternNode(void)
{
}

PatternNode::PatternNode(PeakWindow firstWindow, PeakWindow secondWindow) {
	_firstWindow = firstWindow.cloneProperties();
	_secondWindow = secondWindow.cloneProperties();
	_count = 1;
	_next = NULL;
	_former = NULL;
	_last_sample_index = secondWindow.endIndex();
}

int PatternNode::size() {
	return _count;
}

double PatternNode::getSimilarity(PeakWindow firstWindow, PeakWindow secondWindow)
 {
		double firstSimilarity = 0;
		double secondSimilarity = 0;

		if (_firstWindow.isPositive() * firstWindow.isPositive() > 0) {
			firstSimilarity = _firstWindow.getSimilarity(firstWindow);
			secondSimilarity = _secondWindow.getSimilarity(secondWindow);
		} else if (_firstWindow.isPositive() * firstWindow.isPositive() < 0) {
			firstSimilarity = _firstWindow.getSimilarity(secondWindow);
			secondSimilarity = _secondWindow.getSimilarity(firstWindow);
		}

		return firstSimilarity * secondSimilarity;
}

int PatternNode::averageWindow(PeakWindow firstWindow, PeakWindow secondWindow)
{
		if(_firstWindow.averageWindow(firstWindow, _count, 1) &&
			_secondWindow.averageWindow(secondWindow, _count, 1))
		{
			++_count;
			_last_sample_index = secondWindow.endIndex();
			return true;
		}
		else
		{
			return false;
		}
}

PatternNode* PatternNode::nextNode() {
	return _next;
}

PatternNode* PatternNode::formerNode() {
	return _former;
}

int PatternNode::endIndex()
{
	return _last_sample_index;				
}

void PatternNode::setNextNode(PatternNode* next) {
	_next = next;
}

void PatternNode::setFormerNode(PatternNode* former) {
	_former = former;
}

void PatternNode::zeroClearing()
{
	_count = 0;
}