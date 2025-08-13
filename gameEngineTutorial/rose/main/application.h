#pragma once

#include "src.h"

namespace rose{
class ROSE_ENGINE_API Application{
    public:
    Application();

    void static run();

    ~Application();
};


}

//note to me:: ROSE_ENGINE_API must always be use when we want to specify that the
//file is to exported simply used in all declarations(functions structures, classe) in engine