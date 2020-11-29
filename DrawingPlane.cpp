#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>

#include <ctime> // for name

#define SCALE_X 78.6  //*0.8
#define SCALE_Y 153.5  //*0.8
#define TXT_NAME "Bear_Coordinates.txt"

using namespace std;

struct coordinate{
	double x;
	double y;
};

double decastlejaeu(double b0, double b1, double b2, double t){
    double b0t = (1-t)*b0 + t*b1 ;
    double b1t = (1-t)*b1 + t*b2 ;
      
    return (1-t)*b0t + t* b1t ;
}

vector<string> split(string input, char delimiter){
	vector<string> ans;
	stringstream str(input);
	string temp;
	
	while(getline(str, temp, delimiter)){
		ans.push_back(temp);
	}
	
	return ans;
}

// get Date info (used to name output file)
string fileName(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d_%H%M_",timeinfo);
    std::string str(buffer);
    
    return str;
}

void run(){
	// open file
	ifstream txt("ControlPointsBear.txt");
	ofstream output;
	
	if(txt.is_open() ){
		// open file to write
		//output.open(fileName()+TXT_NAME+".txt");
		output.open(TXT_NAME);
		
		string line;
		
		// skip first 12 lines as it does not have necessary info
		for(int i = 0; i < 12; i++) getline(txt, line); 
		
		while(getline(txt, line)){
			array<coordinate, 3> stroke;
			
			/*
			// stroke start
			if(line == "Stroke start!"){
				//stroke = new list<coordinate>();
			}
			*/
			// get 3 points into stroke
			if(line.substr(0,2) == "p0"){				
				for(int i = 0; i < 3; i++){
					vector<string> tempSplit = split(line.substr(5), ',');
				
					stroke[i].x = stod(tempSplit[0])*SCALE_X;
					stroke[i].y = stod(tempSplit[1])*SCALE_Y;
					
					getline(txt, line);
				}
				output << stroke[0].x << " " << stroke[0].y << endl; 
				
				// find 4 other points in stroke using decastlejaeu algorithm
				for(int i = 1; i < 5; i++){
					double x = decastlejaeu(stroke[0].x, stroke[1].x, stroke[2].x, 0.2*i);
					double y = decastlejaeu(stroke[0].y, stroke[1].y, stroke[2].y, 0.2*i);
					
					output << x << " " << y << endl;
				}
			}
			
			// write stroke coordinates to txt file and clear data
			else if(line == "Stroke end!"){
				/*
				for(int i = 0; i < stroke.size(); i++){
					coordinate temp = stroke.front();
					output << temp.x << " " << temp.y << endl;
					stroke.pop_front();
				}

				// delete stroke
				stroke.clear();
				*/
				
				// add final point(p2) to the file and "end" to indicate the end of stroke
				output << stroke[2].x << " " << stroke[2].y << endl;
				output << "End\n\n";
			}
		}
		
	}
	else{
		cout << "File Not Found" << endl;
	}	
	output.close();
}

int main(){
	run();
	
	return 0;
}
