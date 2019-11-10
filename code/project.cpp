#include "tempTrender.h"
#include <string>
using namespace std;

void project() {
	string pathToFile = "../CleanData/datasets/uppsala_tm_1722-2013.dat"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	t.hotCold();
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();

	//t.tempPerYear(2050);
}
