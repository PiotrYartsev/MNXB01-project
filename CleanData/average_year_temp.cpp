#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <string.h>
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
size_t pos = 0;
string output;
std::string delimiter = ";";
std::string token;
while ((pos = line.find(delimiter)) != std::string::npos) {
    token = line.substr(0, pos);
    output.append(token);
    line.erase(0, pos + delimiter.length());
std::cout << output << "\n";
}
}
}

