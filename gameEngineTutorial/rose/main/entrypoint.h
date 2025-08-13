#pragma once

#ifdef _WIN32

extern rose::Application* createTheProgram();

int main(int argc, char** argv){
  
    rose::Log::init();
    ROSE_WARN("Initialized log!");
    APP_ERROR("Hello...!");


    auto app = createTheProgram();     
    app->run();
    delete app;

    return 0;   
}

#endif