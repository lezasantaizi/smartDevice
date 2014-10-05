#include "Utils.h"

int Utils::MaxAxisCount = 3;
int Utils::SamplingRate = 25;
int Utils::MinValidPatternActionCount = 3;
int Utils::BasicFeatureCount = 10;
int Utils::BracePeaceAccelerationNormValue = 1059;

Date Utils::ParseDate(string date_string) {
	try {
		return DateFormat.parse(date_string);
	} catch (ParseException e) {
		try {
			return DateFormat2.parse(date_string);
		} catch (ParseException e2) {
			return NULL;
		}
	}
}

Date Utils::ParseTime(string time_string) {

	return TimeFormat.parse(time_string);

}

Date Utils::AddSeconds(Date date, int seconds) {
	Calendar calendar = Calendar.getInstance();
	calendar.setTime(date);
	calendar.add(Calendar.SECOND, seconds);
	return calendar.getTime();
}

Date Utils::AddMinutes(Date date, int minutes) {
	Calendar calendar = Calendar.getInstance();
	calendar.setTime(date);
	calendar.add(Calendar.MINUTE, minutes);
	return calendar.getTime();
}

Date Utils::AddHours(Date date, int hours) {
	Calendar calendar = Calendar.getInstance();
	calendar.setTime(date);
	calendar.add(Calendar.HOUR, hours);
	return calendar.getTime();
}

double Utils::getCosineSimilarity(ArrayList<Double> array1, ArrayList<Double> array2) 
{
	if (array1.size() != array2.size())
		throw new Exception("the two arrays do not have the same length");

	if (array1.size() <= 0)
		return 0;

	double numerator = 0;
	double array1_L2 = 0;
	double array2_L2 = 0;

	for (int i = 0; i < array1.size(); ++i) {
		double maximum = max(abs(array1.get(i)),
			abs(array2.get(i)));
		if (maximum > 0) {
			double score1 = array1.get(i) / maximum;
			double score2 = array2.get(i) / maximum;

			numerator += score1 * score2;
			array1_L2 += score1 * score1;
			array2_L2 += score2 * score2;
		}
	}

	double denominator = sqrt(array1_L2 * array2_L2);
	if (denominator <= 0)
		return 0;
	else
		return numerator / denominator;
}

double Utils::getEuclideanSimilarity(ArrayList<Double> array1,ArrayList<Double> array2) 
{
	//if (array1.size() != array2.size())
	//	throw new Exception("the two arrays do not have the same length");
	assert(array1.size() != array2.size());
	if (array1.size() <= 0)
		return 0;

	double distance = 0;
	for (int i = 0; i < array1.size(); ++i) {
		double maximum = max(abs(array1.get(i)),
			abs(array2.get(i)));
		if (maximum > 0) {
			double score1 = array1.get(i) / maximum;
			double score2 = array2.get(i) / maximum;

			distance += pow(score1 - score2, 2);
		}
	}

	distance = sqrt(distance);
	double sim = 1 / (1 + distance);
	return sim;
}