#ifndef UTIL_BL
#define UTIL_BL
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
using namespace  std;
class Utils {
public:
	Utils();
	~Utils();

	static const SimpleDateFormat DateFormat = new SimpleDateFormat(
			"yyyy-MM-dd HH:mm:ss");
	static SimpleDateFormat DateFormat2 = new SimpleDateFormat(
			"yyyy/MM/dd HH:mm");
	static SimpleDateFormat TimeFormat = new SimpleDateFormat("HH:mm:ss");
	static int MaxAxisCount ;
	static int SamplingRate ;
	static int MinValidPatternActionCount ;
	static int BasicFeatureCount ;

	/**
	 * the acceleration norm value when the brace is in peace. use for calculate
	 * the relative acceleration value
	 * */
	static int BracePeaceAccelerationNormValue ;

	/**
	 * Description : Parse the input string into a Date object by DateFormat
	 * 
	 * @return the DateFormat Date object
	 * @author Haocheng Wu
	 * @create 2014-8-20
	 */
	static Date ParseDate(string date_string) ;

	/**
	 * Description : Parse the input string into a Date object by TimeFormat
	 * 
	 * @return Date: the TimeFormat Date object
	 * @author Haocheng Wu
	 * @create 2014-8-20
	 */
	static Date ParseTime(string time_string) ;

	/**
	 * Description : Add seconds based on a given date
	 * 
	 * @author Haocheng Wu
	 * @create 2014-8-20
	 */
	static Date AddSeconds(Date date, int seconds) ;

	/**
	 * Description : Add minutes based on a given date
	 * 
	 * @author Haocheng Wu
	 * @create 2014-8-20
	 */
	static Date AddMinutes(Date date, int minutes);

	/**
	 * Description : Add hours based on a given date
	 * 
	 * @author Haocheng Wu
	 * @create 2014-8-20
	 */
	static Date AddHours(Date date, int hours) ;

	/**
	 * Get the cosine similarity between two arrays
	 * 
	 * @throws Exception
	 * */
	static double getCosineSimilarity(ArrayList<Double> array1,ArrayList<Double> array2);

	/**
	 * Get the cosine similarity between two arrays
	 * 
	 * @throws Exception
	 * */
	static double getEuclideanSimilarity(ArrayList<Double> array1,ArrayList<Double> array2) ;
};
#endif