#include "StorageManager.h"

StorageManager::StorageManager()
{

}

StorageManager::~StorageManager()
{

}

StorageManager::StorageManager(string storageDir) 
{
	_storage_dir = new File(storageDir, "Bracelet");
	if (!_storage_dir.exists())
		_storage_dir.mkdir();

	_all_storage_file = new File(_storage_dir.getAbsolutePath(),
		"acceleration_lab_all.txt");

	_temp_storage_file = new File(_storage_dir.getAbsolutePath(),
		"acceleration_lab_temp.txt");

	_test_storage_file = new File(_storage_dir.getAbsolutePath(),
		"acceleration_lab_test.txt");
}

int StorageManager::getAllStorageFileLength() {
	if (!_all_storage_file.exists())
		throw new FileNotFoundException(_all_storage_file.getAbsolutePath());

	// get length in byte
	FileInputStream fin = new FileInputStream(_all_storage_file);
	int length = fin.available();
	byte[] buffer = new byte[length];
	fin.read(buffer);
	fin.close();
	return length;
}

string StorageManager::getAllStorageFilePath() {
	return _all_storage_file.getAbsolutePath();
}

string StorageManager::getTestStorageFilePath() {
	return _test_storage_file.getAbsolutePath();
}

void StorageManager::cleanStorage() {
	// all storage file
	try {
		FileOutputStream fout = new FileOutputStream(_all_storage_file);
		fout.close();
	} catch (IOException e) {
	}

	// temp storage file
	try {
		FileOutputStream fout = new FileOutputStream(_temp_storage_file);
		fout.close();
	} catch (IOException e) {
	}

	// test storage file
	try {
		FileOutputStream fout = new FileOutputStream(_test_storage_file);
		fout.close();
	} catch (IOException e) {
	}
}

void StorageManager::startWritingSport(Sport* sport){
	// empty the temp file
	FileOutputStream fout = new FileOutputStream(_temp_storage_file, false);

	// print information
	fout.write(("\nActivity Name: " + sport->name + "/" + sport->description + "\n")
		.getBytes());
	fout.write((sport->hand + "," + sport->side + "\n").getBytes());
	fout.write((Utils::DateFormat.format(sport->start_time) + "\n")
		.getBytes());
	fout.write("x\ty\tz\n".getBytes());
	fout.close();
}

void StorageManager::writeSamples(double* xValues, double* yValues,double* zValues, int sampleCount) 
{
	FileOutputStream fout = new FileOutputStream(_temp_storage_file, true);
	for (int i = 0; i < sampleCount; ++i)
		fout.write((String.format("%.4f", xValues[i]) + "\t"
		+ String.format("%.4f", yValues[i]) + "\t"
		+ String.format("%.4f", zValues[i]) + "\n").getBytes());

	fout.close();
}

void StorageManager::endWritingSport(){
	// read the whole temp file
	FileInputStream fin = new FileInputStream(_temp_storage_file);
	int length = fin.available();
	byte[] buffer = new byte[length];
	fin.read(buffer);
	fin.close();

	// write to all storage file
	FileOutputStream fout = new FileOutputStream(_all_storage_file, true);
	fout.write(buffer);
	fout.close();
}