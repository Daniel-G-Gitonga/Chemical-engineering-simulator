#pragma once
#include <iostream>
#include <string>

#include "mine/window.h"
#include "mine/mesh.h"

namespace rose{
    class Render : public Window{
      public:
      Render();
      void initRenderer(int width, int height, std::string win_ttl);
      void render();
      void destroyRenderer();
      ~Render();
      private:

    };
}