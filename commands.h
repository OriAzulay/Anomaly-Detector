

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include <sstream>
#include <iomanip>
using namespace std;

class 
DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	//optinal - func to upload file from path
	void getFileByPath(){ 
		const char *path;
		ofstream file(path);
	}

	virtual ~DefaultIO(){}



	// you may add additional methods here
};


// you may edit this class
class Command{
protected: DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual string getDescription()=0;
	virtual TimeSeries getTrainCsv(){}
	
	virtual ~Command(){}
};

class MacroCommand : public Command{
protected: DefaultIO* dioM;
public:
vector<Command*> commandos;
float threshold;
bool menu;
	MacroCommand(DefaultIO* dio):Command(dio){
		dioM = dio;
		threshold = 0.95;
	}
	virtual void execute(){
		string optionN = dioM->read();
		int i;
		menu = true;
		while(menu){
			for(Command* c : commandos){
				dioM->write(c->getDescription() + "\n");
			}
			// stringstream ss(optionN);
			// ss>>i;
			// commandos.at(i-1)->execute();
			if(optionN == "1"){
				commandos.at(0)->execute();
				optionN = dioM->read();
			}
			if(optionN == "2"){
				commandos.at(1)->execute();
			}
			if(optionN == "3"){
				commandos.at(2)->execute();
			}
			if(optionN == "4"){
				commandos.at(3)->execute();
			}
			if(optionN == "5"){
				commandos.at(4)->execute();
			}
			else{
				menu = false;
			}
			optionN = dioM->read();
		}
		
		

	}

	virtual string getDescription(){
		return "menu";
	}
	void setCommands(Command* a,Command* b,Command* c,Command* d,Command* e, Command* f ){
		commandos = {a,b,c,d,e,f};
	}
	virtual ~MacroCommand(){}
};

// implement here your command classes
class Command_1 : public MacroCommand{
	DefaultIO* dio1;
public:
	string description;
	Command_1(DefaultIO* dio):MacroCommand(dio){
		description = "1.upload a time series csv file";
		dio1 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){
		int itr = 2;
		string fileName = "Train";
		
		while(itr != 0){
			dio1->write("Please upload your local train CSV file.\n");
			ofstream myfile;
			myfile.open("anomaly" + fileName + ".csv");
			string lines = dio1->read();
			while (lines != "done")
			{
				myfile << lines + "\n";
				lines = dio1->read();
			}
			itr--;
			myfile.close();
			fileName = "Test";
			dio1->write("Upload complete.\n");
		}
	}
	TimeSeries getTrainCsv(){
		TimeSeries train("anomalyTrain.csv");
		return train;
	}
	TimeSeries getTestCsv(){
		TimeSeries test("anomalyTest.csv");
		return test;
	}
	~Command_1(){}
};

class Command_2 : public MacroCommand{
	DefaultIO* dio2;
public:
	string description;
	Command_2(DefaultIO* dio):MacroCommand(dio){
		description = "2.algorithm settings";
		dio2 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){
		
		bool opt = false;
		float thr;		
		while(!opt){
			stringstream stream;
			stream << threshold;
			string t = stream.str();
			dio2->write("The current correlation threshold is " + t + "\n" "Type a new threshold");
			string g = dio2->read();
			stringstream s(g);
			s>>thr;
			if(thr > 0 && thr < 1){
				threshold = thr;
				opt = true;
			}else{
				dio->write("please choose a value between 0 and 1.\n");
			}
		}
	}
	~Command_2(){}
};
class Command_3 : public MacroCommand{
	DefaultIO* dio3;
public:
	string description;
	Command_3(DefaultIO* dio):MacroCommand(dio){
		description = "3.detect anomalies";
		dio3 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){
		HybridAnomalyDetector ad;
		ad.learnNormal(commandos.at(0)->getDescription())
	}
	~Command_3(){}
};
class Command_4 : public MacroCommand{
	DefaultIO* dio4;
public:
	string description;
	Command_4(DefaultIO* dio):MacroCommand(dio){
		description = "4.display results";
		dio4 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_4(){}
};
class Command_5 : public MacroCommand{
	DefaultIO* dio5;
public:
	string description;
	Command_5(DefaultIO* dio):MacroCommand(dio){
		description = "5.upload anomalies and analyze results";
		dio5 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_5(){}
};

class Command_6 : public MacroCommand{
	DefaultIO* dio6;
public:
	string description;
	Command_6(DefaultIO* dio):MacroCommand(dio){
		description = "6.exit";
		dio6 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){
		menu = false;
	}
	~Command_6(){}
};

//TODO - find how to push commands into a structure in macroCommand, and where to do it.. how to create the upload object in general....
#endif /* COMMANDS_H_ */
