#include "app.h"
#include "DEFINITIONS/def.h"
#include <glad/glad.h>

int main(int argc, char ** argv){



chem::mess("Hello world , my nmae is daniel G and I am no one intresting \n \n anyways how are you \n\n HELLO FRIEND 😂");
chem::mess("current working dirrectory==> ");
std::cout<<argv[0]<<std::endl;

chem::App * sandBox = new chem::App("The Chemical Engineering SandBox",600.0f,600.0f);
if(sandBox->is_window_ready){
   
       
       sandBox->run();
       //debug...:::...purpose
       std::cout<<" \n window is created  ? "<<sandBox->is_window_ready<<std::endl;

    
}else{
    std::cout<<"THERE IS NO WINDOW AVAILABLE ... ::: ... CHECK THE WINDOW FILE"<<std::endl;
}

delete sandBox;

}