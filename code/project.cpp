#include "tempTrender.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


void project() {
	string pathToFile = "../CleanData/datasets/uppsala_tm_1722-2013.dat"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object


	//t.hotCold();
	t.hotCold_Upp();
	t.tempPerYear(2050);
}
