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
string Input;
	std::cin >> Input;
std::ifstream File(Input.c_str());
if(!File){
		std::cout << "Not in file \n";
		return 1;

}
for( std::string line; getline( File, line ); )
{
double number=0;
int i=0;
stringstream str(line);
string s;
while (std::getline(str, s,';')){

double ss = atof(s.c_str());
number=number+ss;
i++;
}
std::cout << number/i <<"\n";
}
}



