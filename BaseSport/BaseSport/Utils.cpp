#include "Utils.h"

int Utils::MaxAxisCount = 3;
int Utils::SamplingRate = 25;
int Utils::MinValidPatternActionCount = 3;
int Utils::BasicFeatureCount = 10;
int Utils::BracePeaceAccelerationNormValue = 1059;

//Date Utils::ParseDate(string date_string) {
//	try {
//		return DateFormat.parse(date_string);
//	} catch (ParseException e) {
//		try {
//			return DateFormat2.parse(date_string);
//		} catch (ParseException e2) {
//			return NULL;
//		}
//	}
//}
//
string Utils::ParseTime(string time_string) {
	char buf[80];  
	//struct tm *local;  
	//time_t nowtime;  
	//local=localtime(&nowtime);  
	//strftime(buf,80,"%Y-%m-%d %H:%M:%S",local);  
	return buf;

}
//
//Date Utils::AddSeconds(Date date, int seconds) {
//	Calendar calendar = Calendar.getInstance();
//	calendar.setTime(date);
//	calendar.add(Calendar.SECOND, seconds);
//	return calendar.getTime();
//}
//
//Date Utils::AddMinutes(Date date, int minutes) {
//	Calendar calendar = Calendar.getInstance();
//	calendar.setTime(date);
//	calendar.add(Calendar.MINUTE, minutes);
//	return calendar.getTime();
//}
//
//Date Utils::AddHours(Date date, int hours) {
//	Calendar calendar = Calendar.getInstance();
//	calendar.setTime(date);
//	calendar.add(Calendar.HOUR, hours);
//	return calendar.getTime();
//}

double Utils::getCosineSimilarity(vector<double> array1, vector<double> array2) 
{
	assert (array1.size() != array2.size());

	if (array1.size() <= 0)
		return 0;

	double numerator = 0;
	double array1_L2 = 0;
	double array2_L2 = 0;

	for (int i = 0; i < array1.size(); ++i) {
		double maximum = max(abs(array1[i]),
			abs(array2[i]));
		if (maximum > 0) {
			double score1 = array1[i] / maximum;
			double score2 = array2[i] / maximum;

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

double Utils::getEuclideanSimilarity(vector<double> array1,vector<double> array2) 
{

	assert(array1.size() != array2.size());
	if (array1.size() <= 0)
		return 0;

	double distance = 0;
	for (int i = 0; i < array1.size(); ++i) {
		double maximum = max(abs(array1[i]),
			abs(array2[i]));
		if (maximum > 0) {
			double score1 = array1[i] / maximum;
			double score2 = array2[i] / maximum;

			distance += pow(score1 - score2, 2);
		}
	}

	distance = sqrt(distance);
	double sim = 1 / (1 + distance);
	return sim;
}

vector<string> Utils::split(string str,string pattern)
{
	string::size_type pos;
	vector<string> result;
	str+=pattern;
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
 } 

string Utils::trim(const string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}
	return str.substr(pos);
}
