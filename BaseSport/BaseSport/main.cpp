#include "BaseFactory.h"

int main()
{
	string testFile = "acceleration_lab_all.txt";
	string outputDir = "../test";

	OnlineSportManager sportManager(outputDir);
	sportManager.test(testFile);
	return 0;
}