#ifndef STORAGE_MANAGER
#define STORAGE_MANAGER

//======================================================================
//
//        All rights reserved
//
//        filename :***
//        description :
//
//        created by XiaomingRen

//
//======================================================================

#include <iostream>
#include <assert.h>
#include "Sport.h"
#include "Sample.h"
#include "Utils.h"
#include "StorageManager.h"
using namespace  std;
class StorageManager {
private:
	/**
	 * the folder to store the data file
	 * */
	File _storage_dir;

	/**
	 * the overall data file to store all the activities
	 * */
	File _all_storage_file;

	/**
	 * the data file to store one activity
	 * */
	File _temp_storage_file;

	/**
	 * the test file to store the test result
	 * */
	File _test_storage_file;


public:
	StorageManager();
	~StorageManager();

	/**
	 * @param storageFolder
	 *            by default, it is the value of
	 *            Environment.getExternalStorageDirectory()
	 * */
StorageManager(string storageDir) ;

	/**
	 * Get current storage length
	 * */
int getAllStorageFileLength();

	/**
	 * Get the absolute path of all storage file
	 * */
string getAllStorageFilePath() ;

	/**
	 * Get the absolute path of test storage file
	 * */
string getTestStorageFilePath();

	/**
	 * Clean the storage file
	 * */
void cleanStorage() ;

	/**
	 * start an sport, so start write header of the sport
	 * 
	 * @throws IOException
	 * */
void startWritingSport(Sport* sport);

	/**
	 * append the sample values to the temp file
	 * */
void writeSamples(double* xValues, double* yValues,double* zValues, int sampleCount) ;

	/**
	 * end writing the sport, so append the temp file to the all file
	 * */
void endWritingSport();
};

#endif