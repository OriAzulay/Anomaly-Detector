#include "CLI.h"


CLI::CLI(DefaultIO* di) {
    dio = di;
}

void CLI::start(){
    dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
    Command* one = new Command_1(dio);
    Command* two = new Command_2(dio);
    Command* three = new Command_3(dio);
    Command* four = new Command_4(dio);
    Command* five = new Command_5(dio);
    Command* six = new Command_6(dio);
    MacroCommand macro(dio);
    macro.setCommands(one,two,three,four,five,six);
    // for(Command* c : macro.commandos){ 
    //     dio->write(c->getDescription() + "\n");
    // }
    macro.execute();
    

}   

CLI::~CLI(){
}

