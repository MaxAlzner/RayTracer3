
#include "../include/RayTracer.h"

namespace ray
{
    
    inline float parse_value(rapidjson::Value& value)
    {
        return value.IsFloat() ? value.GetFloat() : 0.0f;
    }
    
    inline glm::vec2 parse_vec2(rapidjson::Value& value)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        return glm::vec2(x.IsFloat() ? x.GetFloat() : 0.0f, y.IsFloat() ? y.GetFloat() : 0.0f);
    }
    
    inline glm::vec3 parse_vec3(rapidjson::Value& value)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        rapidjson::Value& z = value["z"];
        return glm::vec3(x.IsFloat() ? x.GetFloat() : 0.0f, y.IsFloat() ? y.GetFloat() : 0.0f, z.IsFloat() ? z.GetFloat() : 0.0f);
    }
    
    inline glm::vec4 parse_vec4(rapidjson::Value& value)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        rapidjson::Value& z = value["z"];
        rapidjson::Value& w = value["w"];
        return glm::vec4(
            x.IsFloat() ? x.GetFloat() : 0.0f,
            y.IsFloat() ? y.GetFloat() : 0.0f,
            z.IsFloat() ? z.GetFloat() : 0.0f,
            w.IsFloat() ? w.GetFloat() : 0.0f);
    }
    
    inline transform_t parse_transform(rapidjson::Value& value)
    {
        return transform_t();
    }
    
    int read_scene(const char* filename, scene_t& scene)
    {
        if (filename != 0)
        {
            std::ifstream file(filename, std::ifstream::in);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);
            char* buffer = (char*)malloc(size);
            if (file.read(buffer, size))
            {
            	rapidjson::Document json;
            	json.Parse(buffer);
            	return read_scene(json, scene);
            }
            
            free(buffer);
        }
        
        return 0;
    }
    
    int read_scene(rapidjson::Document& document, scene_t& scene)
    {
        rapidjson::Value& render = document["render"];
        if (render.IsObject())
        {
            scene._photo = parse_vec2(render["photo"]);
        }
        
        rapidjson::Value& camera = document["camera"];
        if (camera.IsObject())
        {
            scene._camera = camera_t(
                parse_transform(camera["transform"]),
                parse_vec2(camera["aperture"]),
                parse_value(camera["focalPoint"]));
        }
        
        return 0;
    }
    
}