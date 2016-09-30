
#include "../include/RayTracer.h"

namespace ray
{
    
    inline float parse_value(rapidjson::Value& value, float def = 0.0f)
    {
        return value.IsFloat() ? value.GetFloat() : def;
    }
    
    inline glm::vec2 parse_vec2(rapidjson::Value& value, float def = 0.0f)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        return glm::vec2(x.IsFloat() ? x.GetFloat() : def, y.IsFloat() ? y.GetFloat() : def);
    }
    
    inline glm::vec3 parse_vec3(rapidjson::Value& value, float def = 0.0f)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        rapidjson::Value& z = value["z"];
        return glm::vec3(x.IsFloat() ? x.GetFloat() : def, y.IsFloat() ? y.GetFloat() : def, z.IsFloat() ? z.GetFloat() : def);
    }
    
    inline glm::vec4 parse_vec4(rapidjson::Value& value, float def = 0.0f)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        rapidjson::Value& z = value["z"];
        rapidjson::Value& w = value["w"];
        return glm::vec4(
            x.IsFloat() ? x.GetFloat() : def,
            y.IsFloat() ? y.GetFloat() : def,
            z.IsFloat() ? z.GetFloat() : def,
            w.IsFloat() ? w.GetFloat() : def);
    }
    
    inline transform_t parse_transform(rapidjson::Value& value)
    {
        glm::vec4 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        if (value.HasMember("translate"))
        {
            position = glm::vec4(parse_vec3(value["translate"]), 1.0f);
        }
        
        if (value.HasMember("rotation"))
        {
            rotation = parse_vec3(value["rotation"]);
        }
        
        if (value.HasMember("scale"))
        {
            scale = parse_vec3(value["scale"], 1.0f);
        }
        
        if (value.HasMember("tx")) { position.x = parse_value(value["tx"]); }
        else if (value.HasMember("ty")) { position.y = parse_value(value["ty"]); }
        else if (value.HasMember("tz")) { position.z = parse_value(value["tz"]); }
        else if (value.HasMember("rx")) { rotation.x = parse_value(value["rx"]); }
        else if (value.HasMember("ry")) { rotation.y = parse_value(value["ry"]); }
        else if (value.HasMember("rz")) { rotation.z = parse_value(value["rz"]); }
        else if (value.HasMember("sx")) { scale.x = parse_value(value["sx"], 1.0f); }
        else if (value.HasMember("sy")) { scale.y = parse_value(value["sy"], 1.0f); }
        else if (value.HasMember("sz")) { scale.z = parse_value(value["sz"], 1.0f); }
        
        return transform_t(position, scale, rotation);
    }
    
    int read_scene(const char* filename, scene_t& scene)
    {
        if (filename != 0)
        {
            std::ifstream file(filename, std::ifstream::in);
            if (file.is_open())
            {
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