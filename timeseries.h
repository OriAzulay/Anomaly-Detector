#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "string.h"

using namespace std;

class TimeSeries{
protected:
    //vector -> fet.at(index).first\second..
    vector<pair<string, vector<float>>> features;

public:
    TimeSeries(const char* CSVfileName);
    vector<pair<string, vector<float>>> getVector()const{
        return features;
    }
     vector<float> getVecByIndex(int index){
         return features.at(index).second;
     }
    
    
};



#endif /* TIMESERIES_H_ */
