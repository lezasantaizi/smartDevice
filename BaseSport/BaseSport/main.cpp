#include "BaseFactory.h"

int main()
{
	string testFile = "D:/documents/bracelets/data/test/acceleration_lab_all.txt";
	string outputDir = "D:/documents/bracelets/data/test";

	OnlineSportManager sportManager(outputDir);
	sportManager.test(testFile);
	return 0;
}