#include "OnlineSportManager.h"

OnlineSportManager::OnlineSportManager()
{
	_max_recored_sample_count = 100;
	_dump_sample_count = 25;
	_sample_count = 0;
	_x_accelerations = new double[_max_recored_sample_count];
	_y_accelerations = new double[_max_recored_sample_count];
	_z_accelerations = new double[_max_recored_sample_count];
	_sample_index = 1;
	_header_printed = false;
	_support_online_show = false;
	_test_action_count = 0;
	_storageManager = new StorageManager();
	_sport = new Sport();
}

OnlineSportManager::~OnlineSportManager()
{
	delete[] _x_accelerations;
	delete[] _y_accelerations;
	delete[] _z_accelerations;
	delete _storageManager;
	delete _sport;
}

OnlineSportManager::OnlineSportManager(string storageFolder) {
	_storageManager = new StorageManager(storageFolder);
	_max_recored_sample_count = 100;
	_dump_sample_count = 25;
	_sample_count = 0;
	_x_accelerations = new double[_max_recored_sample_count];
	_y_accelerations = new double[_max_recored_sample_count];
	_z_accelerations = new double[_max_recored_sample_count];
	_sample_index = 1;
	_header_printed = false;
	_support_online_show = false;
	_test_action_count = 0;
	_storageManager = new StorageManager();
	_sport = new Sport();
}

void OnlineSportManager::cleanStorage() {
	_storageManager->cleanStorage();
}

void OnlineSportManager::end() {

	_storageManager->endWritingSport();
}

int OnlineSportManager::getActionCount() {
	assert(_sport != NULL) ;

	if (_support_online_show)
		return _sport->getActionCount();
	else
		return 0;
}

int OnlineSportManager::getAllSavedRecordFileLength() {
	return _storageManager->getAllStorageFileLength();
}

string OnlineSportManager::getLatestSavedRecordFilePath() {
	return _storageManager->getAllStorageFilePath();
}

int OnlineSportManager::receive(double x, double y, double z) {
	assert(_sport != NULL) ;

	double norm_x = x / Utils::BracePeaceAccelerationNormValue;
	double norm_y = y / Utils::BracePeaceAccelerationNormValue;
	double norm_z = z / Utils::BracePeaceAccelerationNormValue;

	_x_accelerations[_sample_count] = norm_x;
	_y_accelerations[_sample_count] = norm_y;
	_z_accelerations[_sample_count] = norm_z;
	++_sample_count;

	if (_storageManager != NULL) {
		if (_sample_count >= _dump_sample_count) {
			if (!_header_printed) {
				_storageManager->startWritingSport(_sport);
				_header_printed = true;
			}

			_storageManager->writeSamples(_x_accelerations,
				_y_accelerations, _z_accelerations,
				_sample_count);
			_sample_count = 0;
		}
	}

	Sample sample(_sample_index++, norm_x, norm_y, norm_z);
	int isValid = _sport->receiveSample(sample, true)
		&& _support_online_show;

	return isValid;
}

void OnlineSportManager::reset() {
	assert(_sport != NULL) ;

	_sport->resetActionCount();
}

void OnlineSportManager::start(string sportName, string hand, string side,
				  string description, int supportOnlineShow,int sampling_rate) 
{

	// reset the average axis values
	Sample::resetAverageAxisValues();

	if (sportName.find("Situps") != -1) 
	{
		_sport = new OnlineSitup(sampling_rate);
		_support_online_show = supportOnlineShow;
	} 
	else if (sportName.find("RopeSkipping")!= -1) 
	{
		_sport = new OnlineRopeSkipping(sampling_rate);
		_support_online_show = supportOnlineShow;
	} 
	else if (sportName.find("Walk")!= -1) 
	{
		_sport = new OnlineWalk(sampling_rate);
		_support_online_show = supportOnlineShow;
	} 
	else 
	{
		_sport = new Sport(sampling_rate);
		_support_online_show = false; // not supported activity is not
		// online show
	}

	//_sample_index = 1;
	//_sample_count = 0;
	//_sport->name = sportName;
	//_sport->description = description;
	//_sport->hand = hand;
	//_sport->side = side;
	//_sport->start_time = new Date();
	//_header_printed = false;
}

