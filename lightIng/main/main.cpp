#include <iostream>
#include "app.h"

int main(int argc, char** argv){
    
    App* application = new App();
    application->run();    
    delete application;

    
    return 0;
}