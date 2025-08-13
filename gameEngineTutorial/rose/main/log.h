#pragma once
#include "src.h"
#include "rose_pch.h"

namespace rose{
 
        class ROSE_ENGINE_API Log{
        public:
            static void init();
                                //DATA TYPE                   FUNCTION       {  RETURN_TYPE }
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
        
        private:
        //            DATA TYPE                     VARIABLE
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;

        };

}
//CORE  LOG MACROS
#define ROSE_ERROR(...)    ::rose::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ROSE_WARN(...)     ::rose::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ROSE_INFO(...)     ::rose::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ROSE_TRACE(...)    ::rose::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ROSE_FATAL(...)    ::rose::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//CLIENT LOG MACROS
#define APP_ERROR(...)     ::rose::Log::GetClientLogger()->error(__VA_ARGS__)
#define APP_WARN(...)      ::rose::Log::GetClientLogger()->warn(__VA_ARGS__)
#define APP_INFO(...)      ::rose::Log::GetClientLogger()->info(__VA_ARGS__)
#define APP_TRACE(...)     ::rose::Log::GetClientLogger()->trace(__VA_ARGS__)
#define APP_FATAL(...)     ::rose::Log::GetClientLogger()->fatal(__VA_ARGS__)