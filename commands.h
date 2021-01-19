

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
protected: DefaultIO* dio;
public:
vector<Command*> commandos;
	MacroCommand(DefaultIO* dio):Command(dio){
	}
	virtual void execute(){
		string line;
		// while(dio->read()){
		// 	if(dio->read() =="1"){ //if the first line is 1
		// 		commandos.at(0)->execute();
		// 	}
		// }
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
	Command_1(DefaultIO* dio1):Command(dio1){
		description = "1. upload a time series csv file";
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){
		cout<<"Please upload your local train CSV file.\n";
		
	}
	~Command_1(){}
};

class Command_2 : public Command{
	DefaultIO* dio2;
public:
	string description;
	Command_2(DefaultIO* dio2):Command(dio2){
		description = "2. algorithm settings";
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
	Command_3(DefaultIO* dio3):Command(dio3){
		description = "3. detect anomalies";
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_3(){}
};
class Command_4 : public Command{
	DefaultIO* dio2;
public:
	string description;
	Command_4(DefaultIO* dio4):Command(dio4){
		description = "4. display results";
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_4(){}
};
class Command_5 : public Command{
	DefaultIO* dio2;
public:
	string description;
	Command_5(DefaultIO* dio5):Command(dio5){
		description = "5. upload anomalies and analyze results";
	}
	virtual string getDescription (){
		return description;
	}
	virtual void execute(){};
	~Command_5(){}
};

//TODO - find how to push commands into a structure in macroCommand, and where to do it.. how to create the upload object in general....
#endif /* COMMANDS_H_ */
