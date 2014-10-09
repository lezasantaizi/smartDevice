#include "Sport.h"

Sport::Sport()
{
	_valid_action_count = 0;
	_last_reset_action_num = 0;
	_sample_count = 0;
	_last_reset_sample_num = 0;
	//_basic_features = new double*[Utils::MaxAxisCount];
	//for (int i = 0 ;i< Utils::MaxAxisCount; i++)
	//{
	//	_basic_features[i] = new double[Utils::BasicFeatureCount];
	//}
	
}

Sport::~Sport()
{
	//for (int i = 0; i< Utils::MaxAxisCount; i++)
	//{
	//	delete[] _basic_features[i];
	//}
	//delete[] _basic_features;
}

//useless!
Sport::Sport(int sampling_rate) {
	samplingRate = Utils::SamplingRate;

}

//void Sport::SplitSamplesByCount(int sample_count, double overlap_ratio)
//	{
//
//		// check input param
//		if (overlap_ratio < 0 || overlap_ratio >= 1)
//			throw new Exception("overlap_ratio is out of range of [0, 1)");
//		if (sample_count <= 0)
//			throw new Exception("sample_count is not positive");
//		if (((sample_count - 1) & sample_count) != 0)
//			throw new Exception("sample_count is not number of 2^n");
//
//		// assign window size
//		WindowSize = sample_count;
//
//		// new list of windows
//		Windows = new vector<SampleWindow>();
//
//		// go back count
//		int back_count = (int) (sample_count * overlap_ratio);
//
//		// Split the samples into several groups by specified size.
//		// Please note that we discard the last window which does not
//		// contains enough sample_count samples.
//		int start_index = 0;
//		while (start_index + sample_count < Samples.size()) {
//
//			// add new window
//			Windows.add(new SampleWindow(Samples, start_index, sample_count));
//
//			// new position
//			start_index += sample_count - back_count;
//		}
//}

//useless! always return false!!
int Sport::receiveSample(Sample sample, bool useMinusAvg)
{
		_sample_count = sample.index;
		calculateFeatureByNewSample(sample);

		return false;
}

int Sport::getActionCount() {
	return _valid_action_count - _last_reset_action_num;
}

int Sport::getSampleCount() {
	return _sample_count - _last_reset_sample_num;
}

void Sport::resetActionCount() {
	_last_reset_action_num = _valid_action_count;
	_last_reset_sample_num = _sample_count;
}

double** Sport::getBasicFeatures() {
	//return _basic_features;
	return NULL;
}

Sport Sport::Parse(vector<string> activity_lines,  int sampling_rate) {

	// new activity
	Sport activity(sampling_rate);// = new Sport(sampling_rate);
	//activity.Samples = new vector<Sample>();
	Sample::resetAverageAxisValues();

	// parse name
	vector<string>name_items = Utils::split(activity_lines[0],":");//activity_lines[0].split(":");
	vector<string> name_des_items = Utils::split(Utils::trim(name_items[1]),"/");//name_items[1].trim().split("/");
	activity.name = Utils::trim(name_des_items[0]);//name_des_items[0].trim();
	activity.description = name_des_items.size()>1?Utils::trim(name_des_items[1]):"";//name_des_items.length > 1 ? name_des_items[1].trim() : "";

	// parse hand and side
	vector<string> hand_side_items = Utils::split(activity_lines[1],",");//activity_lines.get(1).split(",");
	activity.hand = Utils::trim(hand_side_items[0]);//hand_side_items[0].trim();
	activity.side = Utils::trim(hand_side_items[1]);//hand_side_items[1].trim();

	// parse time stamp
	//activity.start_time = Utils::ParseDate(Utils::trim(activity_lines[2]));//activity_lines.get(2).trim());
	int index = 1;
	//useless!
	for (int i = 4; i < activity_lines.size(); ++i) 
	{

			vector<string> value_str_array = Utils::split(activity_lines[i],"\t");//activity_lines.get(i).split("\t");

			// parse and add new sample
			Sample sample(index, atof(value_str_array[0].c_str()),atof(value_str_array[1].c_str()),atof(value_str_array[2].c_str()));
			//Sample sample = new Sample(index,
			//	Double.valueOf(value_str_array[0]), // x
			//	Double.valueOf(value_str_array[1]), // y
			//	Double.valueOf(value_str_array[2]));// z

			activity.Samples.push_back(sample);
			index++;

	}


	return activity;
}

vector<Sport> Sport::Parse(string input_file, int sampling_rate) 
{
	vector<Sport> activities;
	vector<string> lines ;
	char buf[128];                
	string line;  
	ifstream infile;  
	infile.open(input_file);  
	if(infile.is_open())          
	{  
		while(infile.good() && !infile.eof())  
		{  
			memset(buf,0,128);  
			infile.getline(buf,128);  
			line = buf;  
			if (line.compare(""))
			{
				if(!line.substr(0,8).compare("Activity"))
				{
					if(lines.size() > 0)
						activities.push_back(Parse(lines, sampling_rate));
					lines.clear();
				}

				lines.push_back(line);

			}
 
		} 
		activities.push_back(Parse(lines, sampling_rate));
		infile.close();  
	}  
	return activities;

	


	
	//// new list
	//vector<Sport> activities = new vector<Sport>();

	//	// open file
	//	FileInputStream fis = new FileInputStream(input_file);
	//	InputStreamReader isr = new InputStreamReader(fis, "UTF-8");
	//	BufferedReader br = new BufferedReader(isr);

	//	String line = "";
	//	vector<String> lines = new vector<String>();
	//	while ((line = br.readLine()) != null) {

	//		if (!line.equals("")) {
	//			// a new activity started
	//			if (line.startsWith("Activity")) {

	//				// parse the old lines as an activity
	//				if (lines.size() > 0)
	//					activities.add(Parse(lines, sampling_rate));

	//				// clean lines
	//				lines.clear();
	//			}

	//			lines.add(line);
	//		}
	//	}

	//	// parse the last activities
	//	activities.add(Parse(lines, sampling_rate));

	//	// close file
	//	br.close();
	//	isr.close();
	//	fis.close();
	//return activities;
}

void Sport::calculateFeatureByNewSample(Sample sample) {
	Sample* minusAvgSample = sample.GetMinusAvgSample();

	for (int i = 0; i < Utils::MaxAxisCount; ++i) {

		// standard deviation
		_basic_features[i][0] += (minusAvgSample->AxisValues[i]	* minusAvgSample->AxisValues[i] - _basic_features[i][0])/ sample.index;
	}
}




