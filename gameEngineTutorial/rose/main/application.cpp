#include "application.h"
#include "rose_pch.h"

namespace rose{
Application::Application(){
    printf("hello world chemical engineers\n");
};
Application::~Application(){
    printf("goodbye chemical engineers\n");
}
void Application::run(){
    printf("The function is working...\n");
}
}