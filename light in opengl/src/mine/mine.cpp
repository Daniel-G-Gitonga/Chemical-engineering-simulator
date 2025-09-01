#include "mine/mine.h"


std::string hello(){
    return "hello world";
    
}

void Main::main_run(){
rose::Render * black_scr = new rose::Render();
black_scr->initRenderer(800,600,"black_scr");
     
while(!black_scr->closeWin()){
    black_scr->render();
    black_scr->events(black_scr->window);
}
black_scr->destroyRenderer();
delete black_scr;
}