#include "OnlineSport.h"

int OnlineSport::_MAX_DISCARD_SAMPLE_COUNT = 2;

void OnlineSport::Init()
{
	for (int i = 0 ;i < 3; i++)
	{
		_isPossibleValidActions[i] = 0;
		_pattern_similarity_scores[i] = 0;
	}
	
}

OnlineSport::OnlineSport()
{
	Init();
}

OnlineSport::~OnlineSport()
{

}
OnlineSport::OnlineSport(int samplingRate, int minActionMilliSeconds,int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
			int maxPatternSize, double patternSimilarThreshold)
{
	OnlineSport(samplingRate, minActionMilliSeconds, maxActionMilliSeconds,
		minActionIntervalMillseSeconds, maxPatternSize,
		patternSimilarThreshold, 0.0);
}

OnlineSport::OnlineSport(int samplingRate, int minActionMilliSeconds,
			int maxActionMilliSeconds, int minActionIntervalMillseSeconds,
			int maxPatternSize, double patternSimilarThreshold,
			double absBandwidthThreshold) :Sport(samplingRate){
				Init();
				//super(samplingRate);
				_min_window_sample_count = (minActionMilliSeconds * samplingRate / 1000);
				_max_window_sample_count = (maxActionMilliSeconds * samplingRate / 1000);
				for (int i = 0;; i++) {
					if (i >= Utils::MaxAxisCount)
						return;
					_firstWindows[i] = new PeakWindow(i, absBandwidthThreshold);
					_secondWindows[i] = new PeakWindow(i, absBandwidthThreshold);
					_patternLists[i] = new PatternList(maxPatternSize,minActionIntervalMillseSeconds, patternSimilarThreshold);
				}
}


int OnlineSport::receiveSample(Sample& sample, bool useMinusAvg)
{
	Sample usedSample;
	if (useMinusAvg)
	{
		sample.GetMinusAvgSample(usedSample);
	}
	else
	{
		usedSample = sample;
	}
	//Sample usedSample =  ?  : ;
	_sample_count = sample.index;

	// calculate the overall basic features by input sample
	calculateFeatureByNewSample(sample);

	int isValid = false;
	_valid_action_count = 0;

	for (int j = 0; j < Utils::MaxAxisCount; j++) {

		if (!isValid)
			isValid = receiveSample(usedSample, j);

		if (_valid_action_count < _patternLists[j]->getActionCount())
			_valid_action_count = _patternLists[j]->getActionCount();
	}

	return isValid;
}

int OnlineSport::receiveSample(Sample& sample, int axis) 
{
	// second window is not empty: then try to add to second window
	if (_secondWindows[axis]->isPositive() != 0) {
		// if cannot add to second window
		if (!_secondWindows[axis]->addValue(sample, axis)) 
		{
			// discard the second window if it is too small
			if (_secondWindows[axis]->size() < _MAX_DISCARD_SAMPLE_COUNT) 
			{
				_secondWindows[axis]->clear();
				receiveSample(sample, axis);
			}
			// discard the first and second window if it is small
			else if (_secondWindows[axis]->size() < _min_window_sample_count) 
			{

				_firstWindows[axis]->clear();
				_secondWindows[axis]->clear();
				_firstWindows[axis]->addValue(sample, axis);
			}

			// A VALID ACTION CANDIDATE!
			else 
			{
				int isValid = isValidAction(axis);
				_firstWindows[axis]->clear();
				_secondWindows[axis]->clear();
				receiveSample(sample, axis);
				return isValid;
			}
		}

		// if can add to the second window
		// A VALID ACTION CANDIDATE if exceed maximum sample count
		else if (_secondWindows[axis]->size() >= _max_window_sample_count) 
		{
			int isValid = isValidAction(axis);
			_firstWindows[axis]->clear();
			_secondWindows[axis]->clear();
			return isValid;
		}
	}

	// second window is empty: then try to add to first window
	// if cannot add to first window
	else if (!_firstWindows[axis]->addValue(sample, axis)) {

		// if first window is too small then discard it
		if (_firstWindows[axis]->size() < _min_window_sample_count) {
			_firstWindows[axis]->clear();
			_firstWindows[axis]->addValue(sample, axis);
		} else {
			_secondWindows[axis]->addValue(sample, axis);
		}
	}

	// if first window exceed maximum sample count, handle the overdue
	else if (_firstWindows[axis]->size() >= _max_window_sample_count) {
		_firstWindows[axis]->handleOverdue();
	}

	return false;
}

int OnlineSport::isValidAction(int axis) {
	if (isPossibleValidAction(axis)) {
		_firstWindows[axis]->calculateFeatures();
		_secondWindows[axis]->calculateFeatures();

		int formerActionCount = _patternLists[axis]->getActionCount();
		int currentActionCount = _patternLists[axis]->add(*_firstWindows[axis], *_secondWindows[axis]);

		_isPossibleValidActions[axis] = true;
		_pattern_similarity_scores[axis] = _patternLists[axis]->getLastSimilarityScore();

		return currentActionCount != formerActionCount;
	} else {
		_isPossibleValidActions[axis] = false;
	}

	return false;
}

string OnlineSport::getDebugString() {
	string sample_line = "";
	char temp[64];
	// valid action count on each axis
	for (int k = 0; k < Utils::MaxAxisCount; ++k)
	{
		sprintf(temp,"\t%.1f",_patternLists[k]->getActionCount() / 10.0);
		sample_line += temp;
	}


	// whether is possible action on each axis
	for (int k = 0; k < Utils::MaxAxisCount; ++k)
	{
		if (_isPossibleValidActions[k] != 0)
		{
			sample_line += "\t1";
		}
		else
		{
			sample_line += "\t0";
		}

	}
		

	// pattern similarity score on each axis
	for (int k = 0; k < Utils::MaxAxisCount; ++k)
	{
		sprintf(temp,"\t%.1f",_pattern_similarity_scores[k] * 10);
		sample_line += temp;
	}

	// max std / 
	double min_std = min(min(_basic_features[0][0], _basic_features[1][0]),
		_basic_features[2][0]);
	double max_std = max(max(_basic_features[0][0], _basic_features[1][0]),
		_basic_features[2][0]);

	sprintf(temp,"\t%.1f",max_std / min_std);
	sample_line += temp;

	return sample_line;
}


void OnlineSport::resetIsPossibleValidActions() {
	for (int i = 0; i < Utils::MaxAxisCount; i++) {
		_isPossibleValidActions[i] = false;
		_pattern_similarity_scores[i] = 0;
	}
}

void OnlineSport::zeroClearing() {

	_last_reset_sample_num = _sample_count;
	_last_reset_action_num = 0;

	for (int i = 0; i < Utils::MaxAxisCount; ++i) {
		_patternLists[i]->zeroClearing();

		for (int j = 0; j < Utils::BasicFeatureCount; ++j)
			_basic_features[i][j] = 0;
	}
}

int OnlineSport::isPossibleValidAction(int axis)
{
	return 0;
}

int OnlineSport::checkCheat()
{
	return 0;
}