#include "PeakWindow.h"


int PeakWindow::_MIN_BAND_DISTANCE = 2;
void PeakWindow::Init()
{
	_startIndex = -1;
	_endIndex = -1;
	_isPositive = 0;
	_size = 0;
	_absMaxValue = 0;
	_curBandwidthSampleCount = 0;
	_maxBandwidthSampleCount = 0;
	_bandCount = 0;
	_lastOutBandIndex = -1;
	_isInBand = false;
	_square_sum = 0; 
}

PeakWindow::PeakWindow()
{
	_axis = -1;
	_absBandwidthThreshold = 0;
	Init();
}
PeakWindow::PeakWindow(int axis) {
	_axis = axis;
	_absBandwidthThreshold = 0;
	Init();
}

PeakWindow::PeakWindow(int axis, double absBrandwidthThreshold) {
	_axis = axis;
	_absBandwidthThreshold = absBrandwidthThreshold;
	Init();
}

int PeakWindow::addValue(Sample& sample, int axis){
	assert(axis == this->axis());
	return addValue(sample.AxisValues[axis], sample.index);
}

int PeakWindow::addValue(double value, int index) 
{
	// empty: directly add
	if (size() <= 0) 
	{
		// add to list
		_startIndex = index;
		_endIndex = index;
		_sampleValues.push_back(value);
		++_size;

		// record the max
		_absMaxValue = abs(value);

		// sum square
		_square_sum += value * value;

		// the positive/negative property is defined by the first value
		if (value >= 0)
			_isPositive = 1;
		else
			_isPositive = -1;

		// record the band information
		recordBand(value);

		return true;
	}
	// not empty and match both positive and negative
	else if (value * isPositive() > 0 || (value == 0 && isPositive() > 0)) 
	{
		// add to list
		_endIndex = index;
		_sampleValues.push_back(value);
		++_size;

		// record the max
		if (abs(value) > _absMaxValue)
			_absMaxValue = abs(value);

		// record the band information
		recordBand(value);

		// sum square
		_square_sum += value * value;

		return true;

	}
	// not empty and match
	else 
	{
		return false;
	}
}

int PeakWindow::axis() {
	return _axis;
}

int PeakWindow::isPositive() {
	return _isPositive;
}

int PeakWindow::size() {
	return _size;
}

int PeakWindow::featureCount() {
	return _features.size();
}

int PeakWindow::startIndex()
{
	return _startIndex;
}

int PeakWindow::endIndex()
{
	return _endIndex;
}

double PeakWindow::absMaxValue() {
	return _absMaxValue;
}

double PeakWindow::getValue(int index) {
	return _sampleValues[index];
}

double PeakWindow::getFeature(int index) {
	return _features[index];
}

vector<double> PeakWindow::getFeatures() {
	return _features;
}
double PeakWindow::absBandwidthThreshold() {
	return _absBandwidthThreshold;
}

int PeakWindow::bandwidth() {
	if (_absBandwidthThreshold > 0)
		return _maxBandwidthSampleCount;
	else
		return size();
}

int PeakWindow::bandCount() {
	return _bandCount;
}

double PeakWindow::squareSum()
{
	return _square_sum;
}

void PeakWindow::setAbsBandwidthThreshold(double absBandwidthThreshold) {
	_absBandwidthThreshold = absBandwidthThreshold;

	// re-calculate the bandwidth counts
	_curBandwidthSampleCount = 0;
	_maxBandwidthSampleCount = 0;

	for (int i = 0; i < size(); ++i) {
		if (abs(_sampleValues[i]) >= absBandwidthThreshold) {
			++_curBandwidthSampleCount;

			// record the max bandwidth
			if (_curBandwidthSampleCount > _maxBandwidthSampleCount)
				_maxBandwidthSampleCount = _curBandwidthSampleCount;
		} else {
			_curBandwidthSampleCount = 0;
		}
	}
}

void PeakWindow::handleOverdue() {

	// copy and clear
	vector<double> copySampleValues = _sampleValues;
	clear();

	// add the last half remain values
	int startIndex = _startIndex;
	for (int i = copySampleValues.size() / 2; i < copySampleValues.size(); ++i)
		addValue(copySampleValues[i], startIndex + i);
}

