#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <string>   
#include <stdlib.h> 
#include <vector>
#include <string>
#include <sstream>
using namespace std;


int main(){
int i=0;
int n=65;
double x[n];

std::ifstream File("CleanData/datasets/smhi-opendata_Lulea/data_years_smhi-opendata_Lulea.txt");
if(!File){
		std::cout << "Not in file \n";
		return 1;

}
for( std::string line; getline( File, line ); )
{
x[i]=atof(line.c_str());
std::cout << x[i];
i++;
}
File.close();


int l=0;
double y[n];

std::ifstream Filetwo("CleanData/datasets/smhi-opendata_Lulea/Final.txt");

for( std::string line; getline( Filetwo, line ); )
{
y[l]=atof(line.c_str());
l++;
}
Filetwo.close();
}