int OnlineSportManager::test(string testFile)
{

	int sampling_rate = 25;
	vector<Sport> activities = Sport::Parse(testFile, sampling_rate);
	//FileOutputStream fout = new FileOutputStream(_storageManager->getTestStorageFilePath());
	ofstream outfile;  
	outfile.open(_storageManager->getTestStorageFilePath());  
	if(outfile.is_open())   
	{
		for (int i = 0; i < activities.size(); ++i) 
		{

			Sample::resetAverageAxisValues();
			Sport activity = activities[i];//.get(i);
			char temp[128];
			sprintf(temp,"\nActivity Name: %s/%s\n",activity.name.c_str(),activity.description.c_str());
			outfile<<temp;
			sprintf(temp,"%s,%s\n",activity.hand.c_str(),activity.side.c_str());
			outfile<<temp;
			//sprintf(temp,"%s\n",Utils::dateFormat);
			//outfile<<temp;
			sprintf(temp,"no.\tx\ty\tz\tA\tvalid\tvx\tvy\tvz\tpx\tpy\tpz\tsx\tsy\tsz\tstd-ratio\n");
			outfile<<temp;
			//	// print information
			//	fout.write(("\nActivity Name: " + activity.name + "/"
			//		+ activity.description + "\n").getBytes());
			//	fout.write((activity.hand + "," + activity.side + "\n")
			//		.getBytes());
			//	fout.write((Utils::DateFormat.format(activity.start_time) + "\n")
			//		.getBytes());
			//	fout.write("no.\tx\ty\tz\tA\tvalid\tvx\tvy\tvz\tpx\tpy\tpz\tsx\tsy\tsz\tstd-ratio\n"
			//		.getBytes());

			OnlineSport *sport = NULL;
			if (!activity.name.compare("Situps"))
				sport = new OnlineSitup(sampling_rate);
			else if (!activity.name.compare("RopeSkipping"))
				sport = new OnlineRopeSkipping(sampling_rate);
			else if (!activity.name.compare("Walk"))
				sport = new OnlineWalk(sampling_rate);
			else
				continue;

			for (int j = 0; j < activity.Samples.size(); ++j) {

				Sample sample = activity.Samples[i];//.get(j);
				Sample* minusAvgSample = sample.GetMinusAvgSample();
				char temp[128];
				sprintf(temp,"%d\t%.4f\t%.4f\t%.4f\t%.4f\t",minusAvgSample->index,minusAvgSample->AxisValues[0],
					minusAvgSample->AxisValues[1],minusAvgSample->AxisValues[2],minusAvgSample->A);
				string sample_line = temp;
				//string sample_line = string.format(
				//	"%d\t%.4f\t%.4f\t%.4f\t%.4f\t",
				//	minusAvgSample.index,
				//	minusAvgSample.AxisValues[0],
				//	minusAvgSample.AxisValues[1],
				//	minusAvgSample.AxisValues[2],
				//	minusAvgSample.A);

				if (sport->receiveSample(sample, true)) 
				{
					char temp[64];
					
					_test_action_count = sport->getActionCount();
					sprintf(temp, "%6.4f", _test_action_count / 10.0);
					sample_line += temp;//Double.toString(_test_action_count / 10.0);
				} 
				else 
				{
					sample_line += "0";
				}

				//sample_line += sport->getDebugString();
				//sample_line += "\n";

				//sport->resetIsPossibleValidActions();
				//fout.write(sample_line.getBytes());
			}
		}

	}

	outfile.close();
	return true;

}

int OnlineSportManager::getTestActionCount() {
	return _test_action_count;
}

//int OnlineSportManager::checkCheat() {
//	if (_sport != NULL && _sport instanceof OnlineSport)
//		return ((OnlineSport) _sport).checkCheat();
//	else
//		return false;
//}
//
//void OnlineSportManager::zeroClearing() {
//	if (_sport != NULL && _sport instanceof OnlineSport)
//		((OnlineSport) _sport).zeroClearing();
//}