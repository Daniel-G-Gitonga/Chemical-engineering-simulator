#pragma once 

#ifdef _WIN32 //signal engine is being used as dll __defined when game uses the dll
  #ifdef ROSE_BUILD_DLL  //defined only when building engine
     #define ROSE_ENGINE_API __declspec(dllexport) //
    #else
    #define ROSE_ENGINE_API __declspec(dllimport)
  #endif
  #else
    #define ROSE_ENGINE_API
  #endif

  #define BIT(x) (1 << x)//BIT ONE SHIFTED TO POSITION X