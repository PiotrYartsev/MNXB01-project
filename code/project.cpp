#include "tempTrender.h"
#include <string>
<<<<<<< HEAD
=======
#include <iostream>
#include <fstream>
using namespace std;
>>>>>>> 32c010efe60d2a4697a5e85f8946d897d068a1cd

void project() {
	string pathToFile = "../CleanData/datasets/uppsala_tm_1722-2013.dat"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
<<<<<<< HEAD
	//t.output_annual_temp(1722,2013);
	//t.moving_mean_all(1722,2013,5,1);
	//t.tempPerYear(2050);
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	t.tempPerYear(2050);
=======
	t.hotCold_Upp();
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();

	//t.tempPerYear(2050);
>>>>>>> 32c010efe60d2a4697a5e85f8946d897d068a1cd
}