void PeakWindow::clear() {
	_sampleValues.clear();//_sampleValues = new ArrayList<Double>();
	_size = 0;
	_isPositive = 0;
	_absMaxValue = 0;
	_curBandwidthSampleCount = 0;
	_maxBandwidthSampleCount = 0;
	_bandCount = 0;
	_lastOutBandIndex = -1;
	_isInBand = false;
	_features.clear();
}

double PeakWindow::getSimilarity(PeakWindow window)  {
	if (_isPositive * window.isPositive() <= 0)
		return 0;
	else
		return Utils::getEuclideanSimilarity(_features, window.getFeatures());
}

int PeakWindow::averageWindow(PeakWindow otherWindow, int selfCount,
				  int otherCount)  {

					  if (_isPositive * otherWindow.isPositive() <= 0)
						  return false;

					  //FIXME
					  // force selfCount = 1, and otherCount = 1
					  selfCount = 1;
					  otherCount = 2;

					  // exceptions
					  assert (selfCount > 0 && otherCount > 0);

					  // get ratios
					  double sum = selfCount + otherCount;
					  double selfRatio = selfCount / sum;
					  double otherRatio = otherCount / sum;

					  // get average scores
					  _size = (int) (selfRatio * size() + otherRatio * otherWindow.size());
					  _absMaxValue = selfRatio * absMaxValue() + otherRatio
						  * otherWindow.absMaxValue();
					  _maxBandwidthSampleCount = (int) (selfRatio * bandwidth() + otherRatio
						  * otherWindow.bandwidth());
					  _bandCount = (int) (selfRatio * bandCount() + otherRatio
						  * otherWindow.bandCount());

					  for (int i = 0; i < _features.size(); ++i)
						  _features[i] = selfRatio * _features[i] + otherRatio * otherWindow.getFeature(i);

					  return true;
}

PeakWindow PeakWindow::cloneProperties() {
	PeakWindow window(_axis, _absBandwidthThreshold);
	window._isPositive = _isPositive;
	window._startIndex = _startIndex;
	window._endIndex = _endIndex;
	window._size = _size;
	window._absMaxValue = _absMaxValue;
	window._curBandwidthSampleCount = _curBandwidthSampleCount;
	window._maxBandwidthSampleCount = _maxBandwidthSampleCount;
	window._bandCount = _bandCount;
	window._isInBand = _isInBand;

	for (int i = 0; i < _features.size(); ++i)
		window._features.push_back(_features[i]);

	return window;
}

void PeakWindow::calculateFeatures() {

	// feature set 1: existed numbers
	_features.push_back((double)(_size));
	_features.push_back((double)(_absMaxValue));
	_features.push_back((double)(_maxBandwidthSampleCount));
	_features.push_back((double)(_bandCount));

	// feature 2: average
	double average = 0;
	for (int i = 0; i < _features.size(); ++i)
		average += _features[i];
	average /= _features.size();
	_features.push_back(average);

	// feature 3: standard deviation
	double deviation = 0;
	for (int i = 0; i < _features.size(); ++i)
		deviation += pow(_features[i] - average, 2);
	deviation = sqrt(deviation / _features.size());
	_features.push_back(deviation);
}

void PeakWindow::recordBand(double value) {
	// record the bandwidth
	if (_absBandwidthThreshold > 0) {

		// in the band
		if (abs(value) >= _absBandwidthThreshold) {
			++_curBandwidthSampleCount;

			// record the max bandwidth
			if (_curBandwidthSampleCount > _maxBandwidthSampleCount)
				_maxBandwidthSampleCount = _curBandwidthSampleCount;

			// a new band
			if (!_isInBand) {
				if (_lastOutBandIndex <= 0
					|| size() - _lastOutBandIndex > _MIN_BAND_DISTANCE)
					++_bandCount;
			}

			_isInBand = true;

		}

		// not in the band
		else {
			_curBandwidthSampleCount = 0;

			if (_isInBand)
				_lastOutBandIndex = size();

			_isInBand = false;
		}
	}
}


PeakWindow::~PeakWindow(void)
{
}
