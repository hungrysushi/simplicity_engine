#pragma once

namespace game_engine {

class Renderer {
public:
        Renderer();
        ~Renderer();
        
        RendererError CreateTriangle();
        RendererError CreateRectangle();
        RendererError DrawObject();
        RendererError DrawWorld();
};

}  // namespace game_engine
