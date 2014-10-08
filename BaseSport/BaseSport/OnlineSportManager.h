#ifndef BASE_FACTORY
#define BASE_FACTORY
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
#include "Sport.h"
#include "Sample.h"
#include "Utils.h"
#include "StorageManager.h"
#include "OnlineSitup.h"
#include "OnlineWalk.h"
#include "OnlineRopeSkipping.h"

class OnlineSportManager
{
	    /**
     * the online sport member, the basic class
     * */
private:
	Sport* _sport;

    /**
     * the storage manager, use for store the acceleration data into file
     * */
    StorageManager* _storageManager;

    /**
     * the max recored sample count before dump them into file
     * */
    int _max_recored_sample_count ;

    /**
     * when the sample count reach to dump_sample_count, then dump to file
     * */
    int _dump_sample_count ;

    /**
     * the current stored sample count
     * */
    int _sample_count ;

    /**
     * stored x acceleration values
     * */
    double* _x_accelerations ;

    /**
     * stored x acceleration values
     * */
    double* _y_accelerations ;

    /**
     * stored x acceleration values
     * */
    double* _z_accelerations ;

    /**
     * the current sample index
     * */
    int _sample_index ;

    /**
     * an indicator to show whether the header of the sport is printed already
     * */
    int _header_printed ;

    /**
     * if true: the OnlineSportManager support online changing the action count
     * */
    int _support_online_show ;

    /**
     * get the action count in test
     * */
    int _test_action_count ;

    /**
     * @param storageFolder
     *            by default, it is the value of
     *            Environment.getExternalStorageDirectory()
     * */
public:

OnlineSportManager();
~OnlineSportManager();
OnlineSportManager(string storageFolder);

    /**
     * clean the storage files
     * */
void cleanStorage() ;

    /**
     * the sport finished, so need to release the objects
     * 
     * @throws IOException
     * */
void end() ;

    /**
     * get the valid action count
     * */
int getActionCount();

    /**
     * get the storage file length
     * */
int getAllSavedRecordFileLength();

    /**
     * get the path of latest saved record file
     * */
string getLatestSavedRecordFilePath() ;

    /**
     * receive a sample's acceleration values on each axis
     * 
     * @return the current valid action count
     * @throws Exception
     * */
int receive(double x, double y, double z) ;

    /**
     * reset current valid action count to 0
     * 
     * @throws Exception
     * */
void reset() ;

    /**
     * start record
     * 
     * @param sportName
     *            : the string of the sport name
     * 
     * @param supportOnlineShow
     *            : if true, then the sport can show action count online, else
     *            it is just used for recording data
     * @throws Exception
     * 
     * */
void start(string sportName, string hand, string side,
							   string description, int supportOnlineShow,
							   int sampling_rate) ;

    /**
     * test the data by simulation
     * */
int test(string testFile);

    /**
     * get the test action count. Sometimes online show is different with test
     * */
int getTestActionCount() ;

    /**
     * check whether the current online sport is cheat
     * */
int checkCheat();

    /**
     * clean the data num, this often happens after find cheat
     * */
void zeroClearing() ;
};

#endif // BASE_FACTORY
