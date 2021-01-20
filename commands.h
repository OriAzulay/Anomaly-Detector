

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class 
DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
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
	virtual ~Command(){}
};

class MacroCommand : public Command{
protected: DefaultIO* dioM;
public:
vector<Command*> commandos;

	MacroCommand(DefaultIO* dio):Command(dio){
		dioM = dio;
	}
	virtual void execute(){
		string optionN = dioM->read();
		while(optionN != "6"){
			if(optionN == "1"){
				commandos.at(0)->execute();
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
			optionN = dioM->read();
		}
		
		

	}

	virtual string getDescription(){
		return "menu";
	}
	void setCommands(Command* a,Command* b,Command* c,Command* d,Command* e ){
		commandos = {a,b,c,d,e};
	}
	virtual ~MacroCommand(){}
};

// implement here your command classes
//Upload time series

class Command_1 : public Command{
	DefaultIO* dio1;
public:
	string description;
	Command_1(DefaultIO* dio):Command(dio){
		description = "1. upload a time series csv file";
		dio1 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){
		int itr = 2;
		string fileName = "Train";
		
		while(itr != 0){
			cout<<"Please upload your local train CSV file.\n";
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
			cout<<"Upload complete.\n";
		}
		TimeSeries trainCSV("anomalyTrain.csv");
		TimeSeries testCSV("anomalyTest.csv");
		
	}
	~Command_1(){}
};

class Command_2 : public Command{
	DefaultIO* dio2;
public:
	string description;
	Command_2(DefaultIO* dio):Command(dio){
		description = "2. algorithm settings";
		dio2 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_2(){}
};
class Command_3 : public Command{
	DefaultIO* dio3;
public:
	string description;
	Command_3(DefaultIO* dio):Command(dio){
		description = "3. detect anomalies";
		dio3 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_3(){}
};
class Command_4 : public Command{
	DefaultIO* dio4;
public:
	string description;
	Command_4(DefaultIO* dio):Command(dio){
		description = "4. display results";
		dio4 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_4(){}
};
class Command_5 : public Command{
	DefaultIO* dio5;
public:
	string description;
	Command_5(DefaultIO* dio):Command(dio){
		description = "5. upload anomalies and analyze results";
		dio5 = dio;
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_5(){}
};

//TODO - find how to push commands into a structure in macroCommand, and where to do it.. how to create the upload object in general....
#endif /* COMMANDS_H_ */
