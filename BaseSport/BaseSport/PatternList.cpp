#include "PatternList.h"


PatternList::PatternList()
{
	_last_similarity = 0;
	_head = NULL;
	_tail = NULL;
}


PatternList::~PatternList()
{
}

PatternList::PatternList(int maxSize, int max_interval_milliseconds,double similarThreshold) 
{
	assert (maxSize >= 1 && similarThreshold > 0);
	_maxSize = maxSize;
	_similarThreshold = similarThreshold;
	_max_interval_sample_count = max_interval_milliseconds / 1000 * Utils::SamplingRate;
	_count = 0;
	_head = NULL;
	_tail = NULL;
}

int PatternList::maxSize() {
	return _maxSize;
}


int PatternList::size() {
	return _count;
}

int PatternList::getActionCount() {
	if (_head == NULL)
		return 0;
	else
		return _head->size();
}

int PatternList::add(PeakWindow* firstWindow, PeakWindow* secondWindow)
{

			// find the similar pattern
			PatternNode* cur_node = _head;
			while (cur_node != NULL) {

				// when found the expired pattern, delete it
				if (firstWindow->startIndex() - cur_node->endIndex() > _max_interval_sample_count
					&& cur_node->size() < Utils::MinValidPatternActionCount) {

						PatternNode* next_node = cur_node->nextNode();
						delete(cur_node);
						cur_node = next_node;
						continue;
				}

				// when found the similar pattern, merge it
				_last_similarity = cur_node->getSimilarity(*firstWindow,
					*secondWindow);
				if (_last_similarity >= _similarThreshold) {

					// when merge success: (A1+B1, A2+B2) or (A1+B2, A2+B1)
					if (cur_node->averageWindow(*firstWindow, *secondWindow)
						|| cur_node->averageWindow(*secondWindow, *firstWindow)) {

							// bubble sort
							while (cur_node->formerNode() != NULL && cur_node->size() > cur_node->formerNode()->size())
								swap(cur_node->formerNode(), cur_node);

							break;
					}
				}

				// when not similar, go to the next node
				cur_node = cur_node->nextNode();
			}

			// no similar pattern found
			if (cur_node == NULL) {
				// create a new pattern
				PatternNode* new_node = new PatternNode(*firstWindow,
					*secondWindow);

				// empty
				if (_count <= 0) {
					_head = new_node;
					++_count;
				}
				// no full: directly attach to tail
				else if (_count < _maxSize) {
					_tail->setNextNode(new_node);
					new_node->setFormerNode(_tail);
					++_count;
				}
				// full: remove the tail no matter how many count it has
				// because it is good for updating the pattern
				else {
					// maxSize == 1
					if (_tail->formerNode() == NULL) {
						_head = new_node;
					}
					// maxSize > 1
					else {
						_tail->formerNode()->setNextNode(new_node);
						new_node->setFormerNode(_tail->formerNode());
					}
				}

				_tail = new_node;
			}

			// head size is valid action counts
			return _head == NULL ? 0 : _head->size();
}

void PatternList::swap(PatternNode* firstNode, PatternNode* secondNode)
{

	assert(firstNode->nextNode() == secondNode);
		//throw new Exception(
		//"Second node is not the next node of first node");

	if (_head == firstNode)
		_head = secondNode;

	if (_tail == secondNode)
		_tail = firstNode;

	if (secondNode->nextNode() != NULL)
		secondNode->nextNode()->setFormerNode(firstNode);

	if (firstNode->formerNode() != NULL)
		firstNode->formerNode()->setNextNode(secondNode);

	firstNode->setNextNode(secondNode->nextNode());
	secondNode->setFormerNode(firstNode->formerNode());

	secondNode->setNextNode(firstNode);
	firstNode->setFormerNode(secondNode);
}

void PatternList::deleteAll(PatternNode* node) {
	if (_head == node)
		_head = node->nextNode();

	if (_tail == node)
		_tail = node->formerNode();

	if (node->formerNode() != NULL)
		node->formerNode()->setNextNode(node->nextNode());

	if (node->nextNode() != NULL)
		node->nextNode()->setFormerNode(node->formerNode());

	--_count;
}

double PatternList::getLastSimilarityScore()
{
	return _last_similarity;
}

void PatternList::zeroClearing() {
	//PatternNode* cur_node = _head;
	//while(cur_node != NULL)
	//{
	//	cur_node->zeroClearing();
	//	*cur_node = cur_node->nextNode();
	//}
}