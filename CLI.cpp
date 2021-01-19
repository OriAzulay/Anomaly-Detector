#include "CLI.h"


CLI::CLI(DefaultIO* di) {
    dio = di;
}

void CLI::start(){
    cout<<"Welcome to the Anomaly Detection Server."<<endl<<"Please choose an option:"<<endl;
    Command* one = new Command_1(dio);
    Command* two = new Command_2(dio);
    Command* three = new Command_3(dio);
    Command* four = new Command_4(dio);
    Command* five = new Command_5(dio);
    MacroCommand macro(dio);
    macro.setCommands(one,two,three,four,five);
    for(Command* c : macro.commandos){
        cout<<c->getDescription()<<endl;
    }
    cout<<"6. exit"<<endl;
    macro.execute();
    

}   

CLI::~CLI(){
}

