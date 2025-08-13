#include <engineheaders.h>

class Sandbox : public rose::Application{
public:
Sandbox();
~Sandbox();

};

Sandbox::Sandbox(){
    
    rose::Application::run();
    
}

rose::Application* createTheProgram(){
    return new Sandbox();
}