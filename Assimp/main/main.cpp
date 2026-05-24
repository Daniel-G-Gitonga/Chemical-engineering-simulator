#include <iostream>
#include "app.h"

int main(){
    

    App* main_app = new App();
    main_app->createWindow(800, 400);
    main_app->run();
    delete main_app;

    return 0;
}