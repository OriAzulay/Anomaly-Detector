#include "CLI.h"

DefaultIO* io;

CLI::CLI(DefaultIO* dio) {
    io = dio;
    setCommand();
}

void CLI::start(){ //The interaction need to work with the dio for generic..
    
}

void CLI::setCommand(){
    
}

CLI::~CLI() {
}

