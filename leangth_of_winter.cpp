#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main(){
// Initialize 2D array 
char cities[4] = { "Blue", "Red", "Orange", 
                           "Yellow" }; 
  

}

/*This script takes an input file, and creates an output with the year and the mean temperature that year separated by space.
 * Check the format of the Uppsala file. If you want to change the column to average, just change temp_col, and the number_of_columns, if applied to another dataset.
 * NOTE: It only works in the format year something temperature something, not with dates (1977 is ok but 1972-07-01 is not) or columns separated by commas.*/
	
int leangth_of_winter(int chosen_year, char cities, ){

    
    
    for (int i = 0; i < sizeof(cities); i++) 
        
	


cout << cities << "\n"; 

	

	//Choose path to file
	std::ifstream inFile("CleanData/datasets/uppsala_tm_1722-2013.dat");
	if(!inFile) {
		std::cout << "Not in file";
		return 1;
		}
	
}
