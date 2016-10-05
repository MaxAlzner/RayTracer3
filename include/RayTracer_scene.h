#pragma once

#include <iostream>
#include <fstream>

namespace ray
{
    
    struct scene_t
    {
        
        inline scene_t() {}
        inline ~scene_t() {}
        
        std::string _filename;
        glm::ivec2 _photo;
        camera_t _camera;
        tracestack_t _stack;
        
    };
    
    extern int read_scene(const char* filename, scene_t& scene);
    
    extern int read_scene(rapidjson::Document& document, scene_t& scene);
    
}